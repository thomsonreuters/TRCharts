[#ftl strip_text=true]

[#macro java_method_declaration method isImplementation][#rt]
[#if isImplementation]public [#if method.instance][#if !(method.concrete && method.bound)]abstract [/#if][#else]static [/#if][/#if]${method.returnType.javaType} ${method.name}([#rt]
[#list method.parameters as param][#rt]
[#if isImplementation]final [/#if]${param.type.javaType} ${param.name}[#rt]
[#if param_has_next], [/#if][#rt]
[/#list])[#rt]
[/#macro]

[#macro java_call_parameters method][#rt]
[#list method.parameters as param][#rt]
[@java_unmarshall param.type]${param.name}[/@java_unmarshall][#if param_has_next], [/#if][#rt]
[/#list][#rt]
[/#macro]

[#macro java_marshall type][#rt]
[#if type.javaType!=type.javaJniType](${type.javaType})[/#if][#nested][#rt]
[/#macro]

[#macro java_unmarshall type][#rt]
[#nested][#rt]
[/#macro]

[#macro java_template_parameters templateParameters=[]][#rt]
[#if templateParameters?has_content][#rt]
<[#list templateParameters as param][#rt]
${param.name}[#if param_has_next], [/#if][#rt]
[/#list][#rt]>
[/#if][#rt]
[/#macro]


[#macro java_comment_body comment indent = ''][#rt]
[#if comment.type='warning']
${indent} * <p>
${indent} * ${comment.wrapBody(73, '<b>WARNING:</b> ', indent + ' * ')}
${indent} * </p>
[#elseif comment.type='note']
${indent} * <p>
${indent} * ${comment.wrapBody(73, '<b>NOTE:</b> ', indent + ' * ')}
${indent} * </p>
[#elseif comment.type='see']
${indent} * ${comment.wrapBody(73, '@see ', indent + ' * ')}
[#else]
${indent} * <p>
${indent} * ${comment.wrapBody(73, '', indent + ' * ')}
${indent} * </p>
[/#if]
[/#macro]

[#macro java_toplevel_comment_body comment][#rt]
[@java_comment_body comment/]
[/#macro]

[#macro java_toplevel_comments]/**
[#list javaComments as comment]
[@java_toplevel_comment_body comment/]
[/#list]
 */[#rt]
[/#macro]

[#macro java_getter_comments field]/**
	 * Get the ${field.description!field.name}.
[#list field.javaComments as comment]
[@java_comment_body comment '	'/]
[/#list]
	 * @return The current ${field.description!field.name}.
	 */[#rt]
[/#macro]

[#macro java_setter_comments field]/**
	 * Set the ${field.description!field.name}.
[#list field.javaComments as comment]
[@java_comment_body comment '	'/]
[/#list]
	 * @param value The new ${field.description!field.name}.
	 */[#rt]
[/#macro]

[#macro java_method_comments method]/**
[#list method.javaComments as comment]
[@java_comment_body comment '	'/]
[/#list]
[#list method.parameters as param]	 * @param ${param.name} [#list param.javaComments as comment]${comment.body}[/#list]
[/#list]
[#if method.returnType.returnable]	 * @return The result.
[/#if]
	 */[#rt]
[/#macro]

[#macro java_enum_value_comments enumValue]/**
[#list enumValue.javaComments as comment]
[@java_comment_body comment '	'/]
[/#list]
	 */[#rt]
[/#macro]