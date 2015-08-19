[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_StringMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_StringMarshaller_hpp

#include <${jniCppFilePrefix}Support/Marshaller.hpp>

namespace ${jniCppNamespace}
{
	class StringMarshaller : public BasicObjectMarshaller<std::string, jstring>
	{
	public:
		virtual std::string marshall(JNIEnv * env, const jstring & in) const;

		virtual jstring unmarshall(JNIEnv * env, const std::string & in) const;
	};

	inline std::string StringMarshaller::marshall(JNIEnv * const env, const jstring & in) const
	{
		const char* chars = env->GetStringUTFChars(in, NULL);
		std::string ret(chars);
		env->ReleaseStringUTFChars(in, chars);
		return ret;
	}

	inline jstring StringMarshaller::unmarshall(JNIEnv * const env, const std::string & in) const
	{
		jstring ret = env->NewStringUTF((const char*)in.c_str());
		return ret;
	}
}

#endif