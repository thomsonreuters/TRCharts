[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Impl_${name}Impl_hpp
#define ${cppHeaderGuardPrefix}Impl_${name}Impl_hpp

#include <${cppPublicFilePrefix}${name}.hpp>

namespace ${cppNamespace}
{
	namespace Impl
	{
		[#list fields as field]
		${""}[@cpp_getter_declaration_signature field, false/];

		[#if !field.readonly]
		${""}[@cpp_setter_declaration_signature field, false/];

		[/#if]
		[/#list]
		[#list methods as method]
		${""}[@cpp_method_declaration_signature method, false/];

		[/#list]
		[#list fields as field]
		extern ${field.type.cppValueType} ${field.name};
		[/#list]
	}
}

#endif