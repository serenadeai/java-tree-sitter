package ai.serenade.treesitter.query.exceptions;

public class QueryException extends Exception{

    public int errorOffset;

    public QueryException(String message, int errorOffset){
        super(message);
        this.errorOffset = errorOffset;
    }
}
