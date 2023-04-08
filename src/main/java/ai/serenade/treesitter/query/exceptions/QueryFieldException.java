package ai.serenade.treesitter.query.exceptions;

public class QueryFieldException extends QueryException {
    public QueryFieldException(String message, int errorOffset) {
        super(message, errorOffset);
    }
}
