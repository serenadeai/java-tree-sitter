package ai.serenade.treesitter;

public class Parser implements AutoCloseable {
  private long pointer;

  Parser(long pointer) {
    this.pointer = pointer;
  }

  public Parser() {
    this(TreeSitterJNI.parserNew());
  }

  public void setLanguage(String language) {
    TreeSitterJNI.parserSetLanguage(pointer, language);
  }

  public void setLanguage(long language) {
    TreeSitterJNI.parserSetLanguagePointer(pointer, language);
  }

  public Tree parseString(String source) {
    return new Tree(TreeSitterJNI.parserParseString(pointer, source, source.length()));
  }

  @Override
  public void close() {
    TreeSitterJNI.parserDelete(pointer);
  }
}
