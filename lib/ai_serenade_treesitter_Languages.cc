#include "ai_serenade_treesitter_Languages.h"
#include <jni.h>
#include <string.h>
#include <tree_sitter/api.h>

extern "C" TSLanguage* tree_sitter_agda();
extern "C" TSLanguage* tree_sitter_bash();
extern "C" TSLanguage* tree_sitter_c();
extern "C" TSLanguage* tree_sitter_c_sharp();
extern "C" TSLanguage* tree_sitter_cpp();
extern "C" TSLanguage* tree_sitter_css();
extern "C" TSLanguage* tree_sitter_dart();
extern "C" TSLanguage* tree_sitter_elm();
extern "C" TSLanguage* tree_sitter_eno();
extern "C" TSLanguage* tree_sitter_go();
extern "C" TSLanguage* tree_sitter_haskell();
extern "C" TSLanguage* tree_sitter_html();
extern "C" TSLanguage* tree_sitter_java();
extern "C" TSLanguage* tree_sitter_javascript();
extern "C" TSLanguage* tree_sitter_jsx();
extern "C" TSLanguage* tree_sitter_julia();
extern "C" TSLanguage* tree_sitter_kotlin();
extern "C" TSLanguage* tree_sitter_lua();
extern "C" TSLanguage* tree_sitter_markdown();
extern "C" TSLanguage* tree_sitter_ocaml();
extern "C" TSLanguage* tree_sitter_php();
extern "C" TSLanguage* tree_sitter_python();
extern "C" TSLanguage* tree_sitter_ruby();
extern "C" TSLanguage* tree_sitter_rust();
extern "C" TSLanguage* tree_sitter_scala();
extern "C" TSLanguage* tree_sitter_scss();
extern "C" TSLanguage* tree_sitter_swift();
extern "C" TSLanguage* tree_sitter_toml();
extern "C" TSLanguage* tree_sitter_tsx();
extern "C" TSLanguage* tree_sitter_typescript();
extern "C" TSLanguage* tree_sitter_vue();
extern "C" TSLanguage* tree_sitter_yaml();
extern "C" TSLanguage* tree_sitter_wasm();

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_agda(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_agda();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_bash(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_bash();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_c(JNIEnv* env,
                                                                jclass self) {
  return (jlong)tree_sitter_c();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_c_sharp(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_c_sharp();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_cpp(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_cpp();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_css(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_css();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_dart(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_dart();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_elm(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_elm();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_eno(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_eno();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_go(JNIEnv* env,
                                                                 jclass self) {
  return (jlong)tree_sitter_go();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_haskell(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_haskell();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_html(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_html();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_java(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_java();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_javascript(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_javascript();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_jsx(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_jsx();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_julia(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_julia();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_kotlin(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_kotlin();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_lua(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_lua();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_markdown(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_markdown();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_ocaml(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_ocaml();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_php(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_php();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_python(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_python();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_ruby(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_ruby();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_rust(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_rust();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_scala(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_scala();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_scss(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_scss();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_swift(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_swift();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_toml(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_toml();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_tsx(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_tsx();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_typescript(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_typescript();
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_Languages_vue(JNIEnv* env,
                                                                  jclass self) {
  return (jlong)tree_sitter_vue();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_yaml(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_yaml();
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_Languages_wasm(JNIEnv* env, jclass self) {
  return (jlong)tree_sitter_wasm();
}
