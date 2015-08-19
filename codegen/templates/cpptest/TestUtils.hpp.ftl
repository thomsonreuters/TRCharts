[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}

#ifndef ${cppHeaderGuardPrefix}Test_TestUtils_hpp
#define ${cppHeaderGuardPrefix}Test_TestUtils_hpp

namespace ${cppNamespace}
{
	namespace TestUtils
	{
		template <typename T>
		void nonDefaultValue(const T & defaultValue);

		template <typename T>
		void nonDefaultValue<std::shared_ptr<T>>(const std::shared_ptr<T> & defaultValue)
		{
			return std::make_shared<T>();
		}

		template <typename T>
		void nonDefaultValue<std::vector<T>>(const std::vector<T> & defaultValue)
		{
			std::vector<T> result = defaultValue;
			result.push_back(nonDefaultValue(T()));
			return result;
		}
	}
}

#endif