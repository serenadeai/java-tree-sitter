package ai.serenade.treesitter;

public class Range {
    public final int startRow;
    public final int endRow;

    public final int startCol;
    public final int endCol;

    public Range(Point startPoint, Point endPoint) {
        this.startRow = startPoint.row;
        this.startCol = startPoint.column;
        this.endRow = endPoint.row;
        this.endCol = endPoint.column;
    }

    public Range(int startRow, int startCol, int endRow, int endCol) {
        this.startRow = startRow;
        this.startCol = startCol;
        this.endRow = endRow;
        this.endCol = endCol;
    }

    @Override
    public String toString() {
        return String.format("[(%d, %d), (%d, %d)]", startRow, startCol, endRow, endCol);
    }
}
