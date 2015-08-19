[#ftl]
[#include "/templates/java/_macros.ftl"]
${copyright}
${autogenNote}

package ${javaPackage};

import java.util.List;

${""}[@java_toplevel_comments /]

@SuppressWarnings("all")
public class ${javaClassname}[#if extend??] extends ${extend.javaType}[/#if]
{
	[#list fields as field]
	private ${field.type.javaType} ${field.name};
	[/#list]

	[#if fields?has_content]
	/**
	 * Initialize a ${name} with default values.
	 */
	public ${javaClassname}()
	{
	}

	/**
	 * Initialize a ${name} with provided values.
	 *
[#list allFields as field]	 * @param ${field.name} The ${field.description!field.name}.
[/#list]
	 */

	public ${javaClassname}([#list allFields as field]${field.type.javaType} ${field.name}[#if field_has_next], [/#if][/#list])
	{
		[#if inheritedFields?has_content]
		super([#list inheritedFields as field]${field.name}[#if field_has_next], [/#if][/#list]);
		[/#if]
		[#list fields as field]
		this.${field.name} = ${field.name};
		[/#list]
	}

	[/#if]
	[#list fields as field]
	${""}[@java_getter_comments field/]

	public final ${field.type.javaType} get${field.name?cap_first}()
	{
		return this.${field.name};
	}

	[#if !field.readonly]
	${""}[@java_setter_comments field/]

	public final void set${field.name?cap_first}(final ${field.type.javaType} value)
	{
		this.${field.name} = value;
	}

	[/#if]
	[/#list]
	@Override
	public String toString()
	{
		return "${javaClassname} {" +
		[#if extend??]
				"super=" + super.toString()[#if fields?has_content] + ", "[/#if] +
		[/#if]
		[#list fields as field]
				"${field.name}=" + ${field.name}[#if field_has_next] + ", "[/#if] +
		[/#list]
				"}";
	}

	@Override
	public boolean equals(final Object other)
	{
		if(this == other) return true;[#if extend??]
		if(!(super.equals(this))) return false;[/#if]
		if(!(other instanceof ${javaClassname})) return false;

		final ${javaClassname} tmp = (${javaClassname})other;

		[#list fields as field]
		[#if field.type.javaPrimitive]
		if(!(this.${field.name} == tmp.${field.name})) return false;
		[#else]
		if(!((this.${field.name} == null) ? (tmp.${field.name} == null) : this.${field.name}.equals(tmp.${field.name}))) return false;
		[/#if]
		[/#list]

		return true;
	}

	@Override
	public int hashCode()
	{
		int result = [#if extend??]super.hashCode()[#else]7[/#if];

		[#list fields as field]
		[#if field.type.javaPrimitive]
		result = 31 * result + ((${field.type.javaContainerType})${field.name}).hashCode();
		[#else]
		result = 31 * result + ((this.${field.name} == null) ? 0 : this.${field.name}.hashCode());
		[/#if]
		[/#list]

		return result;
	}

	[#if methods?has_content]
	[#list methods as method]
	${""}[@java_method_comments method/]

	${""}[@java_method_declaration method true/]
	{
		[#if method.returnType.returnable]return [@java_marshall method.returnType]native${method.name?cap_first}([@java_call_parameters method/])[/@java_marshall];[#else]native${method.name?cap_first}([@java_call_parameters method/]);[/#if]
	}

	[/#list]

	[#list methods as method]
	private static final native ${method.returnType.javaJniType} native${method.name?cap_first}([#list method.parameters as param]${param.type.javaJniType} ${param.name}[#if param_has_next], [/#if][/#list]);
	[/#list]
	[/#if]
}
