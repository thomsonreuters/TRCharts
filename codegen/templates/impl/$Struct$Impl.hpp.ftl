[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Impl_${name}Impl_hpp
#define ${cppHeaderGuardPrefix}Impl_${name}Impl_hpp

#include <${cppPublicFilePrefix}${name}.hpp>

namespace ${cppNamespace}
{
	${cppTemplateDeclaration!}
	struct ${cppClassname} : public Generated${cppClassname}
	{
		[#if fields?has_content]
		${cppClassname}(void);

		${cppClassname}([#list allFields as field]${field.type.cppConstReferenceType} ${field.name}[#if field_has_next], [/#if][/#list]);

		[/#if]
		[#list methods as method]
		${""}[@cpp_method_declaration_signature method/];

		[/#list]
	};
}

#endif