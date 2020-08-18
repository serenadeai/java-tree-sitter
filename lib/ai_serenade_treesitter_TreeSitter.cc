#include "ai_serenade_treesitter_TreeSitter.h"

#include <jni.h>
#include <string.h>
#include <tree_sitter/api.h>

static jint JNI_VERSION = JNI_VERSION_10;

static jclass _nodeClass;
static jfieldID _nodeContext0Field;
static jfieldID _nodeContext1Field;
static jfieldID _nodeContext2Field;
static jfieldID _nodeContext3Field;
static jfieldID _nodeIdField;
static jfieldID _nodeTreeField;

static jclass _treeCursorClass;
static jfieldID _treeCursorContext0Field;
static jfieldID _treeCursorContext1Field;
static jfieldID _treeCursorIdField;
static jfieldID _treeCursorTreeField;

#define _loadClass(VARIABLE, NAME)             \
  {                                            \
    jclass tmp;                                \
    tmp = env->FindClass(NAME);                \
    VARIABLE = (jclass)env->NewGlobalRef(tmp); \
    env->DeleteLocalRef(tmp);                  \
  }

#define _loadField(VARIABLE, CLASS, NAME, TYPE) \
  { VARIABLE = env->GetFieldID(CLASS, NAME, TYPE); }

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION) != JNI_OK) {
    return JNI_ERR;
  }

  _loadClass(_nodeClass, "ai/serenade/treesitter/Node");
  _loadField(_nodeContext0Field, _nodeClass, "context0", "I");
  _loadField(_nodeContext1Field, _nodeClass, "context1", "I");
  _loadField(_nodeContext2Field, _nodeClass, "context2", "I");
  _loadField(_nodeContext3Field, _nodeClass, "context3", "I");
  _loadField(_nodeIdField, _nodeClass, "id", "J");
  _loadField(_nodeTreeField, _nodeClass, "tree", "J");

  _loadClass(_treeCursorClass, "ai/serenade/treesitter/TreeCursor");
  _loadField(_treeCursorContext0Field, _treeCursorClass, "context0", "I");
  _loadField(_treeCursorContext1Field, _treeCursorClass, "context1", "I");
  _loadField(_treeCursorIdField, _treeCursorClass, "id", "J");
  _loadField(_treeCursorTreeField, _treeCursorClass, "tree", "J");

  return JNI_VERSION;
}

void JNI_OnUnload(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION);

  env->DeleteGlobalRef(_nodeClass);
  env->DeleteGlobalRef(_treeCursorClass);
}

jobject _marshalNode(JNIEnv* env, TSNode node) {
  jobject javaObject = env->AllocObject(_nodeClass);
  env->SetIntField(javaObject, _nodeContext0Field, node.context[0]);
  env->SetIntField(javaObject, _nodeContext1Field, node.context[1]);
  env->SetIntField(javaObject, _nodeContext2Field, node.context[2]);
  env->SetIntField(javaObject, _nodeContext3Field, node.context[3]);
  env->SetLongField(javaObject, _nodeIdField, (jlong)node.id);
  env->SetLongField(javaObject, _nodeTreeField, (jlong)node.tree);
  return javaObject;
}

TSNode _unmarshalNode(JNIEnv* env, jobject javaObject) {
  return (TSNode){
      {
          (uint32_t)env->GetIntField(javaObject, _nodeContext0Field),
          (uint32_t)env->GetIntField(javaObject, _nodeContext1Field),
          (uint32_t)env->GetIntField(javaObject, _nodeContext2Field),
          (uint32_t)env->GetIntField(javaObject, _nodeContext3Field),
      },
      (const void*)env->GetLongField(javaObject, _nodeIdField),
      (const TSTree*)env->GetLongField(javaObject, _nodeTreeField)};
}

jobject _marshalTreeCursor(JNIEnv* env, TSTreeCursor cursor) {
  jobject javaObject = env->AllocObject(_treeCursorClass);
  env->SetIntField(javaObject, _treeCursorContext0Field, cursor.context[0]);
  env->SetIntField(javaObject, _treeCursorContext1Field, cursor.context[1]);
  env->SetLongField(javaObject, _treeCursorIdField, (jlong)cursor.id);
  env->SetLongField(javaObject, _treeCursorTreeField, (jlong)cursor.tree);
  return javaObject;
}

TSTreeCursor _unmarshalTreeCursor(JNIEnv* env, jobject javaObject) {
  return (TSTreeCursor){
      (const void*)env->GetLongField(javaObject, _treeCursorTreeField),
      (const void*)env->GetLongField(javaObject, _treeCursorIdField),
      {
          (uint32_t)env->GetIntField(javaObject, _treeCursorContext0Field),
          (uint32_t)env->GetIntField(javaObject, _treeCursorContext1Field),
      }};
}

