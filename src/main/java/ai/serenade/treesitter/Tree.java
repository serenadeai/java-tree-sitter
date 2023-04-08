package ai.serenade.treesitter;

import ai.serenade.treesitter.query.internals.ResourceWithPointer;

public class Tree extends ResourceWithPointer {

  Tree(long pointer) {
    super();
    this.pointer = pointer;
  }


  @Override
  protected void deleteObject() {
    TreeSitter.treeDelete(pointer);
  }

  public Node getRootNode() {
    return TreeSitter.treeRootNode(pointer);
  }
}
