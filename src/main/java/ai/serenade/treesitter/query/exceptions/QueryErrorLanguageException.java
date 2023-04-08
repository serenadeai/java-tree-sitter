package ai.serenade.treesitter.query.exceptions;

public class QueryErrorLanguageException extends QueryException {
    public QueryErrorLanguageException(String message, int errorOffset) {
        super(message, errorOffset);
    }
}
