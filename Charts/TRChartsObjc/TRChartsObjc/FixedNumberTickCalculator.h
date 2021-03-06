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

#import <TRChartsObjc/NumberTickCalculator.h>
#import <TRChartsObjc/Range.h>
#import <TRCodegenSupportObjc/BaseObject.h>

/**
 * Number tick calculator implementation that returns a constant pre-specified
 * tick interval
 *
 * @warning This is an automatically generated wrapper around a native object;
 * overriding methods will not work as expected.
 *
 */
@interface TRFixedNumberTickCalculator : TRBaseObject<TRNumberTickCalculator>

/** @name Fields */

/**
 * This value is always returned by calculateTickInterval
 *
 * @return The current tick interval.
 * @see setTickInterval:
 */
-(double)tickInterval;

/**
 * This value is always returned by calculateTickInterval
 *
 * @param value The new tick interval.
 * @see tickInterval
 */
-(void)setTickInterval:(double)value;

/** @name Methods */

/**
 * Returns the value of tickInterval
 *
 * @param dataRange Ignored
 * @param visibleDataRange Ignored
 * @param screenLength Ignored
 * @return The result.
 */
-(double)calculateTickInterval:(TRRange *)dataRange visibleDataRange:(TRRange *)visibleDataRange screenLength:(double)screenLength;

@end