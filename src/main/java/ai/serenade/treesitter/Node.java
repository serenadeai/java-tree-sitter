package ai.serenade.treesitter;

public class Node {
  private int context0;
  private int context1;
  private int context2;
  private int context3;
  private long id;
  private long tree;

  public Node() {}

  public Node getChild(int child) {
    return TreeSitterJNI.nodeChild(this, child);
  }

  public int getChildCount() {
    return TreeSitterJNI.nodeChildCount(this);
  }

  public String getNodeString() {
    return TreeSitterJNI.nodeString(this);
  }

  public String getType() {
    return TreeSitterJNI.nodeType(this);
  }

  public int nodeEndByte() {
    return TreeSitterJNI.nodeEndByte(this);
  }

  public int nodeStartByte() {
    return TreeSitterJNI.nodeStartByte(this);
  }

  public TreeCursor walk() {
    return TreeSitterJNI.treeCursorNew(this);
  }
}
