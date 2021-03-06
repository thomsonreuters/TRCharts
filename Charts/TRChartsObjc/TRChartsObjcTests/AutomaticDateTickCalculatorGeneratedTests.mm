/*******************************************************************************
 * Copyright 2015 Thomson Reuters
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/
/* NOTE: This file is autogenerated, do not edit this file directly.*/

#import "AutomaticDateTickCalculatorGeneratedTests.h"
#import <TRChartsObjc/AutomaticDateTickCalculator.h>
#import "TestUtils.hh"

#import <XCTest/XCTestAssertions.h>

@implementation TRAutomaticDateTickCalculatorGeneratedTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

-(id)createInstance
{
	return [[TRAutomaticDateTickCalculator alloc] init];
}

- (void) testInitializeFieldTargetScreenInterval
{
	TRAutomaticDateTickCalculator * instance = [self createInstance];
	if(instance) {
		double expected = 1.0;
		double actual = [instance targetScreenInterval];
		XCTAssertEqual(expected, actual);
	}
}

- (void) testInitializeFieldMinInterval
{
	TRAutomaticDateTickCalculator * instance = [self createInstance];
	if(instance) {
		TRDateInterval * expected = [TRDateInterval unit:TR_DATEUNIT_SECOND magnitude:0.0];
		TRDateInterval * actual = [instance minInterval];
		XCTAssertEqualObjects(expected, actual);
	}
}

- (void) testSetFieldTargetScreenInterval
{
	TRAutomaticDateTickCalculator * instance = [self createInstance];
	if(instance) {
		double original = [instance targetScreenInterval];
		double expected = TRChartsObjc::getNumberTestValue(original);
		[instance setTargetScreenInterval:expected];
		double actual = [instance targetScreenInterval];
		XCTAssertEqual(expected, actual);
	}
}

- (void) testSetFieldMinInterval
{
	TRAutomaticDateTickCalculator * instance = [self createInstance];
	if(instance) {
		TRDateInterval * original = [instance minInterval];
		TRDateInterval * expected = TRChartsObjc::getDateIntervalTestValue(original);
		[instance setMinInterval:expected];
		TRDateInterval * actual = [instance minInterval];
		XCTAssertEqualObjects(expected, actual);
	}
}


@end
