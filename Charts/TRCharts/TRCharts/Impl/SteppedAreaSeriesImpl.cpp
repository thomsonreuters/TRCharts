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

#ifndef TRCharts_Impl_SteppedAreaSeriesImpl_cpp
#define TRCharts_Impl_SteppedAreaSeriesImpl_cpp

#include <TRCharts/Impl/SteppedAreaSeriesImpl.hpp>


Charts::SteppedAreaSeries::SteppedAreaSeries(void)
{
}


Charts::SteppedAreaSeries::~SteppedAreaSeries(void)
{
}


void Charts::SteppedAreaSeries::createVertices(std::vector<glm::vec2> & vertices)
{
    bool isFirst = true;
    ScalarDatum lastValue;
    for(const ScalarDatum & value : data) {
        if(isFirst) {
            isFirst = false;
        } else {
            const glm::vec2 a = createVertex(value.abscissa, 0.0);
            const glm::vec2 b = createVertex(value.abscissa, lastValue.ordinate);
            vertices.push_back(a);
            vertices.push_back(b);
        }
        const glm::vec2 c = createVertex(value.abscissa, 0.0);
        const glm::vec2 d = createVertex(value.abscissa, value.ordinate);
        vertices.push_back(c);
        vertices.push_back(d);
        lastValue = value;
    }
}

void Charts::SteppedAreaSeries::createDatumColors(std::vector<glm::vec4> & colors)
{
    bool isFirst = true;
    glm::vec4 lastValue;
    for(const glm::vec4 & value : datumColors) {
        if(isFirst) {
            isFirst = false;
        } else {
            colors.push_back(lastValue);
            colors.push_back(lastValue);
        }
        colors.push_back(value);
        colors.push_back(value);
        lastValue = value;
    }
}

glm::float_t Charts::SteppedAreaSeries::getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const
{
    if(TR_VERIFY(index >= 0 && index < data.size())) {
        const ScalarDatum & thisDatum = data[index];
        const ScalarDatum & nextDatum = data[std::min(index + 1, data.size() - 1)];
        const glm::vec2 positionProj = position * proj;
        const glm::vec2 datumPositionMin = dataToScreenRaw(glm::dvec2(thisDatum.abscissa, 0.f)) * proj;
        const glm::vec2 datumPositionMax = dataToScreenRaw(glm::dvec2(nextDatum.abscissa, nextDatum.ordinate)) * proj;
        if(glm::all(glm::greaterThanEqual(positionProj, datumPositionMin)) && glm::all(glm::lessThanEqual(positionProj, datumPositionMax))) {
            return 0.f;
        }
        // TODO measure actual distance.
    }
    return std::numeric_limits<glm::float_t>::max();
}

Charts::ScalarDatum Charts::SteppedAreaSeries::blendDatums(const Charts::ScalarDatum & a, const Charts::ScalarDatum & b, const double t) const
{
    return ScalarDatum(glm::mix(a.abscissa, b.abscissa, t), a.ordinate);
}

#endif