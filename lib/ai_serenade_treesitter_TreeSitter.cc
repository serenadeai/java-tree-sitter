#include "ai_serenade_treesitter_TreeSitter.h"

#include <jni.h>
#include <string.h>
#include <tree_sitter/api.h>

struct TreeCursorNode {
  const char* type;
  const char* name;
  uint32_t startByte;
  uint32_t endByte;
};

static jint JNI_VERSION = JNI_VERSION_10;

static jclass _nodeClass;
static jfieldID _nodeContext0Field;
static jfieldID _nodeContext1Field;
static jfieldID _nodeContext2Field;
static jfieldID _nodeContext3Field;
static jfieldID _nodeIdField;
static jfieldID _nodeTreeField;

static jclass _treeCursorNodeClass;
static jfieldID _treeCursorNodeTypeField;
static jfieldID _treeCursorNodeNameField;
static jfieldID _treeCursorNodeStartByteField;
static jfieldID _treeCursorNodeEndByteField;

static jclass _positionClass;
static jfieldID _positionRow;
static jfieldID _positionColumn;

static jclass _queryCreationClass;
static jfieldID _queryCreationClassPointer;
static jfieldID _queryCreationClassErrorType;
static jfieldID _queryCreationClassErrorOffset;

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

  // load class node
  _loadClass(_nodeClass, "ai/serenade/treesitter/Node");
  _loadField(_nodeContext0Field, _nodeClass, "context0", "I");
  _loadField(_nodeContext1Field, _nodeClass, "context1", "I");
  _loadField(_nodeContext2Field, _nodeClass, "context2", "I");
  _loadField(_nodeContext3Field, _nodeClass, "context3", "I");
  _loadField(_nodeIdField, _nodeClass, "id", "J");
  _loadField(_nodeTreeField, _nodeClass, "tree", "J");

  // load class tree cursor
  _loadClass(_treeCursorNodeClass, "ai/serenade/treesitter/TreeCursorNode");
  _loadField(_treeCursorNodeTypeField, _treeCursorNodeClass, "type",
             "Ljava/lang/String;");
  _loadField(_treeCursorNodeNameField, _treeCursorNodeClass, "name",
             "Ljava/lang/String;");
  _loadField(_treeCursorNodeStartByteField, _treeCursorNodeClass, "startByte",
             "I");
  _loadField(_treeCursorNodeEndByteField, _treeCursorNodeClass, "endByte", "I");

  // load class position
  _loadClass(_positionClass, "ai/serenade/treesitter/Position");
  _loadField(_positionRow, _positionClass, "row","I");
  _loadField(_positionColumn, _positionClass, "column","I");


  _loadClass(_queryCreationClass, "ai/serenade/treesitter/query/internals/QueryCreationResult");
  _loadField(_queryCreationClassPointer, _queryCreationClass, "pointer", "J");
  _loadField(_queryCreationClassErrorType, _queryCreationClass, "errorType", "I");
  _loadField(_queryCreationClassErrorOffset, _queryCreationClass, "errorOffset", "I");

  return JNI_VERSION;
}

void JNI_OnUnload(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION);

  env->DeleteGlobalRef(_nodeClass);
  env->DeleteGlobalRef(_treeCursorNodeClass);
  env->DeleteGlobalRef(_positionClass);
}

jobject _marshalPosition(JNIEnv* env, TSPoint point) {
  jobject javaObject = env->AllocObject(_positionClass);
  env->SetIntField(javaObject, _positionRow, point.row);
  env->SetIntField(javaObject, _positionColumn, point.column / 2);
  return javaObject;
}

