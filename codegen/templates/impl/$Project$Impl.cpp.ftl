[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Impl_${name}Impl_cpp
#define ${cppHeaderGuardPrefix}Impl_${name}Impl_cpp

#include <${cppPrivateFilePrefix}${name}Impl.hpp>

[#list fields as field]
${cppTemplateDeclaration!}
${""}[@cpp_getter_implementation_signature cppNamespace + "::Impl", field, false/]
{
	return ${field.name};
}

[#if !field.readonly]
${cppTemplateDeclaration!}
${""}[@cpp_setter_implementation_signature cppNamespace + "::Impl", field, false/]
{
	${field.name} = value;
}

[/#if]
[/#list]
[#list methods as method]
${cppTemplateDeclaration!}
${""}[@cpp_method_implementation_signature cppNamespace + "::Impl", method, false/]
{
	[#if method.returnType.returnable]return ${method.returnType.cppValueType}();[/#if]
}

[/#list]

[#list fields as field]
[#if !field.instance]
${field.type.cppValueType} ${cppNamespace}::Impl::${field.name} = ${field.type.cppValueType}();
[/#if]
[/#list]
#endif