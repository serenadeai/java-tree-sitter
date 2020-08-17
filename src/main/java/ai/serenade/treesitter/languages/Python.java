package ai.serenade.treesitter.languages;

public class Python {

  static {
    System.loadLibrary("tree-sitter-python");
  }

  public static native long treeSitter();
}