jobject _marshalQueryCreationResult(JNIEnv* env, jlong pointer, int error_type, uint32_t error_offset) {
  jobject javaObject = env->AllocObject(_queryCreationClass);
  env->SetIntField(javaObject, _queryCreationClassPointer, pointer);
  env->SetIntField(javaObject, _queryCreationClassErrorType, error_type);
  return javaObject;
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

jobject _marshalTreeCursorNode(JNIEnv* env, TreeCursorNode node) {
  jobject javaObject = env->AllocObject(_treeCursorNodeClass);
  env->SetObjectField(javaObject, _treeCursorNodeTypeField,
                      env->NewStringUTF(node.type));
  env->SetObjectField(javaObject, _treeCursorNodeNameField,
                      env->NewStringUTF(node.name));
  env->SetIntField(javaObject, _treeCursorNodeStartByteField, node.startByte);
  env->SetIntField(javaObject, _treeCursorNodeEndByteField, node.endByte);
  return javaObject;
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeChild(
    JNIEnv* env, jclass self, jobject node, jint child) {
  return _marshalNode(
      env, ts_node_child(_unmarshalNode(env, node), (uint32_t)child));
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeChildByFieldName(
    JNIEnv* env, jclass self, jobject node, jstring fieldName) {
  const char* fieldNameChars = env->GetStringUTFChars(fieldName, NULL);

  TSNode ts_node = ts_node_child_by_field_name(_unmarshalNode(env, node), fieldNameChars, strlen(fieldNameChars));

  if (!ts_node_is_null(ts_node)) {
      jobject res = _marshalNode(env, ts_node);
      env->ReleaseStringUTFChars(fieldName, fieldNameChars);
      return res;
  }
  return NULL;
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeStartPosition(
    JNIEnv* env, jclass self, jobject node) {

  TSNode ts_node = _unmarshalNode(env, node);

  return _marshalPosition(env, ts_node_start_point(ts_node));
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeEndPosition(
    JNIEnv* env, jclass self, jobject node) {

  TSNode ts_node = _unmarshalNode(env, node);
  return _marshalPosition(env, ts_node_end_point(ts_node));
}

JNIEXPORT jint JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeChildCount(
    JNIEnv* env, jclass self, jobject node) {
  return (jint)ts_node_child_count(_unmarshalNode(env, node));
}

JNIEXPORT jboolean JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeHasError(
    JNIEnv* env, jclass self, jobject node) {
    // use conditional to avoid conversion from bool to jboolean (unsigned char)
    return ts_node_has_error(_unmarshalNode(env, node)) ? JNI_TRUE : JNI_FALSE;
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
  return (jint)ts_node_end_byte(_unmarshalNode(env, node)) / 2;
}

JNIEXPORT jint JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeStartByte(
    JNIEnv* env, jclass self, jobject node) {
  return (jint)ts_node_start_byte(_unmarshalNode(env, node)) / 2;
}

JNIEXPORT jstring JNICALL Java_ai_serenade_treesitter_TreeSitter_nodeType(
    JNIEnv* env, jclass self, jobject node) {
  const char* type = ts_node_type(_unmarshalNode(env, node));
  jstring result = env->NewStringUTF(type);
  return result;
}

JNIEXPORT jlong JNICALL
Java_ai_serenade_treesitter_TreeSitter_parserNew(JNIEnv* env, jclass self) {
  jlong res = (jlong)ts_parser_new();
  return res;
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitter_parserDelete(
    JNIEnv* env, jclass self, jlong parser) {
  ts_parser_delete((TSParser*)parser);
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitter_parserSetLanguage(
    JNIEnv* env, jclass self, jlong parser, jlong language) {
  ts_parser_set_language((TSParser*)parser, (TSLanguage*)language);
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_TreeSitter_parserParseBytes(
    JNIEnv* env, jclass self, jlong parser, jbyteArray source_bytes,
    jint length) {
  jbyte* source = env->GetByteArrayElements(source_bytes, NULL);
  jlong result = (jlong)ts_parser_parse_string_encoding(
      (TSParser*)parser, NULL, reinterpret_cast<const char*>(source), length, TSInputEncodingUTF16);
  env->ReleaseByteArrayElements(source_bytes, source, JNI_ABORT);
  return result;
}

JNIEXPORT jlong JNICALL Java_ai_serenade_treesitter_TreeSitter_treeCursorNew(
    JNIEnv* env, jclass self, jobject node) {
  TSTreeCursor* cursor =
      new TSTreeCursor(ts_tree_cursor_new(_unmarshalNode(env, node)));
  return (jlong)cursor;
}

JNIEXPORT jstring JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorCurrentFieldName(
    JNIEnv* env, jclass self, jlong cursor) {
  const char* name = ts_tree_cursor_current_field_name((TSTreeCursor*)cursor);
  jstring result = env->NewStringUTF(name);
  return result;
}

JNIEXPORT jobject JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorCurrentNode(JNIEnv* env,
                                                             jclass self,
                                                             jlong cursor) {
  return _marshalNode(env, ts_tree_cursor_current_node((TSTreeCursor*)cursor));
}

JNIEXPORT jobject JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorCurrentTreeCursorNode(
    JNIEnv* env, jclass self, jlong cursor) {
  TSNode node = ts_tree_cursor_current_node((TSTreeCursor*)cursor);
  return _marshalTreeCursorNode(
      env,
      (TreeCursorNode){ts_node_type(node),
                       ts_tree_cursor_current_field_name((TSTreeCursor*)cursor),
                       ts_node_start_byte(node) / 2, ts_node_end_byte(node) / 2});
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitter_treeCursorDelete(
    JNIEnv* env, jclass self, jlong cursor) {
  delete (TSTreeCursor*)cursor;
}

JNIEXPORT jboolean JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorGotoFirstChild(JNIEnv* env,
                                                                jclass self,
                                                                jlong cursor) {
  return (jboolean)ts_tree_cursor_goto_first_child((TSTreeCursor*)cursor);
}

JNIEXPORT jboolean JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorGotoNextSibling(JNIEnv* env,
                                                                 jclass self,
                                                                 jlong cursor) {
  return (jboolean)ts_tree_cursor_goto_next_sibling((TSTreeCursor*)cursor);
}

JNIEXPORT jboolean JNICALL
Java_ai_serenade_treesitter_TreeSitter_treeCursorGotoParent(JNIEnv* env,
                                                            jclass self,
                                                            jlong cursor) {
  return (jboolean)ts_tree_cursor_goto_parent((TSTreeCursor*)cursor);
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitter_treeDelete(
    JNIEnv* env, jclass self, jlong tree) {
  ts_tree_delete((TSTree*)tree);
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_treeRootNode(
    JNIEnv* env, jclass self, jlong tree) {
  return _marshalNode(env, ts_tree_root_node((TSTree*)tree));
}

JNIEXPORT jobject JNICALL Java_ai_serenade_treesitter_TreeSitter_queryNew(
    JNIEnv* env, jclass self, jlong language, jstring code) {
  const TSLanguage* lang = (TSLanguage*) language;
  const char* code_chars = env->GetStringUTFChars(code, NULL);
  uint32_t error_offset;
  TSQueryError error_type;
  TSQuery* q = ts_query_new(
      lang,
      code_chars,
      strlen(code_chars),
      &error_offset,
      &error_type);

  return _marshalQueryCreationResult(env, (jlong)q, error_type, error_offset);
}

JNIEXPORT void JNICALL Java_ai_serenade_treesitter_TreeSitter_queryDelete(
    JNIEnv* env, jclass self, jlong pointer) {
    // FIXME - understand why this does not work
//  ts_query_delete((TSQuery*) pointer);
}