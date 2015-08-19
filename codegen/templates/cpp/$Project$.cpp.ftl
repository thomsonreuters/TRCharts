[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#ifndef ${cppHeaderGuardPrefix}${name}_cpp
#define ${cppHeaderGuardPrefix}${name}_cpp

#include <${cppPublicFilePrefix}${name}.hpp>
#include <${cppPrivateFilePrefix}${name}Impl.hpp>

[#list fields as field]
${""}[@cpp_getter_implementation_signature cppNamespace, field, false/]
{
	return Impl::${field.type.getterPrefix}${field.name?cap_first}();
}

[#if !field.readonly]
${""}[@cpp_setter_implementation_signature cppNamespace, field, false/]
{
	Impl::set${field.name?cap_first}(value);
}

[/#if]
[/#list]
[#list methods as method]
${""}[@cpp_method_implementation_signature cppNamespace, method, false/]
{
	[#if method.returnType.returnable]return [/#if]Impl::[@cpp_method_call method/];
}

[/#list]
#endif