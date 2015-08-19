[#ftl]
[#include "/templates/jni/_macros.ftl"/]
${copyright}
${autogenNote}

#include <${jniCppFilePrefix}${name}.hpp>
#include <${jniCppFilePrefix}Support/Marshallers.hpp>
#include <${jniCppFilePrefix}Support/Handle.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>
#include <${cppPublicFilePrefix}${name}.hpp>

using namespace ${jniCppNamespace};

[#if concrete]
JNIEXPORT jlong JNICALL Java_${jniPackage}_${javaClassname}_nativeCreate(JNIEnv *env, jobject obj)
{
	[@jni_proc]
		${cppNamespacedClassname} * const nativeObject = new ${cppNamespacedClassname}();
		Handle * const handle = new Handle(env, nativeObject, obj);
		nativeObject->setHandle(handle);
		return reinterpret_cast<jlong>(handle);
	[/@jni_proc]
}

JNIEXPORT void JNICALL Java_${jniPackage}_${javaClassname}_nativeDestroy(JNIEnv *env, jobject obj, jlong ptr)
{
	[@jni_proc]
		${""}[@jni_read_handle/]
		delete handle;
	[/@jni_proc]
}

[/#if]
[#list fields + newlyBoundFields as field]
[#if field.bound]
${""}[@jni_getter_declaration field/]
{
	[@jni_proc]
		${""}[@jni_read_handle/]
		return [@jni_unmarshall field.type]handle->getNativeObject<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}>(env)->${field.type.getterPrefix}${field.name?cap_first}()[/@jni_unmarshall];
	[/@jni_proc]
}

[#if !field.readonly]
${""}[@jni_setter_declaration field/]
{
	[@jni_proc]
		${""}[@jni_read_handle/]
		handle->getNativeObject<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}>(env)->set${field.name?cap_first}([@jni_marshall field.type]value[/@jni_marshall]);
	[/@jni_proc]
}
[/#if]
[/#if]
[/#list]

[#list methods + newlyBoundMethods as method]
[#if method.bound]
${""}[@jni_method_declaration method /]
{
	[@jni_proc]
		${""}[@jni_read_handle/]
		[#if method.returnType.returnable]return [@jni_unmarshall method.returnType]handle->getNativeObject<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}>(env)->${method.name}([@jni_call_parameters method/])[/@jni_unmarshall];[#rt]
[#else]handle->getNativeObject<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}>(env)->${method.name}([@jni_call_parameters method/]);[/#if]
	[/@jni_proc]
}
[/#if]

[/#list]
