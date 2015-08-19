[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_Marshallers_hpp
#define ${jniCppHeaderGuardPrefix}Support_Marshallers_hpp

#include <${jniCppFilePrefix}Support/Marshaller.hpp>

[#list referencedTypeDependencies as dependency]
#include <${cppPublicFilePrefix}${dependency.name}.hpp>
[/#list]

namespace ${cppNamespace}
{
	[#list referencedTypeForwardDependencies as dependency]
	${dependency.cppDeclarationType} ${dependency.cppClassname};
	[/#list]
}

namespace ${jniCppNamespace}
{
	//namespace Marshallers
	//{
		[#list referencedTypes as type]
		[#if type.returnable && type.bound]
		const Marshaller<${type.cppValueType}, ${type.cppJniType}> & get${type.name?cap_first}Marshaller(void);

		[/#if]
		[/#list]
	//}
}

#endif