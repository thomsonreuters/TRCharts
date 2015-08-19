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

#include <ostream>

namespace ${cppNamespace}
{
	${cppTemplateDeclaration!}
	struct ${cppClassname};
	[#list forwardDependencies as dependency]
	${dependency.cppDeclarationType} ${dependency.cppClassname};
	[/#list]

	${cppTemplateDeclaration!}
	struct Generated${cppClassname}[#if extend??]: public ${extend.cppRawType}[/#if]
	{
		[#list fields as field]
		${field.type.cppValueType} ${field.name};
		[/#list]

		[#if fields?has_content]
		Generated${cppClassname}(void);

		Generated${cppClassname}([#list allFields as field]${field.type.cppConstReferenceType} ${field.name}[#if field_has_next], [/#if][/#list]);

		[/#if]
		bool operator==(const Generated${cppClassname} & other) const;

		bool operator!=(const Generated${cppClassname} & other) const;
	};

	${cppTemplateDeclaration!}
	std::ostream & operator<<(std::ostream & to, const Generated${cppClassname} & from);
}

#include <${cppPublicFilePrefix}Impl/${cppClassname}Impl.hpp>

#endif