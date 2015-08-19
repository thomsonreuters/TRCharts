[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_Handle_hpp
#define ${jniCppHeaderGuardPrefix}Support_Handle_hpp

#include <${jniCppFilePrefix}Support/Common.hpp>
#include <${cppCodegenSupportFilePrefix}BaseObject.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>

#include <cassert>

namespace ${jniCppNamespace}
{
	class Handle
	{
	public:
		Handle(JNIEnv * env, ${cppCodegenSupportNamespace}::BaseObject * nativeObject, jobject hostObject);

		~Handle(void);

		template <typename T>
		std::shared_ptr<T> getNativeObject(JNIEnv * env) const;

		jobject getHostObject(JNIEnv * env) const;

	private:
		${cppCodegenSupportNamespace}::BaseObject * const nativeObject;
		const jobject weakHostObject;
		mutable std::weak_ptr<${cppCodegenSupportNamespace}::BaseObject> weakNativeObject;
	};
}

template <typename T>
std::shared_ptr<T> ${jniCppNamespace}::Handle::getNativeObject(JNIEnv * const env) const
{
	std::shared_ptr<${cppCodegenSupportNamespace}::BaseObject> sharedNativeObject = weakNativeObject.lock();
	if(!sharedNativeObject) {
		const jobject strongRef = env->NewGlobalRef(weakHostObject);
		sharedNativeObject.reset(nativeObject, [=](${cppCodegenSupportNamespace}::BaseObject * const ptr) -> void {
			JNIEnv * const env = Utils::getThreadEnv();
			assert(env);
			if(env) {
				env->DeleteGlobalRef(strongRef);
			}
		});
		weakNativeObject = sharedNativeObject;
	}
	return std::dynamic_pointer_cast<T>(sharedNativeObject);
}

#endif