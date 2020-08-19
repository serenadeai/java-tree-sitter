package ai.serenade.treesitter;

public class TreeCursor implements AutoCloseable {
  private long pointer;
  private int context0;
  private int context1;
  private long id;
  private long tree;

  TreeCursor(long pointer) {
    this.pointer = pointer;
  }

  @Override
  public void close() {
    TreeSitter.treeCursorDelete(pointer);
  }

  public Node getCurrentNode() {
    return TreeSitter.treeCursorCurrentNode(pointer);
  }

  public String getCurrentFieldName() {
    return TreeSitter.treeCursorCurrentFieldName(pointer);
  }

  public TreeCursorNode getCurrentTreeCursorNode() {
    return TreeSitter.treeCursorCurrentTreeCursorNode(pointer);
  }

  public boolean gotoFirstChild() {
    return TreeSitter.treeCursorGotoFirstChild(pointer);
  }

  public boolean gotoNextSibling() {
    return TreeSitter.treeCursorGotoNextSibling(pointer);
  }

  public boolean gotoParent() {
    return TreeSitter.treeCursorGotoParent(pointer);
  }
}
