[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_Marshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_Marshaller_hpp

#include <${jniCppFilePrefix}Support/Common.hpp>

namespace ${jniCppNamespace}
{
	template <typename T, typename U>
	class Marshaller
	{
	public:
		virtual ~Marshaller(void);

		virtual T marshall(JNIEnv * env, const U & value) const = 0;

		virtual U unmarshall(JNIEnv * env, const T & value) const = 0;

		virtual jvalue unmarshallToValue(JNIEnv * env, const T & in) const = 0;

		virtual T getFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID) const = 0;

		virtual void setFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID, const T & value) const = 0;

		virtual T callMethod(JNIEnv * env, jobject obj, jmethodID methodID, jvalue * args) const = 0;

		virtual T marshallBoxed(JNIEnv * env, const jobject & in) const = 0;

		virtual jobject unmarshallBoxed(JNIEnv * env, const T & in) const = 0;
	};

	template <typename T, typename U>
	Marshaller<T, U>::~Marshaller(void)
	{
	}
}

#endif