#include "ai_serenade_treesitter_TreeSitterJNI.h"
#include <jni.h>
#include <string.h>
#include <tree_sitter/api.h>

extern "C" TSLanguage* tree_sitter_css();
extern "C" TSLanguage* tree_sitter_dart();
extern "C" TSLanguage* tree_sitter_html();
extern "C" TSLanguage* tree_sitter_java();
extern "C" TSLanguage* tree_sitter_javascript();
extern "C" TSLanguage* tree_sitter_jsx();
extern "C" TSLanguage* tree_sitter_python();
extern "C" TSLanguage* tree_sitter_scss();
extern "C" TSLanguage* tree_sitter_tsx();
extern "C" TSLanguage* tree_sitter_typescript();

jobject _marshalNode(JNIEnv* env, TSNode node) {
  jclass javaClass = env->FindClass("ai/serenade/treesitter/Node");
  jobject javaObject = env->AllocObject(javaClass);

  jfieldID context0Field = env->GetFieldID(javaClass, "context0", "I");
  jfieldID context1Field = env->GetFieldID(javaClass, "context1", "I");
  jfieldID context2Field = env->GetFieldID(javaClass, "context2", "I");
  jfieldID context3Field = env->GetFieldID(javaClass, "context3", "I");
  jfieldID idField = env->GetFieldID(javaClass, "id", "J");
  jfieldID treeField = env->GetFieldID(javaClass, "tree", "J");

  env->SetIntField(javaObject, context0Field, node.context[0]);
  env->SetIntField(javaObject, context1Field, node.context[1]);
  env->SetIntField(javaObject, context2Field, node.context[2]);
  env->SetIntField(javaObject, context3Field, node.context[3]);
  env->SetLongField(javaObject, idField, (jlong)node.id);
  env->SetLongField(javaObject, treeField, (jlong)node.tree);

  return javaObject;
}

TSNode _unmarshalNode(JNIEnv* env, jobject javaObject) {
  jclass javaClass = env->FindClass("ai/serenade/treesitter/Node");
  jfieldID context0Field = env->GetFieldID(javaClass, "context0", "I");
  jfieldID context1Field = env->GetFieldID(javaClass, "context1", "I");
  jfieldID context2Field = env->GetFieldID(javaClass, "context2", "I");
  jfieldID context3Field = env->GetFieldID(javaClass, "context3", "I");
  jfieldID idField = env->GetFieldID(javaClass, "id", "J");
  jfieldID treeField = env->GetFieldID(javaClass, "tree", "J");

  return (TSNode){{
                      (uint32_t)env->GetIntField(javaObject, context0Field),
                      (uint32_t)env->GetIntField(javaObject, context1Field),
                      (uint32_t)env->GetIntField(javaObject, context2Field),
                      (uint32_t)env->GetIntField(javaObject, context3Field),
                  },
                  (const void*)env->GetLongField(javaObject, idField),
                  (const TSTree*)env->GetLongField(javaObject, treeField)};
}

TSTreeCursor _unmarshalTreeCursor(JNIEnv* env, jobject javaObject) {
  jclass javaClass = env->FindClass("ai/serenade/treesitter/TreeCursor");
  jfieldID context0Field = env->GetFieldID(javaClass, "context0", "I");
  jfieldID context1Field = env->GetFieldID(javaClass, "context1", "I");
  jfieldID idField = env->GetFieldID(javaClass, "id", "J");
  jfieldID treeField = env->GetFieldID(javaClass, "tree", "J");

  return (TSTreeCursor){
      (const void*)env->GetLongField(javaObject, treeField),
      (const void*)env->GetLongField(javaObject, idField),
      {
          (uint32_t)env->GetIntField(javaObject, context0Field),
          (uint32_t)env->GetIntField(javaObject, context1Field),
      }};
}

jobject _marshalTreeCursor(JNIEnv* env, TSTreeCursor cursor) {
  jclass javaClass = env->FindClass("ai/serenade/treesitter/TreeCursor");
  jobject javaObject = env->AllocObject(javaClass);

  jfieldID context0Field = env->GetFieldID(javaClass, "context0", "I");
  jfieldID context1Field = env->GetFieldID(javaClass, "context1", "I");
  jfieldID idField = env->GetFieldID(javaClass, "id", "J");
  jfieldID treeField = env->GetFieldID(javaClass, "tree", "J");

  env->SetIntField(javaObject, context0Field, cursor.context[0]);
  env->SetIntField(javaObject, context1Field, cursor.context[1]);
  env->SetLongField(javaObject, idField, (jlong)cursor.id);
  env->SetLongField(javaObject, treeField, (jlong)cursor.tree);

  return javaObject;
}

void _updateTreeCursor(JNIEnv* env, jobject cursor, TSTreeCursor* treeCursor) {
  jclass javaClass = env->FindClass("ai/serenade/treesitter/TreeCursor");

  jfieldID context0Field = env->GetFieldID(javaClass, "context0", "I");
  jfieldID context1Field = env->GetFieldID(javaClass, "context1", "I");
  jfieldID idField = env->GetFieldID(javaClass, "id", "J");
  jfieldID treeField = env->GetFieldID(javaClass, "tree", "J");

  env->SetIntField(cursor, context0Field, treeCursor->context[0]);
  env->SetIntField(cursor, context1Field, treeCursor->context[1]);
  env->SetLongField(cursor, idField, (jlong)treeCursor->id);
  env->SetLongField(cursor, treeField, (jlong)treeCursor->tree);
}

