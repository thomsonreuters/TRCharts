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

#include <TRCodegenSupport/BaseObject.hpp>

CodegenSupport::BaseObject::BaseObject(void)
:handle(nullptr)
{
}

CodegenSupport::BaseObject::~BaseObject(void)
{
}

std::shared_ptr<CodegenSupport::BaseObject> CodegenSupport::BaseObject::getSharedPtr(void)
{
	return shared_from_this();
}

std::shared_ptr<const CodegenSupport::BaseObject> CodegenSupport::BaseObject::getSharedPtr(void) const
{
	return shared_from_this();
}

void CodegenSupport::BaseObject::setHandle(void * const handle)
{
	this->handle = handle;
}

void * CodegenSupport::BaseObject::getHandle(void) const
{
	return this->handle;
}