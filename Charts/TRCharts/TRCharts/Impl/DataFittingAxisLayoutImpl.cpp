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

#ifndef Charts_Impl_DataFittingAxisLayoutImpl_cpp
#define Charts_Impl_DataFittingAxisLayoutImpl_cpp

#include <TRCharts/Impl/DataFittingAxisLayoutImpl.hpp>
#include <TRCharts/ContinuousAxis.hpp>
#include <TRCharts/RangeCalculator.hpp>


Charts::DataFittingAxisLayout::DataFittingAxisLayout(void)
	:GeneratedDataFittingAxisLayout()
{
}


Charts::DataFittingAxisLayout::~DataFittingAxisLayout(void)
{
}

const std::shared_ptr<Charts::RangeCalculator> & Charts::DataFittingAxisLayout::getRangeCalculator(void) const
{
    return this->rangeCalculator;
}

void Charts::DataFittingAxisLayout::setRangeCalculator(const std::shared_ptr<Charts::RangeCalculator> & value)
{
    this->rangeCalculator = value;
}

Charts::DataTransform Charts::DataFittingAxisLayout::calculateTransform(const std::shared_ptr<Charts::ContinuousAxis> & axis, const Charts::Range & dataRange, double screenLength, const Charts::DataTransform & renderTransform) const
{
    DataTransform transform{};
    Charts::Range actualDataRange = dataRange;
    if(this->rangeCalculator) {
        actualDataRange = this->rangeCalculator->calculateRange(actualDataRange);
    }
    if(Range::positive(actualDataRange)) {
        transform.scale = 1.0 / Range::length(actualDataRange);
    } else {
        transform.scale = 1.0;
    }
    transform.offset = -actualDataRange.min * transform.scale;
    return transform;
}


#endif