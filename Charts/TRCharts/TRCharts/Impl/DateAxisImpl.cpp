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

#ifndef TRCharts_Impl_DateAxisImpl_cpp
#define TRCharts_Impl_DateAxisImpl_cpp

#include <TRCharts/Impl/DateAxisImpl.hpp>
#include <TRCharts/DateTickCalculator.hpp>
#include <TRCharts/DateFormatter.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>

#include <ctime>

Charts::DateAxis::DateAxis(void)
		: offsetSeconds(), tickFormatter(), tickCalculator()
{
}

Charts::DateAxis::~DateAxis(void)
{
}

const std::shared_ptr<Charts::DateFormatter> & Charts::DateAxis::getTickFormatter(void) const
{
	return this->tickFormatter;
}

void Charts::DateAxis::setTickFormatter(const std::shared_ptr<Charts::DateFormatter> & value)
{
	newVersion();
	this->tickFormatter = value;
}

const std::shared_ptr<Charts::DateTickCalculator> & Charts::DateAxis::getTickCalculator(void) const
{
	return this->tickCalculator;
}

void Charts::DateAxis::setTickCalculator(const std::shared_ptr<Charts::DateTickCalculator> & value)
{
	newVersion();
	this->tickCalculator = value;
}

double Charts::DateAxis::getOffsetSeconds(void) const
{
    return this->offsetSeconds;
}

void Charts::DateAxis::setOffsetSeconds(double value)
{
    if(this->offsetSeconds != value) {
        newVersion();
        this->offsetSeconds = value;
    }
}

Charts::Axis::Tick Charts::DateAxis::createTick(double value) const
{
    std::string label;
    if(tickFormatter) {
        label = tickFormatter->formatDate(value + offsetSeconds, tickInterval.unit);
    } else {
        label = "?";
    }
    return ContinuousAxis::createTick(value, label);
}

#include <iostream>

bool Charts::DateAxis::update(const RenderArgs & args)
{
	bool changed = Charts::ContinuousAxis::update(args);
	if (tickCalculator && Range::valid(dataRange) && Range::valid(screenDataRange)) {
		const DateInterval newTickInterval = tickCalculator->calculateTickInterval(dataRange, screenDataRange, getScreenLength());
		if (newTickInterval != tickInterval) {
			tickInterval = newTickInterval;
			changed = true;
		}
	}
	if (changed) {
		ticks.clear();
		const time_t rawMinTime = screenDataRange.min;
		tm tickStart = tm();
		if (TR_VERIFY(Utils::getTime(tickStart, rawMinTime))) {
            const double approxIntervalSeconds = Utils::dateUnitSeconds(tickInterval.unit) * tickInterval.magnitude;
			Utils::roundTime(tickStart, tickInterval);
            tm tick = tickStart;
            if(Range::positive(screenDataRange) && (Range::length(screenDataRange) <= (MAXIMUM_TICKS * approxIntervalSeconds))) {
                const time_t rawMaxTime = screenDataRange.max;
                std::cerr.precision(500);
                while(true) {
                    const time_t time = std::mktime(&tick);
                    // hit an unrepresentable time =/, time ticks will disappear...
                    if(time >= 0) {
                        const double rawTick = double(time) - offsetSeconds;
                        if(rawTick <= rawMaxTime) {
                            if(rawTick >= rawMinTime) {
                                ticks.push_back(createTick(rawTick));
                            }
                            Utils::incrementTime(tick, tickInterval);
                        } else {
                            break;
                        }
                    } else {
                        break;
                    }
                }
            } else {
                const time_t time = std::mktime(&tick);
                const double rawTick = double(time) - offsetSeconds;
                if(time >= 0) {
                    ticks.push_back(createTick(rawTick));
                }
            }
		}
	}
	return changed;
}

std::vector<Charts::Axis::Tick> Charts::DateAxis::getTicks(void) const
{
    return ticks;
}

const Charts::DateInterval & Charts::DateAxis::getTickInterval(void) const
{
    return this->tickInterval;
}

const double Charts::DateAxis::MAXIMUM_TICKS = 1000;

#endif