void _updateTreeCursor(JNIEnv* env, jobject cursor, TSTreeCursor* treeCursor) {
  env->SetIntField(cursor, _treeCursorContext0Field, treeCursor->context[0]);
  env->SetIntField(cursor, _treeCursorContext1Field, treeCursor->context[1]);
  env->SetLongField(cursor, _treeCursorIdField, (jlong)treeCursor->id);
  env->SetLongField(cursor, _treeCursorTreeField, (jlong)treeCursor->tree);
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeChild(
    JNIEnv* env, jclass self, jobject node, jint child) {
  return _marshalNode(
      env, ts_node_child(_unmarshalNode(env, node), (uint32_t)child));
}

JNIEXPORT jint JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeChildCount(
    JNIEnv* env, jclass self, jobject node) {
  return (jint)ts_node_child_count(_unmarshalNode(env, node));
}

JNIEXPORT jstring JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeString(
    JNIEnv* env, jclass self, jobject node) {
  char* nodeString = ts_node_string(_unmarshalNode(env, node));
  jstring result = env->NewStringUTF(nodeString);
  free(nodeString);
  return result;
}

JNIEXPORT jint JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeEndByte(
    JNIEnv* env, jclass self, jobject node) {
  return (jint)ts_node_end_byte(_unmarshalNode(env, node));
}

JNIEXPORT jint JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeStartByte(
    JNIEnv* env, jclass self, jobject node) {
  return (jint)ts_node_start_byte(_unmarshalNode(env, node));
}

JNIEXPORT jstring JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeType(
    JNIEnv* env, jclass self, jobject node) {
  const char* type = ts_node_type(_unmarshalNode(env, node));
  jstring result = env->NewStringUTF(type);
  return result;
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_TreeSitter_parserNew(JNIEnv* env, jclass self) {
  return (jlong)ts_parser_new();
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitter_parserDelete(
    JNIEnv* env, jclass self, jlong parser) {
  ts_parser_delete((TSParser*)parser);
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitter_parserSetLanguage(
    JNIEnv* env, jclass self, jlong parser, jlong language) {
  ts_parser_set_language((TSParser*)parser, (TSLanguage*)language);
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_TreeSitter_parserParseString(JNIEnv* env,
                                                         jclass self,
                                                         jlong parser,
                                                         jstring source_string,
                                                         jint length) {
  const char* source = env->GetStringUTFChars(source_string, 0);
  jlong result =
      (jlong)ts_parser_parse_string((TSParser*)parser, NULL, source, length);
  env->ReleaseStringUTFChars(source_string, source);
  return result;
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_treeCursorNew(
    JNIEnv* env, jclass self, jobject node) {
  return _marshalTreeCursor(env, ts_tree_cursor_new(_unmarshalNode(env, node)));
}

JNIEXPORT jstring JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorCurrentFieldName(
    JNIEnv* env, jclass self, jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  const char* name = ts_tree_cursor_current_field_name(&treeCursor);
  jstring result = env->NewStringUTF(name);
  return result;
}

JNIEXPORT jobject JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorCurrentNode(JNIEnv* env,
                                                             jclass self,
                                                             jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  TSNode current = ts_tree_cursor_current_node(&treeCursor);
  return _marshalNode(env, ts_tree_cursor_current_node(&treeCursor));
}

JNIEXPORT jboolean JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorGotoFirstChild(
    JNIEnv* env, jclass self, jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  bool result = ts_tree_cursor_goto_first_child(&treeCursor);
  _updateTreeCursor(env, cursor, &treeCursor);
  return (jboolean)result;
}

JNIEXPORT jboolean JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorGotoNextSibling(
    JNIEnv* env, jclass self, jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  bool result = ts_tree_cursor_goto_next_sibling(&treeCursor);
  _updateTreeCursor(env, cursor, &treeCursor);
  return (jboolean)result;
}

JNIEXPORT jboolean JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorGotoParent(JNIEnv* env,
                                                            jclass self,
                                                            jobject cursor) {
  TSTreeCursor treeCursor = _unmarshalTreeCursor(env, cursor);
  bool result = ts_tree_cursor_goto_parent(&treeCursor);
  _updateTreeCursor(env, cursor, &treeCursor);
  return (jboolean)result;
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitter_treeDelete(
    JNIEnv* env, jclass self, jlong tree) {
  ts_tree_delete((TSTree*)tree);
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_treeRootNode(
    JNIEnv* env, jclass self, jlong tree) {
  return _marshalNode(env, ts_tree_root_node((TSTree*)tree));
}
