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

#ifndef TRCharts_Impl_AutomaticNumberTickCalculatorImpl_cpp
#define TRCharts_Impl_AutomaticNumberTickCalculatorImpl_cpp

#include <TRCharts/Impl/AutomaticNumberTickCalculatorImpl.hpp>
#include <TRCharts/NumberFormatter.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>


Charts::AutomaticNumberTickCalculator::AutomaticNumberTickCalculator(void)
:targetScreenInterval(1.0), minInterval(0.0), base(10.0), multipliers({5.0, 2.0})
{
}


Charts::AutomaticNumberTickCalculator::~AutomaticNumberTickCalculator(void)
{
}


double Charts::AutomaticNumberTickCalculator::getTargetScreenInterval(void) const
{
	return this->targetScreenInterval;
}


void Charts::AutomaticNumberTickCalculator::setTargetScreenInterval(double value)
{
	this->targetScreenInterval = value;
}

double Charts::AutomaticNumberTickCalculator::getMinInterval(void) const
{
	return this->minInterval;
}


void Charts::AutomaticNumberTickCalculator::setMinInterval(double value)
{
	this->minInterval = value;
}


double Charts::AutomaticNumberTickCalculator::getBase(void) const
{
	return this->base;
}


void Charts::AutomaticNumberTickCalculator::setBase(double value)
{
	this->base = value;
}

const std::vector<double> & Charts::AutomaticNumberTickCalculator::getMultipliers(void) const
{
	return this->multipliers;
}


void Charts::AutomaticNumberTickCalculator::setMultipliers(const std::vector<double> & value)
{
#warning should verify that no multiplier is less than 1.0, or greater than base and that multipliers increase
 	this->multipliers = value;
}

double Charts::AutomaticNumberTickCalculator::calculateTickInterval(const Charts::Range & dataRange, const Charts::Range & visibleDataRange, double screenLength) const
{
    if(Range::positive(visibleDataRange)) {
        // tidy up, can probably determine correct interval analytically
        const double visibleRangeLength = (visibleDataRange.max - visibleDataRange.min);
        const double targetVisibleTicks = screenLength / targetScreenInterval;
        double tickInterval = Utils::pow10Floor(visibleRangeLength / targetVisibleTicks);
        for(const double multiplier : multipliers) {
            if((visibleRangeLength / tickInterval) <= targetVisibleTicks) {
                break;
            }
            tickInterval *= multiplier;
        }
        return std::max(tickInterval, minInterval);
    } else {
        return 0;
    }
}

#endif