package ai.serenade.treesitter;

public class TreeCursor {
  private int context0;
  private int context1;
  private long id;
  private long tree;

  public TreeCursor() {}

  public String getCurrentFieldName() {
    return TreeSitter.cursorCurrentFieldName(this);
  }

  public boolean gotoFirstChild() {
    return TreeSitter.gotoFirstChild(this);
  }

  public boolean gotoNextSibling() {
    return TreeSitter.gotoNextSibling(this);
  }

  public boolean gotoParent() {
    return TreeSitter.gotoParent(this);
  }
}
