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

#ifndef Charts_Impl_IncludeZeroRangeCalculatorImpl_cpp
#define Charts_Impl_IncludeZeroRangeCalculatorImpl_cpp

#include <TRCharts/Impl/IncludeZeroRangeCalculatorImpl.hpp>
#include <TRCharts/RangeCalculator.hpp>


Charts::IncludeZeroRangeCalculator::IncludeZeroRangeCalculator(void)
	:GeneratedIncludeZeroRangeCalculator(), rangeCalculator()
{
}


Charts::IncludeZeroRangeCalculator::~IncludeZeroRangeCalculator(void)
{
}


const std::shared_ptr<Charts::RangeCalculator> & Charts::IncludeZeroRangeCalculator::getRangeCalculator(void) const
{
	return this->rangeCalculator;
}


void Charts::IncludeZeroRangeCalculator::setRangeCalculator(const std::shared_ptr<Charts::RangeCalculator> & value)
{
	this->rangeCalculator = value;
}

Charts::Range Charts::IncludeZeroRangeCalculator::calculateRange(const Charts::Range & dataRange) const
{
    Range result = dataRange;
    if(rangeCalculator) {
        result = rangeCalculator->calculateRange(result);
    }
	return Range::merge(result, Range(0.0, 0.0));
}


#endif