package ai.serenade.treesitter;

public class TreeCursorNode {
  private final String type;
  private final String name;
  private final int startByte;
  private final int endByte;

  private final Point startPoint;

  private final Point endPoint;

  public TreeCursorNode(String type, String name, int startByte, int endByte, Point startPoint, Point endPoint) {
    this.type = type;
    this.name = name;
    this.startByte = startByte;
    this.endByte = endByte;
    this.startPoint = startPoint;
    this.endPoint = endPoint;
  }

  public String getType() {
    return type;
  }

  public String getName() {
    return name;
  }

  public int getStartByte() {
    return startByte;
  }

  public int getEndByte() {
    return endByte;
  }

  public Point getStartPoint() {
    return startPoint;
  }

  public Point getEndPoint() {
    return endPoint;
  }

  public Range getRange() {
    return new Range(startPoint, endPoint);
  }
}
