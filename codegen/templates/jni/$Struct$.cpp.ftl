[#ftl]
[#include "/templates/jni/_macros.ftl"/]
${copyright}
${autogenNote}

#include <${jniCppFilePrefix}${name}.hpp>
#include <${jniCppFilePrefix}Support/Marshallers.hpp>
#include <${jniCppFilePrefix}Support/Handle.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>
#include <${cppPublicFilePrefix}${name}.hpp>

using namespace ${jniCppNamespace};

[#list methods as method]
[#if method.bound]
${""}[@jni_method_declaration method /]
{
	[@jni_proc]
		[#if method.returnType.returnable]return [@jni_unmarshall method.returnType][#if !bound]I[/#if]${cppNamespacedClassname}::${method.name}([@jni_call_parameters method/])[/@jni_unmarshall];[#rt]
[#else][#if !bound]I[/#if]${cppNamespacedClassname}::${method.name}([@jni_call_parameters method/]);[/#if]
	[/@jni_proc]
}
[/#if]

[/#list]
