package ai.serenade.treesitter;

import ai.serenade.treesitter.query.internals.ResourceWithPointer;

import java.io.UnsupportedEncodingException;
import java.nio.charset.StandardCharsets;

public class Parser extends ResourceWithPointer {

  Parser(long pointer) {
    super();
    this.pointer = pointer;
  }

  public Parser() {
    this(TreeSitter.parserNew());
  }

  public void setLanguage(long language) {
    TreeSitter.parserSetLanguage(pointer, language);
  }

  public Tree parseString(String source) throws UnsupportedEncodingException {
    byte[] bytes = source.getBytes(StandardCharsets.UTF_16LE);
    return new Tree(TreeSitter.parserParseBytes(pointer, bytes, bytes.length));
  }


  @Override
  protected void deleteObject() {
    TreeSitter.parserDelete(pointer);
  }
}
