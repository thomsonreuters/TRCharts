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

#ifndef Charts_Impl_AbstractDateFormatterImpl_cpp
#define Charts_Impl_AbstractDateFormatterImpl_cpp

#include <TRCharts/Impl/AbstractDateFormatterImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TRCharts/Impl/PlatformUtils.hpp>


Charts::AbstractDateFormatter::AbstractDateFormatter(void)
	:GeneratedAbstractDateFormatter(), syntax()
{
}


Charts::AbstractDateFormatter::~AbstractDateFormatter(void)
{
}


Charts::FormatSyntax Charts::AbstractDateFormatter::getSyntax(void) const
{
	return this->syntax;
}


void Charts::AbstractDateFormatter::setSyntax(Charts::FormatSyntax value)
{
	this->syntax = value;
}


std::string Charts::AbstractDateFormatter::formatDateImpl(double seconds, const std::string & format) const
{
    switch(getSyntax()) {
        case FormatSyntax::Cstdlib:
            return Utils::formatDate(seconds, format);
        case FormatSyntax::Platform:
            return PlatformUtils::formatDate(seconds, format);
    }
}


std::string Charts::AbstractDateFormatter::formatDateImpl(tm * time, const std::string & format) const
{
    switch(getSyntax()) {
        case FormatSyntax::Cstdlib:
            return Utils::formatDate(*time, format);
        case FormatSyntax::Platform:
            const time_t seconds = mktime(time);
            return PlatformUtils::formatDate(seconds, format);
    }
}

#endif