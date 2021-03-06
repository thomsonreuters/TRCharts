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

#import <TRChartsObjc/DataTransform.h>
#import <TRChartsObjc/Support/Marshallers.hh>

@implementation TRDataTransform

-(TRDataTransform *)init
{
	self = [super init];
	if(self) {
		self.offset = 0.0;
		self.scale = 1.0;
	}
	return self;
}

+(TRDataTransform *)offset:(double)offset scale:(double)scale
{
	TRDataTransform * const result = [[TRDataTransform alloc] init];
	result.offset = offset;
	result.scale = scale;
	return result;
}

+(TRDataTransform *)concatenate:(TRDataTransform *)dataTransform otherDataTransform:(TRDataTransform *)otherDataTransform
{
	return TRChartsObjc::getDataTransformMarshaller().unmarshall(Charts::DataTransform::concatenate(TRChartsObjc::getDataTransformMarshaller().marshall(dataTransform), TRChartsObjc::getDataTransformMarshaller().marshall(otherDataTransform)));	
}

+(TRDataTransform *)invert:(TRDataTransform *)dataTransform
{
	return TRChartsObjc::getDataTransformMarshaller().unmarshall(Charts::DataTransform::invert(TRChartsObjc::getDataTransformMarshaller().marshall(dataTransform)));	
}

+(double)apply:(TRDataTransform *)dataTransform value:(double)value
{
	return TRChartsObjc::getNumberMarshaller().unmarshall(Charts::DataTransform::apply(TRChartsObjc::getDataTransformMarshaller().marshall(dataTransform), TRChartsObjc::getNumberMarshaller().marshall(value)));	
}

+(TRRange *)applyRange:(TRDataTransform *)dataTransform range:(TRRange *)range
{
	return TRChartsObjc::getRangeMarshaller().unmarshall(Charts::DataTransform::applyRange(TRChartsObjc::getDataTransformMarshaller().marshall(dataTransform), TRChartsObjc::getRangeMarshaller().marshall(range)));	
}

+(double)unapply:(TRDataTransform *)dataTransform value:(double)value
{
	return TRChartsObjc::getNumberMarshaller().unmarshall(Charts::DataTransform::unapply(TRChartsObjc::getDataTransformMarshaller().marshall(dataTransform), TRChartsObjc::getNumberMarshaller().marshall(value)));	
}

+(TRRange *)unapplyRange:(TRDataTransform *)dataTransform range:(TRRange *)range
{
	return TRChartsObjc::getRangeMarshaller().unmarshall(Charts::DataTransform::unapplyRange(TRChartsObjc::getDataTransformMarshaller().marshall(dataTransform), TRChartsObjc::getRangeMarshaller().marshall(range)));	
}

-(BOOL)isEqual:(id)anObject
{
	if(anObject == nil || ! [anObject isKindOfClass:[TRDataTransform class]]) {
		return NO;
	}
	TRDataTransform * other = anObject;
	BOOL result = YES;
	result = result && (self.offset == other.offset);
	result = result && (self.scale == other.scale);
	return result;
}

-(NSUInteger)hash
{
	NSUInteger result = 7;
    result = 31 * result + (NSUInteger)self.offset;
    result = 31 * result + (NSUInteger)self.scale;
	return result;
}

-(id)copyWithZone:(NSZone *)zone
{
	TRDataTransform * copy = [[self class] allocWithZone:zone];
	copy.offset = self.offset;
	copy.scale = self.scale;
	return copy;
}

-(NSString*)description
{
	return [NSString stringWithFormat:@"TRDataTransform[%f, %f]", self.offset, self.scale];
}

@end