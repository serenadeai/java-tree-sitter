package ai.serenade.treesitter;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;

import java.io.UnsupportedEncodingException;
import org.junit.jupiter.api.Test;

public class NodeTest extends TestBase {

  @Test
  void testGetChildren() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.java());
      try (Tree tree = parser.parseString("public class Thing { public static void main() { System.out.println('a'); } }")) {

        Node root = tree.getRootNode();
        assertEquals(1, root.getChildCount());
        assertEquals("program", root.getType());
        assertEquals(0, root.getStartByte());
        assertEquals(77, root.getEndByte());

        Node function = root.getChild(0);
        assertEquals("class_declaration", function.getType());
        assertEquals(4, function.getChildCount());
        assertTrue(function.isNamed());
        assertFalse(function.isNull());
      }
    }
  }

  @Test
  void testGetChildren() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.python());
      try (Tree tree = parser.parseString("def foo(bar baz)\n  print(bar,)\n  print(baz)")) {
        Node root = tree.getRootNode();
        assert(root.hasError());
      }
    }
  }
}
