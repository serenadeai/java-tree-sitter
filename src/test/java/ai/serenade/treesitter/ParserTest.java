package ai.serenade.treesitter;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.UnsupportedEncodingException;
import org.junit.jupiter.api.Test;

public class ParserTest extends TestBase {

  @Test
  void testParse() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.java());
      try (Tree tree = parser.parseString("public class Thing { public static void main() { System.out.println('a'); } }")) {
        assertEquals(
                "(program (class_declaration (modifiers) name: (identifier) body: (class_body (method_declaration (modifiers) type: (void_type) name: (identifier) parameters: (formal_parameters) body: (block (expression_statement (method_invocation object: (field_access object: (identifier) field: (identifier)) name: (identifier) arguments: (argument_list (character_literal)))))))))",
                tree.getRootNode().getNodeString()
        );
      }
    }
  }
}
