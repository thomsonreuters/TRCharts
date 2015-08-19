[#ftl]
${copyright}
${autogenNote}

#include <${jniCppFilePrefix}Support/${name}EnumMarshaller.hpp>
#include <${jniCppFilePrefix}Support/Marshallers.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>

using namespace ${jniCppNamespace};
using namespace ${cppNamespace};

namespace
{
	bool inited = false;
	jclass cls;
	jobject values[${values?size}];

	void checkInited(JNIEnv * const env)
	{
		if(!::inited) {
			::inited = true;
			::cls = (jclass)env->NewGlobalRef(env->FindClass("${jniClassnamePrefix}${javaClassname}"));
			const char * valueNames[${values?size}] = {
				[#list values as value]
				"${value.name?upper_case}"[#if value_has_next],[/#if]
				[/#list]
			};
			for(size_t i = 0; i != ${values?size}; ++i) {
				const jfieldID fid = env->GetStaticFieldID(::cls, valueNames[i], "L${jniClassnamePrefix}${javaClassname};");
				::values[i] = env->NewGlobalRef(env->GetStaticObjectField(::cls, fid));
			}
		}
	}
}

${cppClassname} ${name}EnumMarshaller::marshall(JNIEnv * const env, const jobject & in) const
{
	return static_cast<${cppClassname}>(Utils::enumOrdinal(env, in));
}

jobject ${name}EnumMarshaller::unmarshall(JNIEnv * const env, const ${cppClassname} & in) const
{
	::checkInited(env);
	return values[static_cast<int>(in)];
}