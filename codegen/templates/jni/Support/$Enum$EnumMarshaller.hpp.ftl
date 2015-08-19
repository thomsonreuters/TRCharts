[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_${name}EnumMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_${name}EnumMarshaller_hpp

#include <${jniCppFilePrefix}Support/BasicObjectMarshaller.hpp>
#include <${cppPublicFilePrefix}${name}.hpp>

namespace ${jniCppNamespace}
{
	class ${name}EnumMarshaller : public BasicObjectMarshaller<${cppNamespace}::${cppClassname}, jobject>
	{
	public:
		virtual ${cppNamespace}::${cppClassname} marshall(JNIEnv * env, const jobject & in) const;

		virtual jobject unmarshall(JNIEnv * env, const ${cppNamespace}::${cppClassname} & in) const;
	};
}

#endif