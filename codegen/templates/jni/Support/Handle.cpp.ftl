[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_Handle_cpp
#define ${jniCppHeaderGuardPrefix}Support_Handle_cpp

#include <${jniCppFilePrefix}Support/Handle.hpp>

#include <cassert>

${jniCppNamespace}::Handle::Handle(JNIEnv * const env, ${cppCodegenSupportNamespace}::BaseObject * const nativeObject, const jobject hostObject)
	:nativeObject(nativeObject), weakHostObject(env->NewWeakGlobalRef(hostObject))
{
}

${jniCppNamespace}::Handle::~Handle(void)
{
	delete nativeObject;
}

jobject ${jniCppNamespace}::Handle::getHostObject(JNIEnv * env) const
{
	return env->NewLocalRef(weakHostObject);
}

#endif