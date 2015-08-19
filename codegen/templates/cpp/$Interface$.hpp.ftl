[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#ifndef ${cppHeaderGuardPrefix}${name}_hpp
#define ${cppHeaderGuardPrefix}${name}_hpp

#include <${cppPublicFilePrefix}Common.hpp>
[#list dependencies as dependency]
#include <${dependency.cppIncludeFile}>
[/#list]

namespace ${cppNamespace}
{
	[#list forwardDependencies as dependency]
	${dependency.cppDeclarationType} ${dependency.cppClassname};
	[/#list]

	${cppTemplateDeclaration!}
	class ${cppClassname}[#if extend?has_content]: [#list extend as e]public ${e.cppRawType}[#if e_has_next], [/#if][/#list][/#if]
	{
	public:
		virtual ~${cppClassname}(void);

		[#list methods as method]
		${""}[@cpp_method_declaration_signature method/] = 0;

		[/#list]
	};
}

#endif