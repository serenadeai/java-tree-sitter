package ai.serenade.treesitter.query.exceptions;

public class QueryNodeTypeException extends QueryException {
    public QueryNodeTypeException(String message, int errorOffset) {
        super(message, errorOffset);
    }
}
