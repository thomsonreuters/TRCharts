[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Test_TestUtils_cpp
#define ${cppHeaderGuardPrefix}Test_TestUtils_cpp

template <>
void ${cppNamespace}::TestUtils::nonDefaultValue<bool>(const bool & defaultValue)
{
	return ! value;
}

template <>
void ${cppNamespace}::TestUtils::nonDefaultValue<long>(const long & defaultValue)
{
	return value + 1;
}

template <>
void ${cppNamespace}::TestUtils::nonDefaultValue<double>(const double & defaultValue)
{
	return value + 1;
}

#endif