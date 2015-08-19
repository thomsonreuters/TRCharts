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

#ifndef TRCharts_Impl_SteppedBandSeriesImpl_cpp
#define TRCharts_Impl_SteppedBandSeriesImpl_cpp

#include <TRCharts/Impl/SteppedBandSeriesImpl.hpp>


Charts::SteppedBandSeries::SteppedBandSeries(void)
{
}


Charts::SteppedBandSeries::~SteppedBandSeries(void)
{
}


void Charts::SteppedBandSeries::createVertices(std::vector<glm::vec2> & vertices)
{
    bool isFirst = true;
    RangeDatum previousValue;
    for(const RangeDatum & value : data) {
        if(isFirst) {
            isFirst = false;
        } else {
            vertices.push_back(createVertex(value.abscissa, previousValue.ordinate.min));
            vertices.push_back(createVertex(value.abscissa, previousValue.ordinate.max));
            // degenerate
            vertices.push_back(createVertex(value.abscissa, value.ordinate.min));
        }
        vertices.push_back(createVertex(value.abscissa, value.ordinate.min));
        vertices.push_back(createVertex(value.abscissa, value.ordinate.max));
        previousValue = value;
    }
}

void Charts::SteppedBandSeries::createDatumColors(std::vector<glm::vec4> & colors)
{
    bool isFirst = true;
    glm::vec4 previousValue;
    for(const glm::vec4 & value : datumColors) {
        if(isFirst) {
            isFirst = false;
        } else {
            colors.push_back(previousValue);
            colors.push_back(previousValue);
            colors.push_back(value);
        }
        colors.push_back(value);
        colors.push_back(value);
        previousValue = value;
    }
}

Charts::RangeDatum Charts::SteppedBandSeries::blendDatums(const Charts::RangeDatum & a, const Charts::RangeDatum & b, const double t) const
{
    return RangeDatum(glm::mix(a.abscissa, b.abscissa, t), a.ordinate);
}

#endif