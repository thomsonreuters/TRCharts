[#ftl]
${copyright}
${autogenNote}

#import <${objcFilePrefix}Support/Marshallers.hh>
[#list referencedTypeForwardDependencies as dependency]
#import <${dependency.objcIncludeFile}>
[/#list]

#import <${cppPublicFilePrefix}Common.hpp>
[#list referencedTypeForwardDependencies as dependency]
#import <${dependency.cppIncludeFile}>
[/#list]

#import <${objcCodegenSupportFilePrefix}BooleanMarshaller.hh>
#import <${objcCodegenSupportFilePrefix}IntegerMarshaller.hh>
#import <${objcCodegenSupportFilePrefix}NumberMarshaller.hh>
#import <${objcCodegenSupportFilePrefix}StringMarshaller.hh>
#import <${objcCodegenSupportFilePrefix}ObjectMarshaller.hh>
#import <${objcCodegenSupportFilePrefix}EnumMarshaller.hh>
#import <${objcCodegenSupportFilePrefix}ListMarshaller.hh>

[#list referencedTypeDependencies + referencedTypeForwardDependencies as dependency]
[#if dependency.objcMarshallerIncludeFile??]
#import <${dependency.objcMarshallerIncludeFile}>
[/#if]
[/#list]

namespace
{
	[#list referencedTypes as type]
	[#if type.returnable && type.bound]
	std::shared_ptr<${objcCodegenSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}>> cached${type.name}Marshaller;
	[/#if]
	[/#list]
}

[#list referencedTypes as type]
[#if type.returnable && type.bound]
const ${objcCodegenSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}> & ${objcSupportNamespace}::get${type.name?cap_first}Marshaller(void)
{
	if(!::cached${type.name}Marshaller) {
		::cached${type.name}Marshaller.reset(new ${type.objcMarshaller});
	}
	return *::cached${type.name}Marshaller;
}

[/#if]
[/#list]
namespace
{
	// Need to force static init of all marshallers, else access to the marshalling layer has race conditions.
	const bool staticInitMarshallers = ([](void) -> bool {
		[#list referencedTypes as type]
		[#if type.returnable && type.bound]
		${objcSupportNamespace}::get${type.name?cap_first}Marshaller().init();
		[/#if]
		[/#list]
		return true;
	})();
}