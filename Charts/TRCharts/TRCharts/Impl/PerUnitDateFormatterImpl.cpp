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

#ifndef TRCharts_Impl_PerUnitDateFormatterImpl_cpp
#define TRCharts_Impl_PerUnitDateFormatterImpl_cpp

#include <TRCharts/Impl/PerUnitDateFormatterImpl.hpp>

#include <TRCharts/Impl/Utils.hpp>

Charts::PerUnitDateFormatter::PerUnitDateFormatter(void)
{
}


Charts::PerUnitDateFormatter::~PerUnitDateFormatter(void)
{
}


void Charts::PerUnitDateFormatter::setUnitFormat(Charts::DateUnit unit, const std::string & format)
{
	unitFormats[unit] = format;
}


std::string Charts::PerUnitDateFormatter::getUnitFormat(Charts::DateUnit unit) const
{
    const auto iter = unitFormats.find(unit);
    if(iter != unitFormats.end()) {
        return iter->second;
    } else {
        return std::string("");
    }
}


void Charts::PerUnitDateFormatter::setZeroUnitFormat(Charts::DateUnit unit, const std::string & format)
{
	zeroUnitFormats[unit] = format;
}


std::string Charts::PerUnitDateFormatter::getZeroUnitFormat(Charts::DateUnit unit) const
{
    const auto iter = zeroUnitFormats.find(unit);
    if(iter != zeroUnitFormats.end()) {
        return iter->second;
    } else {
        return std::string("");
    }
}


std::string Charts::PerUnitDateFormatter::formatDate(double seconds, Charts::DateUnit unit) const
{
    tm time = tm();
    if(Utils::getTime(time, seconds)) {
        if(zeroUnitFormats.size()) {
            DateUnit zeroUnit;
            bool hasZeroUnit = false;
            for(size_t i = 0; i != Enums::size<DateUnit>(); ++i) {
                const DateUnit potentialZeroUnit = DateUnit(i);
                if(Utils::timeGet(time, potentialZeroUnit) == 0) {
                    zeroUnit = potentialZeroUnit;
                    hasZeroUnit = true;
                } else {
                    break;
                }
            }
            if(hasZeroUnit) {
                const std::string format = getZeroUnitFormat(zeroUnit);
                if(format.size()) {
                   return formatDateImpl(&time, format);
                }
            }
        }
        DateUnit formatUnit = unit;
        std::string format = "";
        do {
            format = getUnitFormat(formatUnit);
            if(format.size()) {
                break;
            } else {
                formatUnit = DateUnit(int(formatUnit) - 1);
            }
        } while(int(formatUnit) != 0);
        return formatDateImpl(&time, format);
    } else {
       return "?";
    }
}


#endif