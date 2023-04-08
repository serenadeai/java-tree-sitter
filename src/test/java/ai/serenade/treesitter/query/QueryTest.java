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
      try(Query query = new Query(Languages.python(), q)) {
        assertNotNull(query);
        System.out.println(query.toString());
        assertNotEquals(0, query.getPointer());
        List<QueryCapture> captures = query.getCaptures();

      }
    }
  }

//  @Test
//  void testQueryInValid() throws UnsupportedEncodingException, QueryException {
//    try (Parser parser = new Parser()) {
//      parser.setLanguage(Languages.python());
//      String q = """
//              (function_definition
//              	name: (identifier) @name
//                  parameters: (parameters
//              )
//          """;
//      assertThrows(QuerySyntaxException.class, () -> {
//        new Query(Languages.python(), q);
//      });
//    }
//  }
}
