package ai.serenade.treesitter;

public class TreeCursor {
  private int context0;
  private int context1;
  private long id;
  private long tree;

  public TreeCursor() {}

  public Node getCurrentNode() {
    return TreeSitter.treeCursorCurrentNode(this);
  }

  public String getCurrentFieldName() {
    return TreeSitter.treeCursorCurrentFieldName(this);
  }

  public boolean gotoFirstChild() {
    return TreeSitter.treeCursorGotoFirstChild(this);
  }

  public boolean gotoNextSibling() {
    return TreeSitter.treeCursorGotoNextSibling(this);
  }

  public boolean gotoParent() {
    return TreeSitter.treeCursorGotoParent(this);
  }
}
