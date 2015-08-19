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

#ifndef TRCharts_Impl_SteppedLineSeriesImpl_cpp
#define TRCharts_Impl_SteppedLineSeriesImpl_cpp

#include <TRCharts/Impl/SteppedLineSeriesImpl.hpp>
#include <TR3DUtils/Utils.hpp>

Charts::SteppedLineSeries::SteppedLineSeries(void)
{
}


Charts::SteppedLineSeries::~SteppedLineSeries(void)
{
}


void Charts::SteppedLineSeries::createVertices(const IndexRange & indexRange, std::vector<glm::vec2> & vertices) const
{
    if(TR_VERIFY(IndexRange::validWithin(indexRange, IndexRange(0, data.size())))) {
        bool isFirst = true;
        ScalarDatum previousValue;
        for(size_t i = indexRange.begin; i != size_t(indexRange.end); ++i) {
            const ScalarDatum & value = data[i];
            if(isFirst) {
                isFirst = false;
            } else {
                vertices.push_back(createVertex(value.abscissa, previousValue.ordinate));
                vertices.push_back(createVertex(value.abscissa, value.ordinate));
            }
            vertices.push_back(createVertex(value.abscissa, value.ordinate));
            previousValue = value;
        }
    }
}


void Charts::SteppedLineSeries::createDatumColors(const IndexRange & indexRange, std::vector<glm::vec4> & colors) const
{
    if(TR_VERIFY(IndexRange::validWithin(indexRange, IndexRange(0, datumColors.size())))) {
        bool isFirst = true;
        glm::vec4 previousValue;
        for(size_t i = indexRange.begin; i != size_t(indexRange.end); ++i) {
            const glm::vec4 & value = datumColors[i];
            if(isFirst) {
                isFirst = false;
            } else {
                colors.push_back(previousValue);
                colors.push_back(previousValue);
            }
            colors.push_back(value);
            previousValue = value;
        }
    }
}


void Charts::SteppedLineSeries::createDatumLineParams(const IndexRange & indexRange, std::vector<glm::vec2> & lineParams) const
{
    if(TR_VERIFY(IndexRange::validWithin(indexRange, IndexRange(0, datumLineStyles.size())))) {
        bool isFirst = true;
        glm::vec2 previousValue;
        for(size_t i = indexRange.begin; i != size_t(indexRange.end); ++i) {
            const glm::vec2 & value = createLineParams(datumLineStyles[i]);
            if(isFirst) {
                isFirst = false;
            } else {
                lineParams.push_back(previousValue);
                lineParams.push_back(previousValue);
            }
            lineParams.push_back(value);
            previousValue = value;
        }
    }
}

Charts::ScalarDatum Charts::SteppedLineSeries::blendDatums(const Charts::ScalarDatum & a, const Charts::ScalarDatum & b, const double t) const
{
    return ScalarDatum(glm::mix(a.abscissa, b.abscissa, t), a.ordinate);
}

#endif