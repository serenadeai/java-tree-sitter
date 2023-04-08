package ai.serenade.treesitter.query;

import ai.serenade.treesitter.TreeSitter;

public class QueryMatch implements AutoCloseable {
  public int id;
  public int patternIndex;
  public int captureCount;

  QueryMatch(long pointer) {
  }

  @Override
  public void close() {
    // FIXME
//    TreeSitter.queryDelete(pointer);
  }

}
