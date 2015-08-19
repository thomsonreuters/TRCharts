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

#import <TRCodegenSupportObjc/StringMarshaller.hh>

#import <cassert>

std::string CodegenSupportObjc::StringMarshaller::marshall(const StrongStringPtr & in) const
{
    if(const char * cstr = [in cStringUsingEncoding:NSUTF8StringEncoding]) {
        return std::string(cstr);
    } else {
        assert(false && "Could not convert string to UTF8");
        return std::string("?");
    }
}

CodegenSupportObjc::StrongStringPtr CodegenSupportObjc::StringMarshaller::unmarshall(const std::string & in) const
{
    return [NSString stringWithUTF8String:in.c_str()];
}

std::string CodegenSupportObjc::StringMarshaller::marshallBoxed(const id & in) const
{
    return marshall(in);
}

id CodegenSupportObjc::StringMarshaller::unmarshallBoxed(const std::string & in) const
{
    return unmarshall(in);
}