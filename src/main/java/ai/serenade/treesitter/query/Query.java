package ai.serenade.treesitter.query;


import ai.serenade.treesitter.TreeSitter;
import ai.serenade.treesitter.query.exceptions.*;
import ai.serenade.treesitter.query.internals.QueryCreationResult;
import ai.serenade.treesitter.query.internals.ResourceWithPointer;

import java.util.ArrayList;
import java.util.List;

public class Query extends ResourceWithPointer {

  public Query(long language, String query) throws QueryException {
    super();

    QueryCreationResult result = TreeSitter.queryNew(language, query);
    switch (result.errorType) {
      case 1 -> {
        throw new QuerySyntaxException("invalid syntax", result.errorOffset);
      }
      case 2 -> {
        throw new QueryNodeTypeException("invalid syntax", result.errorOffset);
      }
      case 3 -> {
        throw new QueryFieldException("invalid syntax", result.errorOffset);
      }
      case 4 -> {
        throw new QueryErrorCaptureException("invalid capture", result.errorOffset);
      }
      case 5 -> {
        throw new QueryErrorStructureException("invalid query structure", result.errorOffset);
      }
      case 6 -> {
        throw new QueryErrorLanguageException("invalid language", result.errorOffset);
      }
    }

    this.pointer = result.pointer;

  }

  @Override
  protected void deleteObject() {
    TreeSitter.queryDelete(this.pointer);
  }

  public List<QueryCapture> getCaptures() {
    int n = TreeSitter.queryCaptureCount(this.pointer);
    List<QueryCapture> result = new ArrayList<>();
    for(int i = 0 ; i < n ; i++) {
      String name = TreeSitter.queryCaptureNameForId(this.pointer, i);
      result.add(new QueryCapture(i, name));
    }
    return result;
  }

  public String toString() {
    return String.format("Query with pointer %x", this.pointer);
  }

  public long getPointer() {
    return this.pointer;
  }
}
