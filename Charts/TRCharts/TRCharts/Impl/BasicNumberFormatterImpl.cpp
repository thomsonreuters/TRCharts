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

#include <TRCharts/Impl/BasicNumberFormatterImpl.hpp>
#include <TRCharts/Impl/PlatformUtils.hpp>

Charts::BasicNumberFormatter::BasicNumberFormatter(void)
	:decimalPlaces(3)
{
}


Charts::BasicNumberFormatter::~BasicNumberFormatter(void)
{
}


long Charts::BasicNumberFormatter::getDecimalPlaces(void) const
{
	return this->decimalPlaces;
}


void Charts::BasicNumberFormatter::setDecimalPlaces(long value)
{
	this->decimalPlaces = value;
}


std::string Charts::BasicNumberFormatter::formatNumber(double value) const
{
    const std::string result = PlatformUtils::formatNumber(value, decimalPlaces);
    if(result == "-0") {
        return "0";
    } else {
        return result;
    }
}
