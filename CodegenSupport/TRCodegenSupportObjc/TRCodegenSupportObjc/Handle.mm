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

#import <TRCodegenSupportObjc/Handle.hh>

CodegenSupportObjc::Handle::Handle(CodegenSupport::BaseObject * nativeObject, id hostObject)
	:nativeObject(nativeObject), weakHostObject(hostObject), internalData(nullptr)
{
}

CodegenSupportObjc::Handle::~Handle(void)
{
	// remove for multithreaded implementation
    assert([NSThread isMainThread]);
	// some better asserts?
	delete nativeObject;
}

id CodegenSupportObjc::Handle::getHostObject(void) const
{
	return weakHostObject;
}

void * CodegenSupportObjc::Handle::getInternalData(void) const
{
	return internalData;
}

void CodegenSupportObjc::Handle::setInternalData(void * data)
{
	this->internalData = data;
}