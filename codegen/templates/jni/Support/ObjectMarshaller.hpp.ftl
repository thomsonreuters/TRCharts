[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_ObjectMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_ObjectMarshaller_hpp

#include <${jniCppFilePrefix}Support/Marshaller.hpp>
#include <${jniCppFilePrefix}Support/Handle.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>

namespace ${jniCppNamespace}
{
	template <typename T>
	class ObjectMarshaller : public BasicObjectMarshaller<std::shared_ptr<T>, jobject>
	{
	public:
		virtual std::shared_ptr<T> marshall(JNIEnv * env, const jobject & in) const;

		virtual jobject unmarshall(JNIEnv * env, const std::shared_ptr<T> & in) const;
	};

	template <typename T>
	std::shared_ptr<T> ObjectMarshaller<T>::marshall(JNIEnv * const env, const jobject & in) const
	{
		if(in) {
			const Handle * const handle = reinterpret_cast<Handle *>(Utils::getBaseObjectHandle(env, in));
			return handle->getNativeObject<T>(env);
		} else {
			return std::shared_ptr<T>();
		}
	}

	template <typename T>
	jobject ObjectMarshaller<T>::unmarshall(JNIEnv * const env, const std::shared_ptr<T> & in) const
	{
		if(in) {
			const Handle * const handle = static_cast<Handle *>(in->getHandle());
			return handle->getHostObject(env);
		} else {
			return nullptr;
		}
	}
}

#endif