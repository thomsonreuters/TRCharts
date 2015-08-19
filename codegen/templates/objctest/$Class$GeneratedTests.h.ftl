[#ftl]
${copyright}
${autogenNote}

[#if extend?exists]
#import "${extend.classDef.name}Tests.h"
[#else]
#import <XCTest/XCTest.h>
[/#if]

@interface ${objcClassname}GeneratedTests : [#if extend?exists]${extend.classDef.objcClassname}Tests[#else]XCTestCase[/#if]

[#if instance]
-(id)createInstance;
[/#if]

@end
