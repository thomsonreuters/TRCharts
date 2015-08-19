[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_BooleanMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_BooleanMarshaller_hpp

#include <${jniCppFilePrefix}Support/Marshaller.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>

namespace ${jniCppNamespace}
{
	class BooleanMarshaller : public Marshaller<bool, jboolean>
	{
	public:
		virtual bool marshall(JNIEnv * env, const jboolean & in) const;

		virtual jboolean unmarshall(JNIEnv * env, const bool & in) const;

		virtual jvalue unmarshallToValue(JNIEnv * env, const bool & in) const;

		virtual bool getFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID) const;

		virtual void setFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID, const bool & value) const;

		virtual bool callMethod(JNIEnv * env, jobject obj, jmethodID methodID, jvalue * args) const;

		virtual bool marshallBoxed(JNIEnv * env, const jobject & value) const;

		virtual jobject unmarshallBoxed(JNIEnv * env, const bool & value) const;
	};

	inline bool BooleanMarshaller::marshall(JNIEnv * const env, const jboolean & in) const
	{
		return bool(in);
	}

	inline jboolean BooleanMarshaller::unmarshall(JNIEnv * const env, const bool & in) const
	{
		return jboolean(in);
	}

	inline jvalue BooleanMarshaller::unmarshallToValue(JNIEnv * env, const bool & in) const
	{
		jvalue value{};
		value.z = unmarshall(env, in);
		return value;
	}

	inline bool BooleanMarshaller::getFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID) const
	{
		return marshall(env, env->GetBooleanField(obj, fieldID));
	}

	inline void BooleanMarshaller::setFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID, const bool & value) const
	{
		env->SetBooleanField(obj, fieldID, unmarshall(env, value));
	}

	inline bool BooleanMarshaller::callMethod(JNIEnv * const env, const jobject obj, const jmethodID methodID, jvalue * const args) const
	{
		return marshall(env, env->CallBooleanMethodA(obj, methodID, args));
	}

	inline bool BooleanMarshaller::marshallBoxed(JNIEnv * const env, const jobject & in) const
	{
		return marshall(env, Utils::unboxBoolean(env, in));
	}

	inline jobject BooleanMarshaller::unmarshallBoxed(JNIEnv * const env, const bool & in) const
	{
		return Utils::boxBoolean(env, unmarshall(env, in));
	}
}

#endif