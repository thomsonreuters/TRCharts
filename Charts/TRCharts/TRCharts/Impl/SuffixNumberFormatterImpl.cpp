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

#ifndef TRCharts_Impl_SuffixNumberFormatterImpl_cpp
#define TRCharts_Impl_SuffixNumberFormatterImpl_cpp

#include <TRCharts/Impl/SuffixNumberFormatterImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>

Charts::SuffixNumberFormatter::SuffixNumberFormatter(void)
:base(1000), suffixes({"", "K", "M", "G", "T", "P", "E", "Z", "Y"})
{
    recalculatePowers();
}

Charts::SuffixNumberFormatter::~SuffixNumberFormatter(void)
{
}


long Charts::SuffixNumberFormatter::getBase(void) const
{
	return this->base;
}


void Charts::SuffixNumberFormatter::setBase(long value)
{
	this->base = value;
    recalculatePowers();
}


const std::vector<std::string> & Charts::SuffixNumberFormatter::getSuffixes(void) const
{
	return this->suffixes;
}


void Charts::SuffixNumberFormatter::setSuffixes(const std::vector<std::string> & value)
{
	this->suffixes = value;
    recalculatePowers();
}

void Charts::SuffixNumberFormatter::recalculatePowers(void)
{
    powers.resize(suffixes.size());
    for(size_t i = 0; i != suffixes.size(); ++i) {
        const double power = pow(double(base), double(i));
        powers[i] = power;
    }
}

std::string Charts::SuffixNumberFormatter::formatNumber(double value) const
{
    if(TR_VERIFY(base > 0) && (suffixes.size() == powers.size())){
        for(size_t i = 0; i != suffixes.size(); ++i) {
            const size_t j = suffixes.size() - (i + 1);
            const double power = powers[j];
            if(fabs(value) >= power) {
                return BasicNumberFormatter::formatNumber(value / power) + suffixes[j];
            }
        }
    }
	return BasicNumberFormatter::formatNumber(value);
}

#endif