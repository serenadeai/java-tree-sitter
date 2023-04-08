package ai.serenade.treesitter.query;

import ai.serenade.treesitter.Node;
import ai.serenade.treesitter.TreeSitter;

public class QueryCursor implements AutoCloseable {
  private long pointer;

  public QueryCursor(Query query, Node node) {


  }

  public QueryMatch nextMatch() {
    return null;
  }

  @Override
  public void close() {
    //TreeSitter.queryCursorDelete(pointer);
  }

}
