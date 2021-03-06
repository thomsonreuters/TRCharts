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

#import <TRChartsObjc/LineSeries.h>
#import <TRChartsObjc/LineStyleSource.h>

#import <TRCharts/LineSeries.hpp>
#import <TRCharts/LineStyleSource.hpp>

#import <TRChartsObjc/Support/Marshallers.hh>
#import <TRCodegenSupportObjc/Handle.hh>

@implementation TRLineSeries

-(TRLineSeries*)init {
	TRChartsObjc::verifyCurrentQueue();
	self = [super initConcrete];
	Charts::LineSeries * const obj = new Charts::LineSeries();
	CodegenSupportObjc::Handle * const handle = new CodegenSupportObjc::Handle(obj, self);
	obj->setHandle(handle);
	[self setHandle:handle];
	return self;
}

-(TRLineStyle *)lineStyle {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::LineSeries> obj = handle->getNativeObject<Charts::LineSeries>();
	return TRChartsObjc::getLineStyleMarshaller().unmarshall(obj->getLineStyle());
}

-(void)setLineStyle:(TRLineStyle *)value {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::LineSeries> obj = handle->getNativeObject<Charts::LineSeries>();
	obj->setLineStyle(TRChartsObjc::getLineStyleMarshaller().marshall(value));
}

-(id<TRLineStyleSource>)lineStyleSource {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::LineSeries> obj = handle->getNativeObject<Charts::LineSeries>();
	return TRChartsObjc::getLineStyleSourceMarshaller().unmarshall(obj->getLineStyleSource());
}

-(void)setLineStyleSource:(id<TRLineStyleSource>)value {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::LineSeries> obj = handle->getNativeObject<Charts::LineSeries>();
	obj->setLineStyleSource(TRChartsObjc::getLineStyleSourceMarshaller().marshall(value));
}

-(id<TRContinuousDataSource>)dataSource {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::LineSeries> obj = handle->getNativeObject<Charts::LineSeries>();
	return TRChartsObjc::getContinuousDataSource_ScalarDatumMarshaller().unmarshall(obj->getDataSource());
}

-(void)setDataSource:(id<TRContinuousDataSource>)value {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::LineSeries> obj = handle->getNativeObject<Charts::LineSeries>();
	obj->setDataSource(TRChartsObjc::getContinuousDataSource_ScalarDatumMarshaller().marshall(value));
}

-(TRScalarDatum *)getDatum:(long)index {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::LineSeries> obj = handle->getNativeObject<Charts::LineSeries>();
	return TRChartsObjc::getScalarDatumMarshaller().unmarshall(obj->getDatum(TRChartsObjc::getIntegerMarshaller().marshall(index)));	
}

-(TRScalarDatum *)interpolateDatum:(double)abscissa {
	TRChartsObjc::verifyCurrentQueue();
	CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([self handle]);
	std::shared_ptr<Charts::LineSeries> obj = handle->getNativeObject<Charts::LineSeries>();
	return TRChartsObjc::getScalarDatumMarshaller().unmarshall(obj->interpolateDatum(TRChartsObjc::getNumberMarshaller().marshall(abscissa)));	
}

@end