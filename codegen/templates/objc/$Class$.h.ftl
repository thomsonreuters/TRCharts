[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

[#list dependencies as dependency]
#import <${dependency.objcIncludeFile}>
[/#list]
[#if !extend?exists]
#import <${objcCodegenSupportFilePrefix}BaseObject.h>
[/#if]
[#list forwardDependencies as dependency]
${dependency.objcDeclarationType} ${dependency.objcClassname};
[/#list]

[@objc_class_comments/]
@interface ${objcClassname} : [#if extend?exists]${extend.objcRawType}[#else]${objcBase}[/#if][#if implement?has_content]<[#list implement as i]${i.interfaceDef.objcClassname}[#if i_has_next], [/#if][/#list]>[/#if]

[#if fields?has_content]
/** @name Fields */

[#list fields as field]
[@objc_getter_comments field/]
[@objc_getter_signature field/];
[#if !field.readonly]

[@objc_setter_comments field/]
[@objc_setter_signature field/];
[/#if]

[/#list]
[/#if]
[#if methods?has_content]
/** @name Methods */

[#list methods as method]
[@objc_method_comments method/]
[@objc_method_signature method/];

[/#list]
[/#if]
@end