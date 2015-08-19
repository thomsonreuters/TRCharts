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

#ifndef TRCharts_Impl_FixedNumberTickCalculatorImpl_cpp
#define TRCharts_Impl_FixedNumberTickCalculatorImpl_cpp

#include <TRCharts/Impl/FixedNumberTickCalculatorImpl.hpp>
#include <TRCharts/NumberFormatter.hpp>

Charts::FixedNumberTickCalculator::FixedNumberTickCalculator(void)
:tickInterval(1)
{
}


Charts::FixedNumberTickCalculator::~FixedNumberTickCalculator(void)
{
}

double Charts::FixedNumberTickCalculator::getTickInterval(void) const
{
	return this->tickInterval;
}


void Charts::FixedNumberTickCalculator::setTickInterval(double value)
{
	this->tickInterval = value;
}


double Charts::FixedNumberTickCalculator::calculateTickInterval(const Charts::Range & dataRange, const Charts::Range & visibleDataRange, double screenLength) const
{
    return this->tickInterval;
}

#endif
