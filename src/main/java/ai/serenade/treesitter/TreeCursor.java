package ai.serenade.treesitter;

public class TreeCursor {
  private int context0;
  private int context1;
  private long id;
  private long tree;

  public TreeCursor() {}

  public String getCurrentFieldName() {
    return TreeSitterJNI.cursorCurrentFieldName(this);
  }

  public boolean gotoFirstChild() {
    return TreeSitterJNI.gotoFirstChild(this);
  }

  public boolean gotoNextSibling() {
    return TreeSitterJNI.gotoNextSibling(this);
  }

  public boolean gotoParent() {
    return TreeSitterJNI.gotoParent(this);
  }
}
