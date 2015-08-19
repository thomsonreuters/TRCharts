[#ftl]
[#include "/templates/jni/_macros.ftl"/]
${copyright}
${autogenNote}

#include <${jniCppFilePrefix}Support/${name}StructMarshaller.hpp>
#include <${jniCppFilePrefix}Support/Marshallers.hpp>

using namespace ${jniCppNamespace};
using namespace ${cppNamespace};

namespace
{
	bool inited = false;
	jclass cls;
	jmethodID ctor;
	[#list allFields as field]
	jfieldID fid${field.name?cap_first};
	[/#list]

	void checkInited(JNIEnv * const env)
	{
		if(!::inited) {
			::inited = true;
			::cls = (jclass)env->NewGlobalRef(env->FindClass("${jniClassnamePrefix}${javaClassname}"));
			::ctor = env->GetMethodID(::cls, "<init>", "()V");
			[#list allFields as field]
			::fid${field.name?cap_first} = env->GetFieldID(cls, "${field.name}", "${field.type.jniSignature}");
			[/#list]
		}
	}
}

${cppClassname} ${name}StructMarshaller::marshall(JNIEnv * const env, const jobject & in) const
{
	::checkInited(env);
	${cppClassname} out;
	[#list allFields as field]
	out.${field.name} = [@jni_marshaller field.type/].getFieldValue(env, in, ::fid${field.name?cap_first});
	[/#list]
	return out;
}

jobject ${name}StructMarshaller::unmarshall(JNIEnv * const env, const ${cppClassname} & in) const
{
	::checkInited(env);
	jobject out = env->NewObject(::cls, ::ctor);
	[#list allFields as field]
	[@jni_marshaller field.type/].setFieldValue(env, out, ::fid${field.name?cap_first}, in.${field.name});
	[/#list]
	return out;
}

${cppClassname} ${name}StructMarshaller::getFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID) const
{
	return marshall(env, env->GetObjectField(obj, fieldID));
}

void ${name}StructMarshaller::setFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID, const ${cppClassname} & value) const
{
	env->SetObjectField(obj, fieldID, unmarshall(env, value));
}

${cppClassname} ${name}StructMarshaller::callMethod(JNIEnv * const env, const jobject obj, const jmethodID methodID, jvalue * const args) const
{
	return marshall(env, env->CallObjectMethodA(obj, methodID, args));
}