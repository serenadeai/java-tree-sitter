package ai.serenade.treesitter;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class TreeCursor implements AutoCloseable, Iterator<TreeCursorNode> {
  private long pointer;
  private int context0;
  private int context1;
  private long id;
  private long tree;

  private boolean end = false;

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

  @Override
  public boolean hasNext() {
    Node curr = this.getCurrentNode();
    // If the end flag is set, we assume the iterator is exhausted.
    if (end) return false;
    // If this is a null node, return false.
    if (curr.isNull()) return false;
    // If this node has children, return true.
    if (curr.getChildCount() > 0) {
      System.out.println("next is child");
      return true;
    }
    // If this node has no children but has a sibling, return true.
    if (curr.hasNextSibling()) {
      System.out.println("next is sibling");
      return true;
    }
    // If this node has no children or next sibling, but has a parent, return true.
    if (curr.hasParent()) {
      System.out.println("next is parent sibling");
      return true;
    }
    // There's a lint that attempts to simplify this if statement above, but we want clarity.
    return false;
  }

  @Override
  public TreeCursorNode next() {
    if (end) throw new NoSuchElementException("This cursor is exhausted.");
    TreeCursorNode currTCNode = this.getCurrentTreeCursorNode();
    Node curr = this.getCurrentNode();
    if (curr.isNull()) throw new NoSuchElementException("Current Tree sitter node is null.");
    boolean couldTraverseNext = false;
    if (curr.getChildCount() > 0) {
       couldTraverseNext = this.gotoFirstChild();
    } else if (curr.hasNextSibling()) {
      couldTraverseNext = this.gotoNextSibling();
    } else {
      // We try to backtrack until we reach a node that has a next sibling.
      // This is a rather dumb pattern to use, but what to do, it would look quite clunky otherwise.
      // We try the following things:
      // 1. check if the current node is not null (if it is, we want to stop).
      // 2. check if the current node has a sibling (if it does, we want to stop).
      // 3. check if we can traverse to the parent node (if we can't, we want to stop).
      while(!this.getCurrentNode().isNull() && !this.getCurrentNode().hasNextSibling() && (couldTraverseNext = this.gotoParent()));
      couldTraverseNext |= this.gotoNextSibling();
    }

    if (!couldTraverseNext) end = true;

    return currTCNode;
  }
}
