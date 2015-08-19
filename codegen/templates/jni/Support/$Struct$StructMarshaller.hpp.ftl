[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_${name}StructMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_${name}StructMarshaller_hpp

#include <${jniCppFilePrefix}Support/BasicObjectMarshaller.hpp>
#include <${cppPublicFilePrefix}${name}.hpp>

namespace ${jniCppNamespace}
{
	class ${name}StructMarshaller : public BasicObjectMarshaller<${cppNamespace}::${cppClassname}, jobject>
	{
	public:
		virtual ${cppNamespace}::${cppClassname} marshall(JNIEnv * env, const jobject & in) const;

		virtual jobject unmarshall(JNIEnv * env, const ${cppNamespace}::${cppClassname} & in) const;

		virtual ${cppNamespace}::${cppClassname} getFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID) const;

		virtual void setFieldValue(JNIEnv * env, jobject obj, jfieldID fieldID, const ${cppNamespace}::${cppClassname} & value) const;

		virtual ${cppNamespace}::${cppClassname} callMethod(JNIEnv * env, jobject obj, jmethodID methodID, jvalue * args) const;
	};
}

#endif