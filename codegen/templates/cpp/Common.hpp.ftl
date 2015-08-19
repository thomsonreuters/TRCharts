[#ftl]
${copyright}
${autogenNote}

#ifndef ${cppHeaderGuardPrefix}Common_hpp
#define ${cppHeaderGuardPrefix}Common_hpp

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

namespace ${cppNamespace}
{
	namespace Enums
	{
		template <typename T>
		size_t size(void);

		template <typename T>
		const char * name(T value);
	}
}

#endif