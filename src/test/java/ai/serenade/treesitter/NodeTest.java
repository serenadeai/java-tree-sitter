package ai.serenade.treesitter;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

public class NodeTest {

  @Test
  void testGetChildren() {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.python());
      try (Tree tree = parser.parseString("def foo(bar, baz):\n  print(bar)\n  print(baz)")) {
        Node root = tree.getRootNode();
        assertEquals(1, root.getChildCount());
        assertEquals("module", root.getType());

        Node function = root.getChild(0);
        assertEquals("function_definition", function.getType());
        assertEquals(5, function.getChildCount());
      }
    }
  }
}
