[#ftl]
${copyright}
${autogenNote}

#ifndef ${cppHeaderGuardPrefix}${name}_hpp
#define ${cppHeaderGuardPrefix}${name}_hpp

#include <${cppPublicFilePrefix}Common.hpp>

namespace ${cppNamespace}
{
	enum class ${cppClassname}
	{
		[#list values as value]
		${value.cppRepresentation}[#if value_has_next],[/#if]
		[/#list]
	};

	namespace Enums
	{
		template <>
		inline size_t size<${cppClassname}>(void)
		{
			return ${values?size};
		}

		template <>
		inline const char * name<${cppClassname}>(${cppClassname} value)
		{
			switch(value) {
			[#list values as value]
			case ${cppClassname}::${value.cppRepresentation}:
				return "${value.cppRepresentation}";
			[/#list]
			default:
				return "?";
			}
		}
	}

	inline std::ostream & operator<<(std::ostream & to, const ${cppClassname} & from)
	{
		to << std::string(Enums::name(from));
		return to;
	}

}

#endif