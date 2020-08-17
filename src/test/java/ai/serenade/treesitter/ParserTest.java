package ai.serenade.treesitter;

import static org.junit.jupiter.api.Assertions.assertEquals;

import ai.serenade.treesitter.languages.Python;
import org.junit.jupiter.api.Test;

public class ParserTest {

  @Test
  void testParse() {
    try (Parser parser = new Parser()) {
      parser.setLanguage("python");
      try (Tree tree = parser.parseString("print(\"hi\")")) {
        assertEquals(
          "(module (expression_statement (call function: (identifier) arguments: (argument_list (string)))))",
          tree.rootNode().getNodeString()
        );
      }
    }
  }
}
