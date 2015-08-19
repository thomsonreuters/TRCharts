[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#ifndef ${cppHeaderGuardPrefix}${name}_cpp
#define ${cppHeaderGuardPrefix}${name}_cpp

#include <${cppPublicFilePrefix}${name}.hpp>
[#list forwardDependencies as dependency]
#include <${cppPublicFilePrefix}${dependency.name}.hpp>
[/#list]

${cppTemplateDeclaration!}
${cppNamespace}::Generated${cppClassname}${cppTemplateParameters!}::Generated${cppClassname}(void)
{
}

${cppTemplateDeclaration!}
${cppNamespace}::Generated${cppClassname}${cppTemplateParameters!}::~Generated${cppClassname}(void)
{
}

${cppTemplateDeclaration!}
std::shared_ptr<${cppDeclarationName}> ${cppNamespace}::Generated${cppClassname}${cppTemplateParameters!}::getSharedPtr(void)
{
	return std::dynamic_pointer_cast<${cppDeclarationName}>(shared_from_this());
}

${cppTemplateDeclaration!}
std::shared_ptr<const ${cppDeclarationName}> ${cppNamespace}::Generated${cppClassname}${cppTemplateParameters!}::getSharedPtr(void) const
{
	return std::dynamic_pointer_cast<const ${cppDeclarationName}>(shared_from_this());
}

#endif