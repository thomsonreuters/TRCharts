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

#ifndef TRCharts_Impl_TickAligningRangeCalculatorImpl_cpp
#define TRCharts_Impl_TickAligningRangeCalculatorImpl_cpp

#include <TRCharts/Impl/TickAligningRangeCalculatorImpl.hpp>
#include <TRCharts/RangeCalculator.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>

Charts::TickAligningRangeCalculator::TickAligningRangeCalculator(void)
	:rangeCalculator()
{
}


Charts::TickAligningRangeCalculator::~TickAligningRangeCalculator(void)
{
}

const std::shared_ptr<Charts::RangeCalculator> & Charts::TickAligningRangeCalculator::getRangeCalculator(void) const
{
	return this->rangeCalculator;
}


void Charts::TickAligningRangeCalculator::setRangeCalculator(const std::shared_ptr<Charts::RangeCalculator> & value)
{
	this->rangeCalculator = value;
}

namespace {

    double alignAwayFromZero(double magnitude)
    {
        if(TR_VERIFY(magnitude > 0)) {
            double result = Charts::Utils::pow10Floor(magnitude);
            const double multipliers[2] = {5, 2};
            size_t multiplierIndex = 0;
            while(result < magnitude) {
                const double multiplier = multipliers[multiplierIndex % 2];
                result *= multiplier;
                ++multiplierIndex;
            }
                
            return result;
        } else {
            return 0.0;
        }
    }
    
    double alignTowardsZero(double magnitude)
    {
        if(TR_VERIFY(magnitude > 0)) {
            double result = Charts::Utils::pow10Ceil(magnitude);
            const double multipliers[2] = {0.5, 0.2};
            size_t multiplierIndex = 0;
            while(result > magnitude) {
                const double multiplier = multipliers[multiplierIndex % 2];
                result *= multiplier;
                ++multiplierIndex;
            }
            return result;
        } else {
            return 0.0;
        }
    }
    
    double alignMin(double value)
    {
        if(value > 0.0) {
            return alignTowardsZero(value);
        } else if (value < 0.0) {
            return -alignAwayFromZero(-value);
        } else {
            return 0.0;
        }
    }
    
    double alignMax(double value)
    {
        if(value > 0.0) {
            return alignAwayFromZero(value);
        } else if (value < 0.0) {
            return -alignTowardsZero(-value);
        } else {
            return 0.0;
        }
    }
}

Charts::Range Charts::TickAligningRangeCalculator::calculateRange(const Charts::Range & dataRange) const
{
    Range result = dataRange;
    if(this->rangeCalculator) {
        result = this->rangeCalculator->calculateRange(dataRange);
    }
    if(result.max > 0.0) {
        result.min = 0.0;//alignMin(result.min);
        result.max = alignMax(result.max);
    } else {
        result.min = 0.0;//alignMin(result.min);
        result.max = 0.0;
    }
    return result;
}


#endif