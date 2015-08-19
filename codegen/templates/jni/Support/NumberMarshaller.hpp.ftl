[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_NumberMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_NumberMarshaller_hpp

#include <${jniCppFilePrefix}Support/Marshaller.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>

namespace ${jniCppNamespace}
{
	class NumberMarshaller : public Marshaller<double, jdouble>
	{
	public:
		virtual double marshall(JNIEnv * env, const jdouble & in) const;

		virtual jdouble unmarshall(JNIEnv * env, const double & in) const;

		virtual jvalue unmarshallToValue(JNIEnv * env, const double & in) const;

		virtual double getFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID) const;

		virtual void setFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID, const double & value) const;

		virtual double callMethod(JNIEnv * env, jobject obj, jmethodID methodID, jvalue * args) const;

		virtual double marshallBoxed(JNIEnv * env, const jobject & value) const;

		virtual jobject unmarshallBoxed(JNIEnv * env, const double & value) const;
	};

	inline double NumberMarshaller::marshall(JNIEnv * const env, const jdouble & in) const
	{
		return double(in);
	}

	inline jdouble NumberMarshaller::unmarshall(JNIEnv * const env, const double & in) const
	{
		return jdouble(in);
	}

	inline jvalue NumberMarshaller::unmarshallToValue(JNIEnv * env, const double & in) const
	{
		jvalue value{};
		value.d = unmarshall(env, in);
		return value;
	}

	inline double NumberMarshaller::getFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID) const
	{
		return marshall(env, env->GetDoubleField(obj, fieldID));
	}

	inline void NumberMarshaller::setFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID, const double & value) const
	{
		env->SetDoubleField(obj, fieldID, unmarshall(env, value));
	}

	inline double NumberMarshaller::callMethod(JNIEnv * const env, const jobject obj, const jmethodID methodID, jvalue * const args) const
	{
		return marshall(env, env->CallDoubleMethodA(obj, methodID, args));
	}

	inline double NumberMarshaller::marshallBoxed(JNIEnv * const env, const jobject & in) const
	{
		return marshall(env, Utils::unboxDouble(env, in));
	}

	inline jobject NumberMarshaller::unmarshallBoxed(JNIEnv * const env, const double & in) const
	{
		return Utils::boxDouble(env, unmarshall(env, in));
	}
}

#endif