package ai.serenade.treesitter;

import ai.serenade.treesitter.query.internals.ResourceWithPointer;

public class TreeCursor extends ResourceWithPointer {
  private int context0;
  private int context1;
  private long id;
  private long tree;

  TreeCursor(long pointer) {
    super();
    this.pointer = pointer;
  }


  @Override
  protected void deleteObject() {
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
