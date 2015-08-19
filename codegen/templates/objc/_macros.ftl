[#ftl]
[#macro objc_method_signature method][#rt]
[#if method.instance]-[#else]+[/#if](${method.returnType.objcValueType})${method.name}[#rt]
[#list method.parameters as param][#rt]
[#if param_index!=0] ${param.name}[/#if][#rt]
:(${param.type.objcValueType})${param.name}[#rt]
[/#list][#rt]
[/#macro]

[#macro objc_getter_signature field][#rt]
[#if field.instance]-[#else]+[/#if](${field.type.objcValueType})${field.name}[#rt]
[/#macro]

[#macro objc_setter_signature field][#rt]
[#if field.instance]-[#else]+[/#if](void)set${field.name?cap_first}:(${field.type.objcValueType})value[#rt]
[/#macro]

[#macro objc_marshaller type][#rt]
[#if type.bound]${objcSupportNamespace}::get${type.name?cap_first}Marshaller()[#else]get${type.name?cap_first}Marshaller()[/#if][#rt]
[/#macro]

[#macro objc_marshall type][#rt]
[@objc_marshaller type/].marshall([#nested])[#rt]
[/#macro]

[#macro objc_unmarshall type][#rt]
[@objc_marshaller type/].unmarshall([#nested])[#rt]
[/#macro]

[#macro objc_native_call method][#rt]
${method.name}([#rt]
[#list method.parameters as param][#rt]
[@objc_marshall param.type]${param.name}[/@objc_marshall][#rt]
[#if param_has_next], [/#if][#rt]
[#lt][/#list])[#rt]
[/#macro]

[#macro objc_call method][#rt]
${method.name}[#rt]
[#list method.parameters as param][#rt]
[#if param_index!=0] ${param.name}[/#if][#rt]
:[@objc_unmarshall param.type]${param.name}[/@objc_unmarshall][#rt]
[#lt][/#list][#rt]
[/#macro]

[#macro objc_comment_body comment prefix = ''][#rt]
 * ${comment.wrapBody(77, prefix, ' * ')}
[/#macro]

[#macro objc_comment comment][#rt]
[#if comment.type='warning']
[@objc_comment_body comment '@warning '/]
[#elseif comment.type='note']
[@objc_comment_body comment '@note '/]
[#elseif comment.type='see']
[@objc_comment_body comment '@see '/]
[#else]
[@objc_comment_body comment/]
[/#if]
[/#macro]

[#macro objc_comments comments]/**
[#list comments as comment]
[@objc_comment comment/]
 *
[/#list]
 */
[/#macro]

[#macro objc_toplevel_comments][@objc_comments objcComments/][/#macro]

[#macro objc_class_comments][@objc_comments objcComments/][/#macro]

[#macro objc_struct_comments][@objc_comments objcComments/][/#macro]

[#macro objc_property_comments field]/**
 * The ${field.description!field.name}.
[#list field.objcComments as comment]
 *
[@objc_comment comment/]
[/#list]
 */
[/#macro]

[#macro objc_struct_constructor_comments]/**
 * Create a ${name} instance with provided values.
 *
[#list allFields as field] * @param ${field.name} The ${field.description!field.name}.
[/#list]
 */
[/#macro]

[#macro objc_getter_comments field]/**
[#list field.objcComments as comment]
[@objc_comment comment/]
 *
[/#list]
 * @return The current ${field.description!field.name}.
[#if !field.readonly]
 * @see set${field.name?cap_first}:
[/#if]
 */
[/#macro]


[#macro objc_setter_comments field]/**
[#list field.objcComments as comment]
[@objc_comment comment/]
 *
[/#list]
 * @param value The new ${field.description!field.name}.
 * @see ${field.name}
 */
[/#macro]

[#macro objc_method_comments method]/**
[#list method.objcComments as comment]
[@objc_comment comment/]
 *
[/#list]
[#list method.parameters as param] * @param ${param.name} [#list param.objcComments as comment]${comment.body}[/#list]
[/#list]
[#if method.returnType.returnable] * @return The result.
[/#if]
 */
[/#macro]

[#macro objc_enter_method][#rt]
${objcSupportNamespace}::verifyCurrentQueue();[#rt]
[/#macro]


[#macro objc_enum_value_comments enumValue]/**
[#list enumValue.objcComments as comment]
	${""}[@objc_comment_body comment/][/#list]	 */[#rt]
[/#macro]