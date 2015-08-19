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

#ifndef Charts_Impl_PaddingRangeCalculatorImpl_cpp
#define Charts_Impl_PaddingRangeCalculatorImpl_cpp

#include <TRCharts/Impl/PaddingRangeCalculatorImpl.hpp>
#include <TRCharts/RangeCalculator.hpp>


Charts::PaddingRangeCalculator::PaddingRangeCalculator(void)
	:GeneratedPaddingRangeCalculator(), rangeCalculator(), padding()
{
}


Charts::PaddingRangeCalculator::~PaddingRangeCalculator(void)
{
}


const std::shared_ptr<Charts::RangeCalculator> & Charts::PaddingRangeCalculator::getRangeCalculator(void) const
{
	return this->rangeCalculator;
}


void Charts::PaddingRangeCalculator::setRangeCalculator(const std::shared_ptr<Charts::RangeCalculator> & value)
{
	this->rangeCalculator = value;
}


const Charts::Range & Charts::PaddingRangeCalculator::getPadding(void) const
{
	return this->padding;
}


void Charts::PaddingRangeCalculator::setPadding(const Charts::Range & value)
{
	this->padding = value;
}


Charts::Range Charts::PaddingRangeCalculator::calculateRange(const Charts::Range & dataRange) const
{
    Charts::Range result = dataRange;
    if(rangeCalculator) {
        result = rangeCalculator->calculateRange(result);
    }
    result.min -= this->padding.min;
    result.max += this->padding.max;
	return result;
}


#endif