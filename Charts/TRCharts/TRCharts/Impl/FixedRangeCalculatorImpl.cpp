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

#ifndef TRCharts_Impl_FixedRangeCalculatorImpl_cpp
#define TRCharts_Impl_FixedRangeCalculatorImpl_cpp

#include <TRCharts/Impl/FixedRangeCalculatorImpl.hpp>


Charts::FixedRangeCalculator::FixedRangeCalculator(void)
{
}


Charts::FixedRangeCalculator::~FixedRangeCalculator(void)
{
}


const Charts::Range & Charts::FixedRangeCalculator::getRange(void) const
{
	return this->range;
}


void Charts::FixedRangeCalculator::setRange(const Charts::Range & value)
{
	this->range = value;
}


Charts::Range Charts::FixedRangeCalculator::calculateRange(const Charts::Range & dataRange) const
{
	return this->range;
}

#endif
