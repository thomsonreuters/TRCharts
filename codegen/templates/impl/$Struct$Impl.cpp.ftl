[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#include <${cppPrivateFilePrefix}${name}Impl.hpp>

[#if fields?has_content]
${cppTemplateDeclaration!}
${cppNamespace}::${cppClassname}::${cppClassname}(void)
	:Generated${cppClassname}()
{
}

${cppTemplateDeclaration!}
${cppNamespace}::${cppClassname}::${cppClassname}([#list allFields as field]${field.type.cppConstReferenceType} ${field.name}[#if field_has_next], [/#if][/#list])
	:Generated${cppClassname}([#list allFields as field]${field.name}[#if field_has_next], [/#if][/#list])
{
}

[/#if]
[#list methods as method]
${""}[@cpp_method_implementation_signature cppDeclarationName method/]
{
	[#if method.returnType.returnable]return ${method.returnType.cppValueType}();[/#if]
}

[/#list]