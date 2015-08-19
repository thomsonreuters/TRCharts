[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

#import <${objcFilePrefix}${name}.h>
[#list forwardDependencies as dependency]
#import <${objcFilePrefix}${dependency.name}.h>
[/#list]

#import <${cppPublicFilePrefix}${name}.hpp>
[#list forwardDependencies as dependency]
#import <${cppPublicFilePrefix}${dependency.name}.hpp>
[/#list]

#import <${objcFilePrefix}Support/Marshallers.hh>
#import <${objcCodegenSupportFilePrefix}Handle.hh>

@implementation ${objcClassname}

-(${objcClassname}*)init {
	${""}[@objc_enter_method/]
[#if instance]
[#if concrete]
	self = [super initConcrete];
	${cppNamespace}::${cppClassname} * const obj = new ${cppNamespace}::${cppClassname}();
	${objcCodegenSupportNamespace}::Handle * const handle = new ${objcCodegenSupportNamespace}::Handle(obj, self);
	obj->setHandle(handle);
	[self setHandle:handle];
	return self;
[#else]
	@throw [NSException exceptionWithName:@"Init" reason:@"Cannot construct ${objcClassname} directly" userInfo:nil];
[/#if]
[#else]
	@throw [NSException exceptionWithName:@"Init" reason:@"Cannot construct ${objcClassname}" userInfo:nil];
[/#if]
}

[#list fields + newlyBoundFields as field]
[@objc_getter_signature field/] {
	${""}[@objc_enter_method/]
[#if field.bound]
[#if field.instance]
	${objcCodegenSupportNamespace}::Handle * const handle = static_cast<${objcCodegenSupportNamespace}::Handle *>([self handle]);
	std::shared_ptr<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}> obj = handle->getNativeObject<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}>();
	return [@objc_unmarshall field.type]obj->${field.type.getterPrefix}${field.name?cap_first}()[/@objc_unmarshall];
[#else]
	return [@objc_unmarshall field.type]${cppDeclarationName}::${field.type.getterPrefix}${field.name?cap_first}()[/@objc_unmarshall];
[/#if]
[#else]
	@throw [NSException exceptionWithName:@"Call" reason:@"Cannot call ${objcClassname}::${field.name} directly" userInfo:nil];
[/#if]
}

[#if !field.readonly]
[@objc_setter_signature field/] {
	${""}[@objc_enter_method/]
[#if field.bound]
[#if field.instance]
	${objcCodegenSupportNamespace}::Handle * const handle = static_cast<${objcCodegenSupportNamespace}::Handle *>([self handle]);
	std::shared_ptr<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}> obj = handle->getNativeObject<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}>();
	obj->set${field.name?cap_first}([@objc_marshall field.type]value[/@objc_marshall]);
[#else]
	${cppDeclarationName}::set${field.name?cap_first}([@objc_marshall field.type]value[/@objc_marshall]);
[/#if]
[#else]
	@throw [NSException exceptionWithName:@"Call" reason:@"Cannot call ${objcClassname}::set${field.name?cap_first} directly" userInfo:nil];
[/#if]
}

[/#if]
[/#list]
[#list methods + newlyBoundMethods as method]
[@objc_method_signature method/] {
	${""}[@objc_enter_method/]
[#if method.bound]
	${objcCodegenSupportNamespace}::Handle * const handle = static_cast<${objcCodegenSupportNamespace}::Handle *>([self handle]);
	std::shared_ptr<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}> obj = handle->getNativeObject<${cppNamespace}::[#if !bound]I[/#if]${cppClassname}>();
	[#if method.returnType.returnable]return [@objc_unmarshall method.returnType]obj->[@objc_native_call method/][/@objc_unmarshall];[#rt]
	[#else]obj->[@objc_native_call method/];[/#if]
[#else]
	@throw [NSException exceptionWithName:@"Call" reason:@"Cannot call ${objcClassname}::${method.name} directly" userInfo:nil];
[/#if]
}

[/#list]
@end