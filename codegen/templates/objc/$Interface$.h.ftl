[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

[#list dependencies as dependency]
#import <${dependency.objcIncludeFile}>
[/#list]
[#list forwardDependencies as dependency]
${dependency.objcDeclarationType} ${dependency.objcClassname};
[/#list]

[@objc_toplevel_comments/]
@protocol ${objcClassname}

[#list methods as method]
[@objc_method_comments method/]
[@objc_method_signature method/];

[/#list]
@end