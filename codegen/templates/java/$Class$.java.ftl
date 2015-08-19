[#ftl]
[#include "/templates/java/_macros.ftl"]
${copyright}
${autogenNote}

package ${javaPackage};

import java.util.List;

${""}[@java_toplevel_comments /]

@SuppressWarnings("all")
public [#if !concrete]abstract [/#if]class ${javaClassname}[@java_template_parameters templateParameters/] extends [#if extend?exists]${extend.javaType}[#else]${javaBaseObject}[/#if][#if implement?has_content] implements [#list implement as i]${i.javaType}[#if i_has_next], [/#if][/#list][/#if]
{
	/**
	 * Default constructor
	 */

	[#if concrete]
	public ${javaClassname}()
	{
		this(true);
		setHandle(nativeCreate());
	}
	[#else]
	private ${javaClassname}()
	{
		this(true);
	}
	[/#if]

[#list fields + newlyBoundFields as field]
	${""}[@java_getter_comments field/]

	public[#if !(field.concrete && field.bound)] abstract[/#if] ${field.type.javaType} ${field.type.getterPrefix}${field.name?cap_first}()[#if field.concrete && field.bound]
	{
		return [@java_marshall field.type]native${field.type.getterPrefix?cap_first}${field.name?cap_first}(getHandle())[/@java_marshall];
	}[#else];[/#if]

[#if !field.readonly]
	${""}[@java_setter_comments field/]

	public[#if !(field.concrete && field.bound)] abstract[/#if] void set${field.name?cap_first}(final ${field.type.javaType} value)[#if field.concrete && field.bound]
	{
		nativeSet${field.name?cap_first}(getHandle(), [@java_unmarshall field.type]value[/@java_unmarshall]);
	}[#else];[/#if]

[/#if]
[/#list]
[#list methods + newlyBoundMethods as method]
	${""}[@java_method_comments method/]

	${""}[@java_method_declaration method true/][#if method.concrete && method.bound]
	{
		[#if method.returnType.returnable]return [@java_marshall method.returnType]native${method.name?cap_first}(getHandle()[#if method.parameters?has_content], [@java_call_parameters method/][/#if])[/@java_marshall];[#else]native${method.name?cap_first}(getHandle()[#if method.parameters?has_content], [@java_call_parameters method/][/#if]);[/#if]
	}[#else];[/#if]

[/#list]
	// need this to prevent default constructor in base classes
	/*package*/ ${javaClassname}(boolean dummy)
	{
		super(dummy);
	}

	[#if concrete]
	protected void onFinalize()
	{
		nativeDestroy(getHandle());
	}

	[/#if]
	[#if concrete]
	private final native long nativeCreate();
	private final native void nativeDestroy(long ptr);
	[/#if]
[#list fields + newlyBoundFields as field][#if field.concrete && field.bound]
	private final native ${field.type.javaJniType} native${field.type.getterPrefix?cap_first}${field.name?cap_first}(long ptr);
[#if !field.readonly]
	private final native void nativeSet${field.name?cap_first}(long ptr, ${field.type.javaJniType} value);
[/#if][/#if]
[/#list]
[#list methods + newlyBoundMethods as method][#if method.concrete && method.bound]
	private final native ${method.returnType.javaJniType} native${method.name?cap_first}(long ptr[#list method.parameters as param], ${param.type.javaJniType} ${param.name}[/#list]);
[/#if][/#list]
}
