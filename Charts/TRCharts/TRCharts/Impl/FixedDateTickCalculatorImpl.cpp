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

#ifndef TRCharts_Impl_FixedDateTickCalculatorImpl_cpp
#define TRCharts_Impl_FixedDateTickCalculatorImpl_cpp

#include <TRCharts/Impl/FixedDateTickCalculatorImpl.hpp>


Charts::FixedDateTickCalculator::FixedDateTickCalculator(void)
:tickInterval(DateUnit::Second, 1)
{
}


Charts::FixedDateTickCalculator::~FixedDateTickCalculator(void)
{
}

const Charts::DateInterval & Charts::FixedDateTickCalculator::getTickInterval(void) const
{
	return this->tickInterval;
}


void Charts::FixedDateTickCalculator::setTickInterval(const Charts::DateInterval & value)
{
	this->tickInterval = value;
}


Charts::DateInterval Charts::FixedDateTickCalculator::calculateTickInterval(const Charts::Range & dataRange, const Charts::Range & visibleDataRange, double screenLength) const
{
    return this->tickInterval;
}


#endif