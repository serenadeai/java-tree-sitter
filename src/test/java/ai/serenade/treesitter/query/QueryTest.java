package ai.serenade.treesitter.query;

import ai.serenade.treesitter.*;
import ai.serenade.treesitter.query.exceptions.QueryException;
import ai.serenade.treesitter.query.exceptions.QuerySyntaxException;
import org.junit.jupiter.api.Test;

import java.io.UnsupportedEncodingException;
import java.util.List;
import java.util.logging.Logger;

import static org.junit.jupiter.api.Assertions.*;

public class QueryTest extends TestBase {
    Logger logger = Logger.getLogger("bla");

    @Test
    void testQueryValid() throws UnsupportedEncodingException, QueryException {
        try (Parser parser = new Parser()) {
            parser.setLanguage(Languages.python());
            String q = """
                    (function_definition
                    	name: (identifier) @name
                      parameters: (parameters) @params
                    )
                """;
            try (Query query = new Query(Languages.python(), q)) {
                assertNotNull(query);
                System.out.println(query);
                assertNotEquals(0, query.getPointer());
                List<QueryCapture> captures = query.getCaptures();
                assertEquals(2, query.getCaptures().size());

            }
        }
    }

    @Test
    void testQueryExecute() throws UnsupportedEncodingException, QueryException {

        try (Parser parser = new Parser()) {
            parser.setLanguage(Languages.python());
            try (Tree tree = parser.parseString("def foo(bar):\n  pass\n")) {
                Node root = tree.getRootNode();
                String q = """
                        (function_definition
                        	name: (identifier) @name
                          parameters: (parameters) @params
                        )
                    """;
                try (Query query = new Query(Languages.python(), q)) {
                    assertNotNull(query);
                    assertEquals(2, query.getCaptures().size());
                    QueryCursor queryCursor = query.execute(root);
                    QueryMatch queryMatch = queryCursor.nextMatch();
                    assertNotNull(queryMatch);
                    assertEquals(2, queryMatch.getCaptures().size());
                    assertEquals("identifier", queryMatch.getCaptures().get(0).node.getType());
                    assertEquals(0, queryMatch.getCaptures().get(0).node.getStartPosition().row);
                    assertEquals(4, queryMatch.getCaptures().get(0).node.getStartPosition().column);
                    assertEquals(0, queryMatch.getCaptures().get(0).node.getEndPosition().row);
                    assertEquals(7, queryMatch.getCaptures().get(0).node.getEndPosition().column);
                    assertEquals("parameters", queryMatch.getCaptures().get(1).node.getType());
                    assertEquals(0, queryMatch.getCaptures().get(1).node.getStartPosition().row);
                    assertEquals(7, queryMatch.getCaptures().get(1).node.getStartPosition().column);
                    assertEquals(0, queryMatch.getCaptures().get(1).node.getEndPosition().row);
                    assertEquals(12, queryMatch.getCaptures().get(1).node.getEndPosition().column);
                    assertNull(queryCursor.nextMatch());
                }
            }

        }
    }


    @Test
    void testQueryExecuteNoMatch() throws UnsupportedEncodingException, QueryException {

        try (Parser parser = new Parser()) {
            parser.setLanguage(Languages.python());
            try (Tree tree = parser.parseString("def foo(bar):\n  pass\n")) {
                Node root = tree.getRootNode();
                String q = """
                        (function_definition
                        	name: (identifier)
                          parameters: (parameters)
                        )
                    """;
                try (Query query = new Query(Languages.python(), q)) {
                    assertNotNull(query);
                    assertEquals(0, query.getCaptures().size());
                    QueryCursor queryCursor = query.execute(root);
                    QueryMatch queryMatch = queryCursor.nextMatch();
                    assertNotNull(queryMatch);
                    assertTrue(queryMatch.getCaptures().isEmpty());
                    queryMatch = queryCursor.nextMatch();
                    assertNull(queryMatch);
                }
            }

        }
    }

    @Test
    void testQueryInValid() throws UnsupportedEncodingException, QueryException {
        try (Parser parser = new Parser()) {
            parser.setLanguage(Languages.python());
            String q = """
                    (function_definition
                    	name: (identifier) @name
                        parameters: (parameters
                    )
                """;
            assertThrows(QuerySyntaxException.class, () -> {
                new Query(Languages.python(), q);
            });
        }
    }
}
