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
    return TreeSitter.nodeChild(this, child);
  }

  public int getChildCount() {
    return TreeSitter.nodeChildCount(this);
  }

  public boolean hasError() {
    return TreeSitter.nodeHasError(this);
  }

  public int getEndByte() {
    return TreeSitter.nodeEndByte(this);
  }

  public String getNodeString() {
    return TreeSitter.nodeString(this);
  }

  public int getStartByte() {
    return TreeSitter.nodeStartByte(this);
  }

  public Range getRange() {
    Point start = TreeSitter.nodeStartPoint(this);
    Point end = TreeSitter.nodeEndPoint(this);
    return new Range(
            start.row,
            start.column,
            end.row,
            end.column
    );
  }

  public boolean hasParent() {
    return TreeSitter.nodeHasParent(this);
  }

  public boolean hasNextSibling() {
    return TreeSitter.nodeHasNextSibling(this);
  }

  public boolean hasPrevSibling() {
    return TreeSitter.nodeHasPrevSibling(this);
  }

  public Node getParent() {
    return TreeSitter.nodeParent(this);
  }

  public Node getNextSibling() {
    return TreeSitter.nodeNextSibling(this);
  }

  public Node getPrevSibling() {
    return TreeSitter.nodePrevSibling(this);
  }

  public String getFieldName() {
    return TreeSitter.nodeGetFieldName(this);
  }

  public String getType() {
    return TreeSitter.nodeType(this);
  }

  public boolean isNull() {
    return TreeSitter.nodeIsNull(this);
  }

  public boolean isNamed() {
    return TreeSitter.nodeIsNamed(this);
  }

  public TreeCursor walk() {
    return new TreeCursor(TreeSitter.treeCursorNew(this));
  }
}
