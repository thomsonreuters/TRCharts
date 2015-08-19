[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_${name}InterfaceMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_${name}InterfaceMarshaller_hpp

#include <${jniCppFilePrefix}Support/BasicObjectMarshaller.hpp>
#include <${cppPublicFilePrefix}${name}.hpp>

namespace ${jniCppNamespace}
{
	${cppTemplateDeclaration!}
	class ${name}InterfaceMarshaller : public BasicObjectMarshaller<std::shared_ptr<${cppDeclarationName}>, jobject>
	{
	public:
		[#if templateParameters??]
		${name}InterfaceMarshaller([#list templateParameters! as param]const Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.cppJniType}> & marshaller${param.name?cap_first}[#if param_has_next], [/#if][/#list]);

		[/#if]
		virtual std::shared_ptr<${cppDeclarationName}> marshall(JNIEnv * env, const jobject & in) const;

		virtual jobject unmarshall(JNIEnv * env, const std::shared_ptr<${cppDeclarationName}> & in) const;

		[#list referencedTypes as type]
		[#if type.returnable && !type.bound]
		const Marshaller<${type.cppValueType}, ${type.cppJniType}> & get${type.name}Marshaller(void) const;

		[/#if]
		[/#list]
	private:
		[#list templateParameters! as param]
		const Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.cppJniType}> & marshaller${param.name?cap_first};
		[/#list]
		[#list referencedTypes as type]
		[#if type.returnable && !type.bound && !type.templateParameter]
		mutable std::shared_ptr<Marshaller<${type.cppValueType}, ${type.cppJniType}>> cached${type.name}Marshaller;
		[/#if]
		[/#list]

		static bool inited;
		static jclass cls;
		[#list methods as method]
		static jmethodID mid${method.name?cap_first};
		[/#list]

		static void checkInited(JNIEnv * env);

		class Proxy;
	};
}

#endif