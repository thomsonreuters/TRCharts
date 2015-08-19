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

#ifndef TRCharts_Impl_NumberAxisImpl_cpp
#define TRCharts_Impl_NumberAxisImpl_cpp

#include <TRCharts/Impl/NumberAxisImpl.hpp>
#include <TRCharts/NumberTickCalculator.hpp>
#include <TRCharts/NumberFormatter.hpp>
#include <TRCharts/Impl/Utils.hpp>


Charts::NumberAxis::NumberAxis(void)
	:tickCalculator(), tickInterval(1.0)
{
}


Charts::NumberAxis::~NumberAxis(void)
{
}



const std::shared_ptr<Charts::NumberTickCalculator> & Charts::NumberAxis::getTickCalculator(void) const
{
	return this->tickCalculator;
}


void Charts::NumberAxis::setTickCalculator(const std::shared_ptr<Charts::NumberTickCalculator> & value)
{
    newVersion();
	this->tickCalculator = value;
}

bool Charts::NumberAxis::update(const RenderArgs & args)
{
    bool changed = Charts::AbstractNumberAxis::update(args);
    if(tickCalculator && Range::valid(dataRange) && Range::valid(screenDataRange)) {
        const double newTickInterval = tickCalculator->calculateTickInterval(dataRange, screenDataRange, getScreenLength());
        if(newTickInterval != tickInterval) {
            tickInterval = newTickInterval;
            changed = true;
        }
    }
    if(changed) {
        ticks.clear();
        if(Range::positive(screenDataRange) && (Range::length(screenDataRange) <= (MAXIMUM_TICKS * tickInterval))) {
            const double tickStart = int(screenDataRange.min / tickInterval) * tickInterval;
            double tick = tickStart;
            while(tick <= screenDataRange.max) {
                if(tick >= screenDataRange.min) {
                    ticks.push_back(createTick(tick));
                }
                tick += tickInterval;
            }
        } else {
            ticks.push_back(createTick(screenDataRange.min));
        }
    }
    return changed;
}


std::vector<Charts::Axis::Tick> Charts::NumberAxis::getTicks(void) const
{
    return ticks;
}

double Charts::NumberAxis::getTickInterval(void) const
{
    return this->tickInterval;
}

const double Charts::NumberAxis::MAXIMUM_TICKS = 1000;

#endif