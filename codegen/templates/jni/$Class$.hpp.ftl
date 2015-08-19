[#ftl]
[#include "/templates/jni/_macros.ftl"/]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}${name}_hpp
#define ${jniCppHeaderGuardPrefix}${name}_hpp

#include <${jniCppFilePrefix}Support/Common.hpp>

#ifdef __cplusplus
extern "C" {
#endif

[#if concrete]
JNIEXPORT jlong JNICALL Java_${jniPackage}_${javaClassname}_nativeCreate(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL Java_${jniPackage}_${javaClassname}_nativeDestroy(JNIEnv *env, jobject obj, jlong ptr);

[/#if]
[#list fields + newlyBoundFields as field]
[@jni_getter_declaration field/];

[#if !field.readonly]
[@jni_setter_declaration field/];

[/#if]
[/#list]
[#list methods + newlyBoundMethods as method]
${""}[@jni_method_declaration method /];

[/#list]
#ifdef __cplusplus
}
#endif
#endif