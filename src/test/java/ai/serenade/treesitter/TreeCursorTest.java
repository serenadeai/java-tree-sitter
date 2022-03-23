package ai.serenade.treesitter;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.UnsupportedEncodingException;
import org.junit.jupiter.api.Test;

public class TreeCursorTest extends TestBase {

  @Test
  void testWalk() throws UnsupportedEncodingException {
    try (Parser parser = new Parser()) {
      parser.setLanguage(Languages.java());
      try (Tree tree = parser.parseString("public class Thing { /** abc \n *\n */\npublic static void main() { System.out.println('a'); } }")) {
        try (TreeCursor cursor = tree.getRootNode().walk()) {

          for (TreeCursor it = cursor; it.hasNext(); ) {
            TreeCursorNode n = it.next();

            System.out.println(n.getType() + " " + n.getName() + " " + n.getRange());

          }
          assertEquals("program", cursor.getCurrentTreeCursorNode().getType());
          assertEquals("program", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoFirstChild());
          assertEquals("class_declaration", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoFirstChild());
          assertEquals("modifiers", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("class", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("identifier", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("class_body", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoFirstChild());
          assertEquals("{", cursor.getCurrentNode().getType());
          System.out.println(cursor.getCurrentNode().getNodeString());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("comment", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("method_declaration", cursor.getCurrentNode().getType());
          assertEquals(true, cursor.gotoNextSibling());
          assertEquals("}", cursor.getCurrentNode().getType());
//          assertEquals("function_definition", cursor.getCurrentNode().getType());
//          assertEquals(true, cursor.gotoFirstChild());
        }
      }
    }
  }
}
