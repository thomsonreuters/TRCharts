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

#import <TRChartsObjc/TickAligningRangeCalculator.h>
#import <TRChartsObjc/RangeCalculator.h>

#import <TRCharts/TickAligningRangeCalculator.hpp>
#import <TRCharts/RangeCalculator.hpp>

#import <TRChartsObjc/Support/Marshallers.hh>
#import <TRCodegenSupportObjc/Handle.hh>

@implementation TRTickAligningRangeCalculator

-(TRTickAligningRangeCalculator*)init {
	TRChartsObjc::verifyCurrentQueue();
	self = [super initConcrete];
	Charts::TickAligningRangeCalculator * const obj = new Charts::TickAligningRangeCalculator();
	CodegenSupportObjc::Handle * const handle = new CodegenSupportObjc::Handle(obj, self);
	obj->setHandle(handle);
	[self setHandle:handle];
	return self;
}

-(id<TRRangeCalculator>)rangeCalculator {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::TickAligningRangeCalculator> obj = handle->getNativeObject<Charts::TickAligningRangeCalculator>();
	return TRChartsObjc::getRangeCalculatorMarshaller().unmarshall(obj->getRangeCalculator());
}

-(void)setRangeCalculator:(id<TRRangeCalculator>)value {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::TickAligningRangeCalculator> obj = handle->getNativeObject<Charts::TickAligningRangeCalculator>();
	obj->setRangeCalculator(TRChartsObjc::getRangeCalculatorMarshaller().marshall(value));
}

-(TRRange *)calculateRange:(TRRange *)dataRange {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::TickAligningRangeCalculator> obj = handle->getNativeObject<Charts::TickAligningRangeCalculator>();
	return TRChartsObjc::getRangeMarshaller().unmarshall(obj->calculateRange(TRChartsObjc::getRangeMarshaller().marshall(dataRange)));	
}

@end