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

#ifndef TRCharts_Impl_AttachableImpl_cpp
#define TRCharts_Impl_AttachableImpl_cpp

#include <TRCharts/Impl/AttachableImpl.hpp>


Charts::Attachable::Attachable(void)
	:Versionable(), attached(), enabled(true), lastCleanVersion(0)
{
}


Charts::Attachable::~Attachable(void)
{
}


bool Charts::Attachable::isAttached(void) const
{
	return this->attached;
}


bool Charts::Attachable::isEnabled(void) const
{
	return this->enabled;
}

void Charts::Attachable::setEnabled(bool value)
{
    if(this->enabled != value) {
        newVersion();
        this->enabled = value;
    }
}

void Charts::Attachable::attach(void)
{
	if(this->attached) {
		throw std::logic_error("Object is already attached");
	}
	this->attached = true;
}

void Charts::Attachable::detach(void)
{
	this->attached = false;
}


bool Charts::Attachable::versionChanged(void) const
{
    return lastCleanVersion != getVersion();
}

void Charts::Attachable::markVersion(void)
{
    lastCleanVersion = getVersion();
}

#endif