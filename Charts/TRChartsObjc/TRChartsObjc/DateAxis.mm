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

#import <TRChartsObjc/DateAxis.h>
#import <TRChartsObjc/DateFormatter.h>
#import <TRChartsObjc/DateTickCalculator.h>

#import <TRCharts/DateAxis.hpp>
#import <TRCharts/DateFormatter.hpp>
#import <TRCharts/DateTickCalculator.hpp>

#import <TRChartsObjc/Support/Marshallers.hh>
#import <TRCodegenSupportObjc/Handle.hh>

@implementation TRDateAxis

-(TRDateAxis*)init {
	TRChartsObjc::verifyCurrentQueue();
	self = [super initConcrete];
	Charts::DateAxis * const obj = new Charts::DateAxis();
	CodegenSupportObjc::Handle * const handle = new CodegenSupportObjc::Handle(obj, self);
	obj->setHandle(handle);
	[self setHandle:handle];
	return self;
}

-(double)offsetSeconds {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::DateAxis> obj = handle->getNativeObject<Charts::DateAxis>();
	return TRChartsObjc::getNumberMarshaller().unmarshall(obj->getOffsetSeconds());
}

-(void)setOffsetSeconds:(double)value {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::DateAxis> obj = handle->getNativeObject<Charts::DateAxis>();
	obj->setOffsetSeconds(TRChartsObjc::getNumberMarshaller().marshall(value));
}

-(id<TRDateFormatter>)tickFormatter {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::DateAxis> obj = handle->getNativeObject<Charts::DateAxis>();
	return TRChartsObjc::getDateFormatterMarshaller().unmarshall(obj->getTickFormatter());
}

-(void)setTickFormatter:(id<TRDateFormatter>)value {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::DateAxis> obj = handle->getNativeObject<Charts::DateAxis>();
	obj->setTickFormatter(TRChartsObjc::getDateFormatterMarshaller().marshall(value));
}

-(id<TRDateTickCalculator>)tickCalculator {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::DateAxis> obj = handle->getNativeObject<Charts::DateAxis>();
	return TRChartsObjc::getDateTickCalculatorMarshaller().unmarshall(obj->getTickCalculator());
}

-(void)setTickCalculator:(id<TRDateTickCalculator>)value {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::DateAxis> obj = handle->getNativeObject<Charts::DateAxis>();
	obj->setTickCalculator(TRChartsObjc::getDateTickCalculatorMarshaller().marshall(value));
}

-(TRDateInterval *)tickInterval {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::DateAxis> obj = handle->getNativeObject<Charts::DateAxis>();
	return TRChartsObjc::getDateIntervalMarshaller().unmarshall(obj->getTickInterval());
}

@end