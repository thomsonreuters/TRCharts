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

#ifndef Charts_Impl_BasicDateFormatterImpl_cpp
#define Charts_Impl_BasicDateFormatterImpl_cpp

#include <TRCharts/Impl/BasicDateFormatterImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TRCharts/Impl/PlatformUtils.hpp>

Charts::BasicDateFormatter::BasicDateFormatter(void)
	:GeneratedBasicDateFormatter(), format()
{
}


Charts::BasicDateFormatter::~BasicDateFormatter(void)
{
}


const std::string & Charts::BasicDateFormatter::getFormat(void) const
{
	return this->format;
}


void Charts::BasicDateFormatter::setFormat(const std::string & value)
{
	this->format = value;
}

std::string Charts::BasicDateFormatter::formatDate(double seconds, Charts::DateUnit unit) const
{
    return formatDateImpl(seconds, this->format);
}

#endif