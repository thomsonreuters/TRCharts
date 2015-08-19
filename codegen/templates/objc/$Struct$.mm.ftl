[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

#import <${objcFilePrefix}${name}.h>
#import <${objcFilePrefix}Support/Marshallers.hh>

@implementation ${objcClassname}

-(${objcClassname} *)init
{
	self = [super init];
	if(self) {
		[#list allFields as field]
		self.${field.name} = ${field.objcDefaultValue};
		[/#list]
	}
	return self;
}

[#if fields?has_content]
+(${objcClassname} *)[#list allFields as field]${field.name}:(${field.type.objcValueType})${field.name}[#if field_has_next] [/#if][/#list]
{
	${objcClassname} * const result = [[${objcClassname} alloc] init];
	[#list allFields as field]
	result.${field.name} = ${field.name};
	[/#list]
	return result;
}

[/#if]
[#list methods as method]
${""}[@objc_method_signature method/]
{
	[#if method.returnType.returnable]return [@objc_unmarshall method.returnType]${cppDeclarationName}::[@objc_native_call method/][/@objc_unmarshall];[#rt]
	[#else]${cppDeclarationName}::[@objc_native_call method/];[/#if]
}

[/#list]
-(BOOL)isEqual:(id)anObject
{
	if(anObject == nil || ! [anObject isKindOfClass:[${objcClassname} class]]) {
		return NO;
	}
	${objcClassname} * other = anObject;
	BOOL result = [#if extend?exists][super isEqual:other][#else]YES[/#if];
[#list fields as field]
[#if field.type.objcPrimitive]
	result = result && (self.${field.name} == other.${field.name});
[#else]
	if(self.${field.name} == nil) {
		result = result && (other.${field.name} == nil);
	} else {
		result = result && [self.${field.name} isEqual:other.${field.name}];
	}
[/#if]
[/#list]
	return result;
}

-(NSUInteger)hash
{
	NSUInteger result = [#if extend?exists][super hash][#else]7[/#if];
[#list fields as field]
[#if field.type.objcPrimitive]
    result = 31 * result + (NSUInteger)self.${field.name};
[#else]
    result = 31 * result + [self.${field.name} hash];
[/#if]
[/#list]
	return result;
}

-(id)copyWithZone:(NSZone *)zone
{
	${objcClassname} * copy = [#if extend?exists][super copyWithZone:zone][#else][[self class] allocWithZone:zone][/#if];
[#list fields as field]
[#if field.type.objcPrimitive]
	copy.${field.name} = self.${field.name};
[#else]
	copy.${field.name} = [self.${field.name} copyWithZone:zone];
[/#if]
[/#list]
	return copy;
}

-(NSString*)description
{
	return [NSString stringWithFormat:@"${objcClassname}[[#if extend??]%@[#if fields?has_content], [/#if][/#if][#list fields as field]%${field.type.objcFormatPlaceholder}[#if field_has_next], [/#if][/#list]]"[#if extend??], [super description][/#if][#list fields as field], self.${field.name}[/#list]];
}

@end