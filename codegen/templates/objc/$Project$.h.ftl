[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

/*[#list interfaces as interface]
@protocol ${interface.objcClassname};
[/#list]
[#list classes as class]
@class ${class.objcClassname};
[/#list]*/

[#list enums as enum]
#import <${objcFilePrefix}${enum.name}.h>
[/#list]

[#list structs as struct]
#import <${objcFilePrefix}${struct.name}.h>
[/#list]
[#list interfaces as interface]
#import <${objcFilePrefix}${interface.name}.h>
[/#list]
[#list templateInterfaces as interface]
#import <${objcFilePrefix}${interface.name}.h>
[/#list]
[#list classes as class]
#import <${objcFilePrefix}${class.name}.h>
[/#list]
[#list templateClasses as class]
#import <${objcFilePrefix}${class.name}.h>
[/#list]

/**
 * Namespace/collection of top-level static methods.
 */

@interface ${objcClassPrefix}${name} : NSObject

/**
 * Throws an exception (should not try to construct).
 */

-(${objcClassPrefix}${name}*)init;

[#list fields as field]
[@objc_getter_comments field + {"instance":false}/]
[@objc_getter_signature field + {"instance":false}/];
[#if !field.readonly]
[@objc_setter_comments field + {"instance":false}/]
[@objc_setter_signature field + {"instance":false}/];
[/#if]

[/#list]
[#list methods as method]
[@objc_method_comments method + {"instance":false}/]
[@objc_method_signature method + {"instance":false}/];

[/#list]
/**
 * For debug purposes, marks the parameter queue as 'ok' for calling library methods.
 *
 * @param queue Queue to mark.
 *
 */
+(void)markQueue:(dispatch_queue_t)queue;

/**
 * For debug purposes, undoes markQueue.
 *
 * @param queue Queue to unmark.
 *
 */
+(void)unmarkQueue:(dispatch_queue_t)queue;

/**
 * For debug purposes, check to see if the current queue is marked.
 *
 * @return True if the current is marked.
 *
 */
+(BOOL)isQueueMarked;


/**
 * For debug purposes, turns on queue verification (all library calls will verify that the current queue is marked).
 *
 * @param yes True to enable verification, false to disable.
 *
 */
+(void)enableQueueVerification:(BOOL)yes;
@end
