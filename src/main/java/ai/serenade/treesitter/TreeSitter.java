package ai.serenade.treesitter;

public class TreeSitter {

  public static native Node nodeChild(Node node, int child);

  public static native int nodeChildCount(Node node);

  public static native boolean nodeHasError(Node node);

  public static native int nodeEndByte(Node node);

  public static native int nodeStartByte(Node node);

  public static native Point nodeStartPoint(Node node);

  public static native Point nodeEndPoint(Node node);

  public static native String nodeString(Node node);

  public static native String nodeType(Node node);

  public static native boolean nodeIsNull(Node node);

  public static native boolean nodeIsNamed(Node node);

  public static native Node nodePrevSibling(Node node);

  public static native Node nodeNextSibling(Node node);

  public static native Node nodeParent(Node node);

  public static native boolean nodeHasParent(Node node);

  public static native boolean nodeHasPrevSibling(Node node);

  public static native boolean nodeHasNextSibling(Node node);

  public static native String nodeGetFieldName(Node node);

  public static native long parserNew();

  public static native void parserDelete(long parser);

  public static native void parserSetLanguage(long parser, long language);

  public static native long parserParseBytes(long parser, byte[] source, int length);

  public static native long treeCursorNew(Node node);

  public static native TreeCursorNode treeCursorCurrentTreeCursorNode(long cursor);

  public static native String treeCursorCurrentFieldName(long cursor);

  public static native Node treeCursorCurrentNode(long cursor);

  public static native void treeCursorDelete(long cursor);

  public static native boolean treeCursorGotoFirstChild(long cursor);

  public static native boolean treeCursorGotoNextSibling(long cursor);

  public static native boolean treeCursorGotoParent(long cursor);

  public static native void treeDelete(long tree);

  public static native Node treeRootNode(long tree);
}
