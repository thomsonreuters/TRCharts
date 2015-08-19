[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#ifndef ${cppHeaderGuardPrefix}${name}_cpp
#define ${cppHeaderGuardPrefix}${name}_cpp

#include <${cppPublicFilePrefix}${name}.hpp>

${cppTemplateDeclaration!}
${cppDeclarationName}::~${cppClassname}(void)
{
}

#endif