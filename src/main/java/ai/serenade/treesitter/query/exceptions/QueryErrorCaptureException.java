package ai.serenade.treesitter.query.exceptions;

public class QueryErrorCaptureException extends QueryException {
    public QueryErrorCaptureException(String message, int errorOffset) {
        super(message, errorOffset);
    }
}
