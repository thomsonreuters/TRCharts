[#ftl]

[#macro jni_marshaller type][#rt]
[#if type.bound]${jniCppNamespace}::get${type.name?cap_first}Marshaller()[#else]marshaller.get${type.name?cap_first}Marshaller()[/#if][#rt]
[/#macro]

[#macro jni_marshall type][#rt]
[@jni_marshaller type/].marshall(env, [#nested])[#rt]
[/#macro]

[#macro jni_unmarshall type][#rt]
[@jni_marshaller type/].unmarshall(env, [#nested])[#rt]
[/#macro]

[#macro jni_getter_declaration field][#rt]
JNIEXPORT ${field.type.cppJniType} JNICALL Java_${jniPackage}_${javaClassname}_native${field.type.getterPrefix?cap_first}${field.name?cap_first}(JNIEnv * env, jobject obj, jlong ptr)[#rt]
[/#macro]

[#macro jni_setter_declaration field][#rt]
JNIEXPORT void JNICALL Java_${jniPackage}_${javaClassname}_nativeSet${field.name?cap_first}(JNIEnv * env, jobject obj, jlong ptr, ${field.type.cppJniType} value)[#rt]
[/#macro]

[#macro jni_call_parameters method][#rt]
[#list method.parameters as param][#rt]
[@jni_marshall param.type]${param.name}[/@jni_marshall][#rt]
[#if param_has_next], [/#if][#rt]
[/#list][#rt]
[/#macro]

[#macro jni_method_declaration method][#rt]
JNIEXPORT ${method.returnType.cppJniType} JNICALL Java_${jniPackage}_${javaClassname}_native${method.name?cap_first}(JNIEnv * env, [#if method.instance]jobject obj, jlong ptr[#else]jclass cls[/#if][#rt]
[#list method.parameters as param][#rt]
, ${param.type.cppJniType} ${param.name}[#rt]
[/#list])[#rt]
[/#macro]

[#macro jni_read_handle][#rt]
${jniCppNamespace}::Handle * const handle = reinterpret_cast<${jniCppNamespace}::Handle *>(ptr);[#rt]
[/#macro]

[#macro jni_proc]
	try {
		Utils::threadEnter(env);
		Utils::EndScopeAction threadExitAction(Utils::threadExit);
[#nested]
	} catch (const std::exception & e) {
		Utils::throwJavaException(env, e.what());
	} catch (...) {
		Utils::throwJavaException(env, nullptr);
	}
[/#macro]