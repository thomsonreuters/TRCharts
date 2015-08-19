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

#import <TRCodegenSupportObjc/IntegerMarshaller.hh>

long CodegenSupportObjc::IntegerMarshaller::marshall(const long & in) const
{
    return in;
}

long CodegenSupportObjc::IntegerMarshaller::unmarshall(const long & in) const
{
    return in;
}

long CodegenSupportObjc::IntegerMarshaller::marshallBoxed(const id & in) const
{
    return marshall([(NSNumber*)in longValue]);
}

id CodegenSupportObjc::IntegerMarshaller::unmarshallBoxed(const long & in) const
{
    return [NSNumber numberWithLong:unmarshall(in)];
}