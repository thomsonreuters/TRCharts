[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Test_${name}_cpp
#define ${cppHeaderGuardPrefix}Test_${name}_cpp

[#list fields as field]
void ${cppNamespace}::${cppClassname}Test::testInitialize${field.name?cap_first}(void) const
{
	const ${cppClassname} instance;
	const ${field.type.cppValueType} expected = ${field.cppDefaultValue};
	[#if field.returnReference]${field.type.cppConstReferenceType}[#else]const ${field.type.cppValueType}[/#if] actual = instance.${field.type.getterPrefix}${field.name?cap_first}();
	CPP_UNIT_ASSERT_EQUAL(expected, actual);
}

[#if !field.readonly]
void ${cppNamespace}::${cppClassname}Test::testSet${field.name?cap_first}(void) const
{
	const ${cppClassname} instance;
	const ${field.type.cppValueType} expected = TestUtils::randomValue<${field.type.cppValueType}>(${field.cppDefaultValue});
	instance.set${field.name?cap_first}(expected);
	[#if field.returnReference]${field.type.cppConstReferenceType}[#else]const ${field.type.cppValueType}[/#if] actual = instance.${field.type.getterPrefix}${field.name?cap_first}();
	CPP_UNIT_ASSERT_EQUAL(expected, actual);
}
[/#if]
[/#list]

#endif