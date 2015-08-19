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

#ifndef TRCharts_Impl_AutomaticDateTickCalculatorImpl_cpp
#define TRCharts_Impl_AutomaticDateTickCalculatorImpl_cpp

#include <TRCharts/Impl/AutomaticDateTickCalculatorImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/Log.hpp>

Charts::AutomaticDateTickCalculator::AutomaticDateTickCalculator(void)
:targetScreenInterval(1.0), minInterval(DateUnit::Second, 0.0)
{
}


Charts::AutomaticDateTickCalculator::~AutomaticDateTickCalculator(void)
{
}

double Charts::AutomaticDateTickCalculator::getTargetScreenInterval(void) const
{
	return this->targetScreenInterval;
}


void Charts::AutomaticDateTickCalculator::setTargetScreenInterval(double value)
{
	this->targetScreenInterval = value;
}


const Charts::DateInterval & Charts::AutomaticDateTickCalculator::getMinInterval(void) const
{
	return this->minInterval;
}


void Charts::AutomaticDateTickCalculator::setMinInterval(const Charts::DateInterval & value)
{
	this->minInterval = value;
}

Charts::DateInterval Charts::AutomaticDateTickCalculator::calculateTickInterval(const Charts::Range & dataRange, const Charts::Range & visibleDataRange, double screenLength) const
{
    const std::vector<std::vector<long>> unitTickIntervals{
        {1, 2, 5, 10, 15, 30},      // second
        {1, 2, 5, 10, 15, 30},      // minute
        {1, 2, 3, 6, 12},              // hour
        {1, 2, 5, 10, 15},          // day
        {1, 2, 6},                  // month
        {1, 2, 3, 4, 5, 10}         // year
    };
    if(TR_VERIFY(unitTickIntervals.size() == Enums::size<DateUnit>())) {
        const double visibleRangeLength = (visibleDataRange.max - visibleDataRange.min);
        const double targetVisibleTicks = screenLength / targetScreenInterval;
        for(size_t i = 0; i != unitTickIntervals.size(); ++i) {
            const DateUnit unit = DateUnit(i);
            const int unitSeconds = Utils::dateUnitSeconds(unit);
            for(long unitTickInterval : unitTickIntervals[i]) {
                const long tickInterval = unitTickInterval * unitSeconds;
                if((visibleRangeLength / tickInterval) <= targetVisibleTicks) {
                    return Utils::maxDateInterval(DateInterval(unit, unitTickInterval), this->minInterval);
                }
            }
        }
        const long unitTickInterval = Utils::pow10Floor(visibleRangeLength / Utils::dateUnitSeconds(DateUnit::Year));
        return Utils::maxDateInterval(DateInterval(DateUnit::Year, unitTickInterval), this->minInterval);
    }
    return DateInterval(DateUnit::Second, 1);
}


#endif