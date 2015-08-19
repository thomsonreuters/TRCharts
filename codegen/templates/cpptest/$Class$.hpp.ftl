[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Test_${name}_hpp
#define ${cppHeaderGuardPrefix}Test_${name}_hpp

namespace ${cppNamespace}
{
	class ${cppClassname}Test : public [#if extend?exists]${cppClassname}Test[#else]CppUnit::TestCase[/#if]
	{
		[#if extend?exists]
		CPPUNIT_TEST_SUITE(${cppClassname}Test);
		[#else]
		CPPUNIT_TEST_SUB_SUITE(${cppClassname}Test, ${cppClassname}Test);
		[/#if]
		[#list fields as field]
		CPPUNIT_TEST(testInitialize${field.name?cap_first});
		[#if !field.readonly]
		CPPUNIT_TEST(testSet${field.name?cap_first});
		[/#if]
		[/#list]
		CPPUNIT_TEST_SUITE_END();

	public:
		[#list fields as field]
		void testInitialize${field.name?cap_first}(void) const;
		[#if !field.readonly]
		void testSet${field.name?cap_first}(void) const;
		[/#if]
		[/#list]
	}
}

#endif