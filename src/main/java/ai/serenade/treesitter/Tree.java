package ai.serenade.treesitter;

public class Tree implements AutoCloseable {
  private long pointer;

  Tree(long pointer) {
    this.pointer = pointer;
  }

  @Override
  public void close() {
    TreeSitterJNI.treeDelete(pointer);
  }

  public Node rootNode() {
    return TreeSitterJNI.treeRootNode(pointer);
  }
}
