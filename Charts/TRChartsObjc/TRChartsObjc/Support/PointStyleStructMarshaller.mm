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

#import <TRChartsObjc/Support/PointStyleStructMarshaller.hh>
#import <TRChartsObjc/Support/Marshallers.hh>



Charts::PointStyle TRChartsObjc::PointStyleStructMarshaller::marshall(const CodegenSupportObjc::StrongAnyPtr & in) const
{
	TRPointStyle * const tmp = (TRPointStyle*)in;
	Charts::PointStyle out;
	out.diameter = TRChartsObjc::getNumberMarshaller().marshall([tmp diameter]);
	return out;
}


CodegenSupportObjc::StrongAnyPtr TRChartsObjc::PointStyleStructMarshaller::unmarshall(const Charts::PointStyle & in) const
{
	TRPointStyle * out = [[TRPointStyle alloc] init];
	[out setDiameter:TRChartsObjc::getNumberMarshaller().unmarshall(in.diameter)];
	return out;
}


Charts::PointStyle TRChartsObjc::PointStyleStructMarshaller::marshallBoxed(const id & in) const
{
	return marshall(in);
}


id TRChartsObjc::PointStyleStructMarshaller::unmarshallBoxed(const Charts::PointStyle & in) const
{
	return unmarshall(in);
}

// TODO: temporary hack until we fix static init + threads problems properly

void TRChartsObjc::PointStyleStructMarshaller::init(void) const
{
}
