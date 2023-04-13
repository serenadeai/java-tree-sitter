package ai.serenade.treesitter.query;

import ai.serenade.treesitter.Node;
import ai.serenade.treesitter.TreeSitter;
import ai.serenade.treesitter.query.internals.ResourceWithPointer;

public class QueryCursor extends ResourceWithPointer {

    private QueryCursor(long pointer) {
        super();
        this.pointer = pointer;
    }

    protected QueryCursor() {
        this(TreeSitter.queryCursorNew());
    }

    public QueryMatch nextMatch() {
        QueryMatch queryMatch = TreeSitter.queryCursorNextMatch(this.pointer);
        return queryMatch;
    }


    @Override
    protected void deleteObject() {
        TreeSitter.queryCursorDelete(this.pointer);
    }

}
