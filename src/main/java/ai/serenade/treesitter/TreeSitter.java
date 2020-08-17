package ai.serenade.treesitter;

public class TreeSitter {

  static {
    System.loadLibrary("java-tree-sitter");
  }

  public static native String cursorCurrentFieldName(TreeCursor cursor);

  public static native boolean gotoFirstChild(TreeCursor cursor);

  public static native boolean gotoNextSibling(TreeCursor cursor);

  public static native boolean gotoParent(TreeCursor cursor);

  public static native Node nodeChild(Node node, int child);

  public static native int nodeChildCount(Node node);

  public static native int nodeEndByte(Node node);

  public static native int nodeStartByte(Node node);

  public static native String nodeString(Node node);

  public static native String nodeType(Node node);

  public static native long parserNew();

  public static native void parserDelete(long parser);

  public static native void parserSetLanguage(long parser, long language);

  public static native long parserParseString(long parser, String source, int length);

  public static native TreeCursor treeCursorNew(Node node);

  public static native void treeDelete(long tree);

  public static native Node treeRootNode(long tree);
}
