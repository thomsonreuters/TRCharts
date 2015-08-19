[#ftl]
${copyright}
${autogenNote}

#import <${objcFilePrefix}${name}.h>

namespace ${objcSupportNamespace}
{
	[#list referencedTypes as type]
	[#if type.returnable && type.bound]
	${type.objcValueType} get${type.name?cap_first}TestValue(${type.objcValueType} defaultValue);

	[/#if]
	[/#list]
}
