package ai.serenade.treesitter;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

public class ParserTest extends TestBase {

  @Test
  void testParse() {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.python());
      try (Tree tree = parser.parseString("print(\"hi\")")) {
        assertEquals(
          "(module (expression_statement (call function: (identifier) arguments: (argument_list (string)))))",
          tree.getRootNode().getNodeString()
        );
      }
    }
  }
}
