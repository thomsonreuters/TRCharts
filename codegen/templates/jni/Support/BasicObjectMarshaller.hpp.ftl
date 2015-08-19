[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_BasicObjectMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_BasicObjectMarshaller_hpp

#include <${jniCppFilePrefix}Support/Marshaller.hpp>
#include <${jniCppFilePrefix}Support/Handle.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>

namespace ${jniCppNamespace}
{
	template <typename T, typename U>
	class BasicObjectMarshaller : public Marshaller<T, U>
	{
	public:
		virtual jvalue unmarshallToValue(JNIEnv * env, const T & in) const;

		virtual T getFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID) const;

		virtual void setFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID, const T & value) const;

		virtual T callMethod(JNIEnv * env, jobject obj, jmethodID methodID, jvalue * args) const;

		virtual T marshallBoxed(JNIEnv * env, const jobject & value) const;

		virtual jobject unmarshallBoxed(JNIEnv * env, const T & in) const;
	};

	template <typename T, typename U>
	jvalue BasicObjectMarshaller<T, U>::unmarshallToValue(JNIEnv * env, const T & in) const
	{
		jvalue value{};
		value.l = this->unmarshall(env, in);
		return value;
	}

	template <typename T, typename U>
	inline T BasicObjectMarshaller<T, U>::getFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID) const
	{
		return this->marshall(env, static_cast<U>(env->GetObjectField(obj, fieldID)));
	}

	template <typename T, typename U>
	inline void BasicObjectMarshaller<T, U>::setFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID, const T & value) const
	{
		env->SetObjectField(obj, fieldID, this->unmarshall(env, value));
	}

	template <typename T, typename U>
	inline T BasicObjectMarshaller<T, U>::callMethod(JNIEnv * const env, const jobject obj, const jmethodID methodID, jvalue * const args) const
	{
		return this->marshall(env, static_cast<U>(env->CallObjectMethodA(obj, methodID, args)));
	}

	template <typename T, typename U>
	inline T BasicObjectMarshaller<T, U>::marshallBoxed(JNIEnv * env, const jobject & in) const
	{
		return this->marshall(env, static_cast<U>(in));
	}

	template <typename T, typename U>
	inline jobject BasicObjectMarshaller<T, U>::unmarshallBoxed(JNIEnv * env, const T & in) const
	{
		return static_cast<jobject>(this->unmarshall(env, in));
	}
}

#endif