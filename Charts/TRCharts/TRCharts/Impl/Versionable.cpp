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

#ifndef TRCharts_Impl_Versionable_cpp
#define TRCharts_Impl_Versionable_cpp

#include <TRCharts/Impl/DrawableImpl.hpp>


Charts::Versionable::Versionable(void)
:version(1)
{
}


Charts::Versionable::~Versionable(void)
{
}


Charts::Versionable::Version Charts::Versionable::getVersion(void) const
{
	return this->version;
}


void Charts::Versionable::newVersion(void)
{
    ++this->version;
}

#endif