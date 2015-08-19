[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

#include <Foundation/Foundation.h>

[#list dependencies as dependency]
#import <${dependency.objcIncludeFile}>
[/#list]
[#list forwardDependencies as dependency]
${dependency.objcDeclarationType} ${dependency.objcClassname};
[/#list]

[@objc_struct_comments/]
@interface ${objcClassname} : [#if extend?exists]${extend.objcRawType}[#else]NSObject <NSCopying>[/#if]

[#if fields?has_content]
/** @name Fields */
[#list fields as field]
[@objc_property_comments field/]
@property ${field.type.objcValueType} ${field.name};

[/#list]
[/#if]
/** @name Methods */
/**
 * Default init.
 *
 * @return Initialized object.
 */
-(${objcClassname} *)init;

[#if fields?has_content]
[@objc_struct_constructor_comments/]
+(${objcClassname} *)[#list allFields as field]${field.name}:(${field.type.objcValueType})${field.name}[#if field_has_next] [/#if][/#list];

[/#if]
[#list methods as method]
[@objc_method_comments method/]
${""}[@objc_method_signature method/];

[/#list]
/**
 * Test for equality (uses all struct fields)
 *
 * @param anObject Object to compare to.
 * @return True if the objects are equal.
 */
-(BOOL)isEqual:(id)anObject;

/**
 * Calculate the hash code (uses all struct fields)
 *
 * @return The hash code.
 */
-(NSUInteger)hash;

/**
 * Create a copy (uses all struct fields)
 *
 * @param zone Memory zone.
 * @return A copy.
 */
-(id)copyWithZone:(NSZone *)zone;

/**
 * Create a string description (uses all struct fields)
 *
 * @return The description.
 */
-(NSString*)description;

@end