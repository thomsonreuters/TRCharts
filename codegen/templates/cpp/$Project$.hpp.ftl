[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#ifndef ${cppHeaderGuardPrefix}${name}_hpp
#define ${cppHeaderGuardPrefix}${name}_hpp

#include <${cppPublicFilePrefix}Common.hpp>

namespace ${cppNamespace}
{
	[#list interfaces as interface]
	class ${interface.cppClassname};
	[/#list]
	[#list classes as class]
	class ${class.cppClassname};
	[/#list]
}

[#list enums as enum]
#include <${cppPublicFilePrefix}${enum.name}.hpp>
[/#list]

[#list interfaces as interface]
#include <${cppPublicFilePrefix}${interface.name}.hpp>
[/#list]
[#list classes as class]
#include <${cppPublicFilePrefix}${class.name}.hpp>
[/#list]

namespace ${cppNamespace}
{
	[#list fields as field]
	${""}[@cpp_getter_declaration_signature field false/];

	[#if !field.readonly]
	${""}[@cpp_setter_declaration_signature field false/];

	[/#if]
	[/#list]
	[#list methods as method]
	${""}[@cpp_method_declaration_signature method false/];

	[/#list]
}

#endif