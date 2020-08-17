package ai.serenade.treesitter;

public class Parser implements AutoCloseable {
  private long pointer;

  Parser(long pointer) {
    this.pointer = pointer;
  }

  public Parser() {
    this(TreeSitter.parserNew());
  }

  public void setLanguage(long language) {
    TreeSitter.parserSetLanguage(pointer, language);
  }

  public Tree parseString(String source) {
    return new Tree(TreeSitter.parserParseString(pointer, source, source.length()));
  }

  @Override
  public void close() {
    TreeSitter.parserDelete(pointer);
  }
}
