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

#ifndef TRCharts_Impl_AbstractNumberAxisImpl_cpp
#define TRCharts_Impl_AbstractNumberAxisImpl_cpp

#include <TRCharts/Impl/AbstractNumberAxisImpl.hpp>
#include <TRCharts/NumberFormatter.hpp>


Charts::AbstractNumberAxis::AbstractNumberAxis(void)
	:tickFormatter()
{
}


Charts::AbstractNumberAxis::~AbstractNumberAxis(void)
{
}


const std::shared_ptr<Charts::NumberFormatter> & Charts::AbstractNumberAxis::getTickFormatter(void) const
{
	return this->tickFormatter;
}


void Charts::AbstractNumberAxis::setTickFormatter(const std::shared_ptr<Charts::NumberFormatter> & value)
{
    newVersion();
	this->tickFormatter = value;
}

Charts::Axis::Tick Charts::AbstractNumberAxis::createTick(const double value) const
{
    std::string label;
    if(tickFormatter) {
        label = tickFormatter->formatNumber(value);
    } else {
        label = "?";
    }
    return ContinuousAxis::createTick(value, label);
}

#endif