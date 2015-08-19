[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Impl_${name}Impl_cpp
#define ${cppHeaderGuardPrefix}Impl_${name}Impl_cpp

#include <${cppPrivateFilePrefix}${name}Impl.hpp>
[#list forwardDependencies as dependency]
#include <${dependency.cppIncludeFile}>
[/#list]

${cppTemplateDeclaration!}
${cppDeclarationName}::${cppClassname}(void)
	:Generated${cppClassname}()[#list fields as field][#if field.instance], ${field.name}()[/#if][/#list]
{
}

${cppTemplateDeclaration!}
${cppDeclarationName}::~${cppClassname}(void)
{
}

[#list fields as field]
${cppTemplateDeclaration!}
${""}[@cpp_getter_implementation_signature cppDeclarationName, field/]
{
[#if instance]
	return this->${field.name};
[#else]
	return Impl::${field.name};
[/#if]
}

[#if !field.readonly]
${cppTemplateDeclaration!}
${""}[@cpp_setter_implementation_signature cppDeclarationName, field/]
{
[#if instance]
	this->${field.name} = value;
[#else]
	Impl::${field.name} = value;
[/#if]
}

[/#if]
[/#list]
[#list methods as method]
[#if method.concrete]
${cppTemplateDeclaration!}
${""}[@cpp_method_implementation_signature cppDeclarationName, method/]
{
	[#if method.returnType.returnable]return ${method.returnType.cppValueType}();[/#if]
}

[/#if]
[/#list]

[#list fields as field]
[#if !field.instance]
${cppTemplateDeclaration!}
${field.type.cppValueType} ${cppDeclarationName}::${field.name} = ${field.type.cppValueType}();
[/#if]
[/#list]
#endif