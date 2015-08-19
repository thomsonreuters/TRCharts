[#ftl]
[#include "/templates/java/_macros.ftl"]
${copyright}
${autogenNote}

package ${javaPackage};

import java.util.List;

${""}[@java_toplevel_comments /]

@SuppressWarnings("all")
public interface ${javaClassname}[@java_template_parameters templateParameters/][#list extend as e] extends ${e.javaType}[#if e_has_next], [/#if][/#list]
{
[#list methods as method]
	${""}[@java_method_comments method/]

	${""}[@java_method_declaration method false/];

[/#list]
}
