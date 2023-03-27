package ai.serenade.treesitter;

import java.io.UnsupportedEncodingException;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class NodeTest extends TestBase {

  @Test
  void testGetChildren() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.python());
      try (Tree tree = parser.parseString("def foo(bar, baz):\n  print(bar)\n  print(baz)")) {
        Node root = tree.getRootNode();
        assertEquals(1, root.getChildCount());
        assertEquals("module", root.getType());
        assertEquals(0, root.getStartByte());
        assertEquals(44, root.getEndByte());

        Node function = root.getChild(0);
        assertEquals("function_definition", function.getType());
        assertEquals(5, function.getChildCount());
      }
    }
  }

  @Test
  void testGetChildren2() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.python());
      try (Tree tree = parser.parseString("def foo(bar baz)\n  print(bar,)\n  print(baz)")) {
        Node root = tree.getRootNode();
        assert(root.hasError());
      }
    }
  }

  @Test
  void testChildByFieldName() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.python());
      try (Tree tree = parser.parseString("if foo:\n  pass")) {
        Node root = tree.getRootNode();
        Node child = root.getChild(0);
        Node condition = child.getChildByFieldName("condition");
        assertNotNull(condition);
        assertEquals(condition.getType(), "identifier");
        assertNull(child.getChildByFieldName("woihfeowiejf"));
      }
    }
  }

  @Test
  void testPosition() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.python());
      try (Tree tree = parser.parseString("if foo:\n  pass")) {
        Node root = tree.getRootNode();
        assertEquals(0, root.getStartPosition().row);
        assertEquals(0, root.getStartPosition().column);
        assertEquals(1, root.getEndPosition().row);
        assertEquals(12, root.getEndPosition().column);

        Node consequence = root.getChild(0).getChildByFieldName("consequence");
        assertEquals(1, consequence.getStartPosition().row);
        assertEquals(4, consequence.getStartPosition().column);
        assertEquals(1, consequence.getEndPosition().row);
        assertEquals(12, consequence.getEndPosition().column);
      }
    }
  }
}
