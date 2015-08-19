[#ftl]
${copyright}
${autogenNote}

#import "${name}GeneratedTests.h"
#import <${objcFilePrefix}${name}.h>
#import "TestUtils.hh"

#import <XCTest/XCTestAssertions.h>

@implementation ${objcClassname}GeneratedTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

[#if instance]
-(id)createInstance
{
	[#if concrete]
	return [[${objcClassname} alloc] init];
	[#else]
	// class is abstract, tests will be run only in subclasses
	return nil;
	[/#if]
}
[/#if]

[#list fields as field]
- (void) testInitializeField${field.name?cap_first}
{
	[#if instance]
	${objcClassname} * instance = [self createInstance];
	if(instance) {
		${field.type.objcValueType} expected = ${field.objcDefaultValue};
		${field.type.objcValueType} actual = [instance ${field.name}];
		[#if field.type.objcPrimitive]
		XCTAssertEqual(expected, actual);
		[#else]
		XCTAssertEqualObjects(expected, actual);
		[/#if]
	}
	[/#if]
}

[/#list]
[#list fields + newlyBoundFields as field]
[#if field.bound & !field.readonly]
- (void) testSetField${field.name?cap_first}
{
	[#if instance]
	${objcClassname} * instance = [self createInstance];
	if(instance) {
		${field.type.objcValueType} original = [instance ${field.name}];
		${field.type.objcValueType} expected = ${objcSupportNamespace}::get${field.type.name}TestValue(original);
		[instance set${field.name?cap_first}:expected];
		${field.type.objcValueType} actual = [instance ${field.name}];
		[#if field.type.objcPrimitive]
		XCTAssertEqual(expected, actual);
		[#else]
		XCTAssertEqualObjects(expected, actual);
		[/#if]
	}
	[/#if]
}

[/#if]
[/#list]

@end
