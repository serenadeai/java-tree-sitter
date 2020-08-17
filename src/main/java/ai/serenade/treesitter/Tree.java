package ai.serenade.treesitter;

public class Tree implements AutoCloseable {
  private long pointer;

  Tree(long pointer) {
    this.pointer = pointer;
  }

  @Override
  public void close() {
    TreeSitter.treeDelete(pointer);
  }

  public Node getRootNode() {
    return TreeSitter.treeRootNode(pointer);
  }
}
