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

#import <TRChartsObjc/AreaSeries.h>

#import <TRCharts/AreaSeries.hpp>

#import <TRChartsObjc/Support/Marshallers.hh>
#import <TRCodegenSupportObjc/Handle.hh>

@implementation TRAreaSeries

-(TRAreaSeries*)init {
	TRChartsObjc::verifyCurrentQueue();
	self = [super initConcrete];
	Charts::AreaSeries * const obj = new Charts::AreaSeries();
	CodegenSupportObjc::Handle * const handle = new CodegenSupportObjc::Handle(obj, self);
	obj->setHandle(handle);
	[self setHandle:handle];
	return self;
}

-(id<TRContinuousDataSource>)dataSource {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::AreaSeries> obj = handle->getNativeObject<Charts::AreaSeries>();
	return TRChartsObjc::getContinuousDataSource_ScalarDatumMarshaller().unmarshall(obj->getDataSource());
}

-(void)setDataSource:(id<TRContinuousDataSource>)value {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::AreaSeries> obj = handle->getNativeObject<Charts::AreaSeries>();
	obj->setDataSource(TRChartsObjc::getContinuousDataSource_ScalarDatumMarshaller().marshall(value));
}

-(TRScalarDatum *)getDatum:(long)index {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::AreaSeries> obj = handle->getNativeObject<Charts::AreaSeries>();
	return TRChartsObjc::getScalarDatumMarshaller().unmarshall(obj->getDatum(TRChartsObjc::getIntegerMarshaller().marshall(index)));	
}

-(TRScalarDatum *)interpolateDatum:(double)abscissa {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::AreaSeries> obj = handle->getNativeObject<Charts::AreaSeries>();
	return TRChartsObjc::getScalarDatumMarshaller().unmarshall(obj->interpolateDatum(TRChartsObjc::getNumberMarshaller().marshall(abscissa)));	
}

@end