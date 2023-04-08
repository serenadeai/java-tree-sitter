package ai.serenade.treesitter.query.exceptions;

public class QuerySyntaxException extends QueryException {
    public QuerySyntaxException(String message, int errorOffset) {
        super(message, errorOffset);
    }
}
