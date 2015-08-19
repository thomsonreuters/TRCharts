[#ftl]
[#include "/templates/jni/_macros.ftl"/]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}${name}_hpp
#define ${jniCppHeaderGuardPrefix}${name}_hpp

#include <${jniCppFilePrefix}Support/Common.hpp>

#ifdef __cplusplus
extern "C" {
#endif
[#list methods as method]
[#if method.bound]
${""}[@jni_method_declaration method /];

[/#if]
[/#list]
#ifdef __cplusplus
}
#endif

#endif
