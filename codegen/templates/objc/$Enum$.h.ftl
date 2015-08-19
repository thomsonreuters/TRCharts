[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

#include <Foundation/Foundation.h>

${""}[@objc_toplevel_comments /]
typedef NS_ENUM(NSInteger, ${objcClassname})
{
	[#list values as value]
	${""}[@objc_enum_value_comments value/]
	${value.objcRepresentation}[#if value_has_next],[/#if]

	[/#list]
};

typedef enum ${objcClassname} ${objcClassname};

/**
 * Get the size (element count) of the ${objcClassname} enum.
 *
 * @return The number of elements.
 */

static inline NSInteger ${objcClassname}_size(void)
{
	return ${values?size};
}

/**
 * Get the name of a given member of the ${objcClassname} enum.
 *
 * @param value The enum value.
 * @return The name (as per source code), or "?" if an invalid value is provided.
 */

static inline NSString * ${objcClassname}_name(${objcClassname} value)
{
	switch(value) {
	[#list values as value]
	case ${value.objcRepresentation}:
		return @"${value.objcRepresentation}";
	[/#list]
	default:
		return @"?";
	}
}
