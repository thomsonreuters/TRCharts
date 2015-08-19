[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

#import <${objcFilePrefix}${name}.h>

#import <${cppPublicFilePrefix}${name}.hpp>

#import <${objcFilePrefix}Support/Marshallers.hh>

@implementation ${objcClassPrefix}${name}

-(${objcClassPrefix}${name}*)init {
	@throw [NSException exceptionWithName:@"Init" reason:@"Cannot construct ${objcClassPrefix}${name}" userInfo:nil];
}

[#list fields as field]
[@objc_getter_signature field + {"instance":false}/] {
	return [@objc_unmarshall field.type]${cppNamespace}::${field.type.getterPrefix}${field.name?cap_first}()[/@objc_unmarshall];
}

[#if !field.readonly]
[@objc_setter_signature field + {"instance":false}/] {
	${cppNamespace}::set${field.name?cap_first}([@objc_marshall field.type]value[/@objc_marshall]);
}

[/#if]
[/#list]
+(void)markQueue:(dispatch_queue_t)queue
{
	${objcSupportNamespace}::markQueue(queue);
}

+(void)unmarkQueue:(dispatch_queue_t)queue
{
	${objcSupportNamespace}::unmarkQueue(queue);
}

+(BOOL)isQueueMarked
{
	return ${objcSupportNamespace}::isQueueMarked();
}

+(void)enableQueueVerification:(BOOL)yes
{
	${objcSupportNamespace}::enableQueueVerification(yes);
}
@end