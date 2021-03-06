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

#import <TRChartsObjc/Support/DateIntervalStructMarshaller.hh>
#import <TRChartsObjc/Support/Marshallers.hh>



Charts::DateInterval TRChartsObjc::DateIntervalStructMarshaller::marshall(const CodegenSupportObjc::StrongAnyPtr & in) const
{
	TRDateInterval * const tmp = (TRDateInterval*)in;
	Charts::DateInterval out;
	out.unit = TRChartsObjc::getDateUnitMarshaller().marshall([tmp unit]);
	out.magnitude = TRChartsObjc::getNumberMarshaller().marshall([tmp magnitude]);
	return out;
}


CodegenSupportObjc::StrongAnyPtr TRChartsObjc::DateIntervalStructMarshaller::unmarshall(const Charts::DateInterval & in) const
{
	TRDateInterval * out = [[TRDateInterval alloc] init];
	[out setUnit:TRChartsObjc::getDateUnitMarshaller().unmarshall(in.unit)];
	[out setMagnitude:TRChartsObjc::getNumberMarshaller().unmarshall(in.magnitude)];
	return out;
}


Charts::DateInterval TRChartsObjc::DateIntervalStructMarshaller::marshallBoxed(const id & in) const
{
	return marshall(in);
}


id TRChartsObjc::DateIntervalStructMarshaller::unmarshallBoxed(const Charts::DateInterval & in) const
{
	return unmarshall(in);
}

// TODO: temporary hack until we fix static init + threads problems properly

void TRChartsObjc::DateIntervalStructMarshaller::init(void) const
{
}