JNIEXPORT jstring JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_cursorCurrentFieldName(
    JNIEnv* env, jclass self, jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  const char* name = ts_tree_cursor_current_field_name(&treeCursor);
  jstring result = env->NewStringUTF(name);
  return result;
}

JNIEXPORT jboolean JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_gotoFirstChild(JNIEnv* env,
                                                         jclass self,
                                                         jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  bool result = ts_tree_cursor_goto_first_child(&treeCursor);
  _updateTreeCursor(env, cursor, &treeCursor);
  return (jboolean)result;
}

JNIEXPORT jboolean JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_gotoNextSibling(JNIEnv* env,
                                                          jclass self,
                                                          jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  bool result = ts_tree_cursor_goto_next_sibling(&treeCursor);
  _updateTreeCursor(env, cursor, &treeCursor);
  return (jboolean)result;
}

JNIEXPORT jboolean JNICALL Java_ai_serenade_treesitter_TreeSitterJNI_gotoParent(
    JNIEnv* env, jclass self, jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  bool result = ts_tree_cursor_goto_parent(&treeCursor);
  _updateTreeCursor(env, cursor, &treeCursor);
  return (jboolean)result;
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitterJNI_nodeChild(
    JNIEnv* env, jclass self, jobject node, jint child) {
  return _marshalNode(
      env, ts_node_child(_unmarshalNode(env, node), (uint32_t)child));
}

JNIEXPORT jint JNICALL Java_ai_serenade_treesitter_TreeSitterJNI_nodeChildCount(
    JNIEnv* env, jclass self, jobject node) {
  return (jint)ts_node_child_count(_unmarshalNode(env, node));
}

JNIEXPORT jstring JNICALL Java_ai_serenade_treesitter_TreeSitterJNI_nodeString(
    JNIEnv* env, jclass self, jobject node) {
  char* nodeString = ts_node_string(_unmarshalNode(env, node));
  jstring result = env->NewStringUTF(nodeString);
  free(nodeString);
  return result;
}

JNIEXPORT jstring JNICALL Java_ai_serenade_treesitter_TreeSitterJNI_nodeType(
    JNIEnv* env, jclass self, jobject node) {
  const char* type = ts_node_type(_unmarshalNode(env, node));
  jstring result = env->NewStringUTF(type);
  return result;
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_parserNew(JNIEnv* env, jclass self) {
  return (jlong)ts_parser_new();
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitterJNI_parserDelete(
    JNIEnv* env, jclass self, jlong parser) {
  ts_parser_delete((TSParser*)parser);
}

JNIEXPORT void JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_parserSetLanguage(
    JNIEnv* env, jclass self, jlong parser, jstring language_name) {
  const char* language = env->GetStringUTFChars(language_name, 0);
  TSLanguage* parser_language;
  if (strcmp(language, "css") == 0) {
    parser_language = tree_sitter_css();
  } else if (strcmp(language, "dart") == 0) {
    parser_language = tree_sitter_dart();
  } else if (strcmp(language, "html") == 0) {
    parser_language = tree_sitter_html();
  } else if (strcmp(language, "java") == 0) {
    parser_language = tree_sitter_java();
  } else if (strcmp(language, "javascript") == 0) {
    parser_language = tree_sitter_javascript();
  } else if (strcmp(language, "jsx") == 0) {
    parser_language = tree_sitter_jsx();
  } else if (strcmp(language, "python") == 0) {
    parser_language = tree_sitter_python();
  } else if (strcmp(language, "scss") == 0) {
    parser_language = tree_sitter_scss();
  } else if (strcmp(language, "tsx") == 0) {
    parser_language = tree_sitter_tsx();
  } else if (strcmp(language, "typescript") == 0) {
    parser_language = tree_sitter_typescript();
  } else {
    env->ReleaseStringUTFChars(language_name, language);
    return;
  }

  ts_parser_set_language((TSParser*)parser, parser_language);
  env->ReleaseStringUTFChars(language_name, language);
}

JNIEXPORT void JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_parserSetLanguagePointer(
    JNIEnv* env, jclass self, jlong parser, jlong language) {
  ts_parser_set_language((TSParser*)parser, (TSLanguage*)language);
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_parserParseString(
    JNIEnv* env, jclass self, jlong parser, jstring source_string,
    jint length) {
  const char* source = env->GetStringUTFChars(source_string, 0);
  jlong result =
      (jlong)ts_parser_parse_string((TSParser*)parser, NULL, source, length);
  env->ReleaseStringUTFChars(source_string, source);
  return result;
}

JNIEXPORT jobject JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_treeCursorNew(JNIEnv* env,
                                                        jclass self,
                                                        jobject node) {
  return _marshalTreeCursor(env, ts_tree_cursor_new(_unmarshalNode(env, node)));
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitterJNI_treeDelete(
    JNIEnv* env, jclass self, jlong tree) {
  ts_tree_delete((TSTree*)tree);
}

JNIEXPORT jobject JNICALL
Java_ai_serenade_treesitter_TreeSitterJNI_treeRootNode(JNIEnv* env, jclass self,
                                                       jlong tree) {
  return _marshalNode(env, ts_tree_root_node((TSTree*)tree));
}
