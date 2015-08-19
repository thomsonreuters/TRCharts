[#ftl]
${copyright}
${autogenNote}

#import "TestUtils.hh"

[#macro getBooleanTestValue type]
	return !defaultValue;
[/#macro]

[#macro getBooleanTestValue type]
	return !defaultValue;
[/#macro]

[#macro getIntegerTestValue type]
	return defaultValue + 1;
[/#macro]

[#macro getNumberTestValue type]
	return defaultValue + 1.0;
[/#macro]

[#macro getEnumTestValue type]
	return defaultValue;
[/#macro]

[#macro getStringTestValue type]
	return [defaultValue stringByAppendingString:@"test"];
[/#macro]

[#macro getListTestValue type]
	return defaultValue;//[defaultValue arrayByAddingObject:${type.valueType.getObjcValue(null)}];
[/#macro]

[#macro getClassTestValue type]
[#if type.classDef.concrete]
	return [[${type.classDef.objcClassname} alloc] init];
[#else]
	return defaultValue;
[/#if]
[/#macro]

[#macro getTemplateClassTestValue type]
	return defaultValue;
[/#macro]

[#macro getStructTestValue type]
	return defaultValue;
[/#macro]

[#macro getTemplateStructTestValue type]
	return defaultValue;
[/#macro]

[#macro getInterfaceTestValue type]
	return defaultValue;
[/#macro]

[#macro getTemplateInterfaceTestValue type]
	return defaultValue;
[/#macro]


[#list referencedTypes as type]
[#if type.returnable && type.bound]
${type.objcValueType} ${objcSupportNamespace}::get${type.name?cap_first}TestValue(${type.objcValueType} defaultValue)
{
[#assign macroName="get" + type.basicType + "TestValue"]
${""}[@.vars[macroName] type/]}

[/#if]
[/#list]
