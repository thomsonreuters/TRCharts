[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Impl_${name}Impl_hpp
#define ${cppHeaderGuardPrefix}Impl_${name}Impl_hpp

#include <${cppPublicFilePrefix}${name}.hpp>
[#list dependencies as dependency]
#include <${dependency.cppIncludeFile}>
[/#list]
#include <${cppPrivateFilePrefix}Common.hpp>

namespace ${cppNamespace}
{
	[#list forwardDependencies as dependency]
	${dependency.cppDeclarationType} ${dependency.cppClassname};
	[/#list]

	${cppTemplateDeclaration!}
	class ${cppClassname} : public Generated${cppClassname}${cppTemplateParameters!}
	{
	public:
		${cppClassname}(void);

		virtual ~${cppClassname}(void);

		[#list fields as field]
		${""}[@cpp_getter_declaration_signature field/];

		[#if !field.readonly]
		${""}[@cpp_setter_declaration_signature field/];

		[/#if]
		[/#list]
		[#list methods as method]
		[#if method.concrete]
		${""}[@cpp_method_declaration_signature method/][#if !method.concrete] = 0[/#if];

		[/#if]
		[/#list]
	private:
		[#list fields as field]
		[#if !field.instance]static [/#if]${field.type.cppValueType} ${field.name};
		[/#list]
	};
}

#endif