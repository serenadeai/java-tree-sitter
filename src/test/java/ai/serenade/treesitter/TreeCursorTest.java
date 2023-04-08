package ai.serenade.treesitter;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.UnsupportedEncodingException;
import org.junit.jupiter.api.Test;

public class TreeCursorTest extends TestBase {

  @Test
  void testWalk() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.python());
      try (Tree tree = parser.parseString("def foo(bar, baz):\n  print(bar)\n  print(baz)")) {
        try (TreeCursor cursor = tree.getRootNode().walk()) {
          assertEquals("module", cursor.getCurrentTreeCursorNode().getType());
          assertEquals("module", cursor.getCurrentNode().getType());
          assertTrue(cursor.gotoFirstChild());
          assertEquals("function_definition", cursor.getCurrentNode().getType());
          assertTrue(cursor.gotoFirstChild());

          assertEquals("def", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("identifier", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("parameters", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals(":", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("block", cursor.getCurrentNode().getType());
          assertEquals("body", cursor.getCurrentFieldName());
          assertEquals(false, cursor.gotoNextSibling());

          assertEquals(true, cursor.gotoParent());
          assertEquals("function_definition", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoFirstChild());
        }
      }
    }
  }
}
