# java-tree-sitter

Java bindings for [tree-sitter](https://tree-sitter.github.io/tree-sitter/).

## Preparing

Recursively clone the project with submodules:

```shell
git clone https://github.com/serenadeai/java-tree-sitter.git --recursive
```

Or clone first and update the submodules then:

```shell   
git clone https://github.com/serenadeai/java-tree-sitter.git
git submodule update --init --recursive  
# or:  git submodule init && git submodule update
```

## Installing

To add this library to a Gradle project:
```java
allprojects {
    repositories {
        maven { 
            url 'https://jitpack.io'
        }
    }
}

dependencies {
    implementation "com.github.serenadeai:java-tree-sitter:1.1.2"
}
```

## Building

Before you can start using java-tree-sitter, you need to build a shared library that Java can load using the `build.py` script. The first argument is the output file (_libjava-tree-sitter_ by default), followed by all of the tree-sitter repositories (already downloaded) that you want to include:

```bash
./build.py -o libjava-tree-sitter path-to-tree-sitter-css path-to-tree-sitter-python ...
```

## Examples

First, load the shared object somewhere in your application:

```java
public class App {
  static {
    // or on a Mac, libjava-tree-sitter.dylib
    System.load("./path/to/libjava-tree-sitter.so");
  }
}
```

Then, you can create a `Parser`, set the language, and parse a string:

```java
try (Parser parser = new Parser()) {
  parser.setLanguage(Languages.python());
  try (Tree tree = parser.parseString("def foo(bar, baz):\n  print(bar)\n  print(baz)")) {
    Node root = tree.getRootNode();
    assertEquals(1, root.getChildCount());
    assertEquals("module", root.getType());
    assertEquals(0, root.getStartByte());
    assertEquals(44, root.getEndByte());

    Node function = root.getChild(0);
    assertEquals("function_definition", function.getType());
    assertEquals(5, function.getChildCount());
  }
}
```

For debugging, it can be helpful to see a string of the tree:

```
try (Parser parser = new Parser()) {
  parser.setLanguage(Languages.python());
  try (Tree tree = parser.parseString("print(\"hi\")")) {
    assertEquals(
      "(module (expression_statement (call function: (identifier) arguments: (argument_list (string)))))",
      tree.getRootNode().getNodeString()
    );
  }
}
```

If you're going to be traversing a tree, then you can use the `walk` method, which is much more efficient than the above getters:

```
try (Parser parser = new Parser()) {
  parser.setLanguage(Languages.python());
  try (Tree tree = parser.parseString("def foo(bar, baz):\n  print(bar)\n  print(baz)")) {
    try (TreeCursor cursor = tree.getRootNode().walk()) {
      assertEquals("module", cursor.getCurrentTreeCursorNode().getType());
      cursor.gotoFirstChild();
      assertEquals("function_definition", cursor.getCurrentTreeCursorNode().getType());
      cursor.gotoFirstChild();
      assertEquals("def", cursor.getCurrentTreeCursorNode().getType());
      cursor.gotoNextSibling();
      cursor.gotoParent();
    }
  }
}
```

For more examples, see the tests in `src/test/java/ai/serenade/treesitter`.
