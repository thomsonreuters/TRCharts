[#ftl]
[#include "/templates/java/_macros.ftl"]
${copyright}
${autogenNote}

package ${javaPackage};

${""}[@java_toplevel_comments /]

public enum ${javaClassname}
{
	[#list values as value]
	${""}[@java_enum_value_comments value/]

	${value.javaRepresentation}[#if value_has_next],[/#if]

	[/#list]
}
