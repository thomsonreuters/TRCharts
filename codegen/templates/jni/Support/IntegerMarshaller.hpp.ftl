[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_IntegerMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_IntegerMarshaller_hpp

#include <${jniCppFilePrefix}Support/Marshaller.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>

namespace ${jniCppNamespace}
{
	class IntegerMarshaller : public Marshaller<long, jlong>
	{
	public:
		virtual long marshall(JNIEnv * env, const jlong & in) const;

		virtual jlong unmarshall(JNIEnv * env, const long & in) const;

		virtual jvalue unmarshallToValue(JNIEnv * env, const long & in) const;

		virtual long getFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID) const;

		virtual void setFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID, const long & value) const;

		virtual long callMethod(JNIEnv * env, jobject obj, jmethodID methodID, jvalue * args) const;

		virtual long marshallBoxed(JNIEnv * env, const jobject & value) const;

		virtual jobject unmarshallBoxed(JNIEnv * env, const long & value) const;
	};

	inline long IntegerMarshaller::marshall(JNIEnv * const env, const jlong & in) const
	{
		return long(in);
	}

	inline jlong IntegerMarshaller::unmarshall(JNIEnv * const env, const long & in) const
	{
		return jlong(in);
	}

	inline jvalue IntegerMarshaller::unmarshallToValue(JNIEnv * env, const long & in) const
	{
		jvalue value{};
		value.j = unmarshall(env, in);
		return value;
	}

	inline long IntegerMarshaller::getFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID) const
	{
		return marshall(env, env->GetLongField(obj, fieldID));
	}

	inline void IntegerMarshaller::setFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID, const long & value) const
	{
		env->SetIntField(obj, fieldID, unmarshall(env, value));
	}

	inline long IntegerMarshaller::callMethod(JNIEnv * const env, const jobject obj, const jmethodID methodID, jvalue * const args) const
	{
		return marshall(env, env->CallLongMethodA(obj, methodID, args));
	}

	inline long IntegerMarshaller::marshallBoxed(JNIEnv * const env, const jobject & in) const
	{
		return marshall(env, Utils::unboxLong(env, in));
	}

	inline jobject IntegerMarshaller::unmarshallBoxed(JNIEnv * const env, const long & in) const
	{
		return Utils::boxLong(env, unmarshall(env, in));
	}
}

#endif