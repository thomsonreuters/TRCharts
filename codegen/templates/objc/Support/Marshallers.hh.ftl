[#ftl]
${copyright}
${autogenNote}

[#list referencedTypeDependencies as dependency]
#import <${dependency.objcIncludeFile}>
[/#list]

#import <${cppPublicFilePrefix}Common.hpp>
[#list referencedTypeDependencies as dependency]
#import <${dependency.cppIncludeFile}>
[/#list]

[#list referencedTypeForwardDependencies as dependency]
${dependency.objcDeclarationType} ${dependency.objcClassname};
[/#list]

#import <${objcCodegenSupportFilePrefix}Marshaller.hh>
#import <${objcFilePrefix}Support/Common.hh>

namespace ${cppNamespace}
{
	[#list referencedTypeForwardDependencies as dependency]
	${dependency.cppDeclarationType} ${dependency.cppClassname};
	[/#list]
}

namespace ${objcSupportNamespace}
{
	[#list referencedTypes as type]
	[#if type.returnable && type.bound]
	const ${objcCodegenSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}> & get${type.name?cap_first}Marshaller(void);

	[/#if]
	[/#list]
}
