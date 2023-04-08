package ai.serenade.treesitter.query.exceptions;

public class QueryErrorStructureException extends QueryException {
    public QueryErrorStructureException(String message, int errorOffset) {
        super(message, errorOffset);
    }
}
