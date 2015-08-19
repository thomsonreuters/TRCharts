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

#ifndef TRCharts_Impl_BandSeriesImpl_cpp
#define TRCharts_Impl_BandSeriesImpl_cpp

#include <TRCharts/Impl/BandSeriesImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/Utils.hpp>


Charts::BandSeries::BandSeries(void)
{
}


Charts::BandSeries::~BandSeries(void)
{
}

void Charts::BandSeries::createVertices(std::vector<glm::vec2> & vertices)
{
    for(const RangeDatum & value : data) {
        vertices.push_back(createVertex(value.abscissa, value.ordinate.min));
        vertices.push_back(createVertex(value.abscissa, value.ordinate.max));
    }
}

void Charts::BandSeries::createDatumColors(std::vector<glm::vec4> & colors)
{
    for(const glm::vec4 & value : datumColors) {
        colors.push_back(value);
        colors.push_back(value);
    }
}

void Charts::BandSeries::preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args)
{
    std::vector<glm::vec2> values;
    createVertices(values);
    std::vector<std::shared_ptr<const TR3DUtils::RenderBuffer>> buffers;
    buffers.push_back(context.createBuffer(2, values.size(), glm::value_ptr(values[0])));
    if(useDatumColors) {
        std::vector<glm::vec4> colors;
        createDatumColors(colors);
        if(TR_VERIFY(values.size() == colors.size())) {
            buffers.push_back(context.createBuffer(4, colors.size(), glm::value_ptr(colors[0])));
        } else {
            useDatumColors = false;
        }
    }
    vao = context.createVAO(buffers, GL_TRIANGLE_STRIP);
    TR3DUtils::RenderProgram::DefineMap defineMap;
    if(useDatumColors) {
        defineMap.insert(Series::getDatumColorsProgramDefine());
    }
    program = context.getNamedProgram(Series::getSimpleSeriesProgramName(), defineMap);
}

void Charts::BandSeries::render(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
    if(TR_VERIFY(vao && program)) {
        beforeRender(context, args);
        program->bind();
        program->bindUniform("modelViewProjection", args.projection);
        program->bindUniform("color", Utils::colorToVec4(getColor()));
        program->bindUniform("offset", getRenderOffset());
        program->bindUniform("abscissaAxis", abscissaAxisDirection);
        program->bindUniform("ordinateAxis", ordinateAxisDirection);
        program->bindUniform("valueScale", getRenderValueScale());
        program->bindUniform("valueOffset", getRenderValueOffset());
        program->bindUniform("opacity", glm::float_t(getOpacity() / 255.0));
        vao->draw();
        afterRender(context, args);
    }
}

Charts::Range Charts::BandSeries::getAbscissaRange(void) const
{
    Range result = Range::identity();
    for(const RangeDatum & datum : data) {
        result.min = std::min(result.min, datum.abscissa);
        result.max = std::max(result.max, datum.abscissa);
    }
    return result;
}

Charts::Range Charts::BandSeries::getOrdinateRange(void) const
{
    Range result = Range::identity();
    for(const RangeDatum & datum : data) {
        result.min = std::min(result.min, datum.ordinate.min);
        result.max = std::max(result.max, datum.ordinate.max);
    }
    return result;
}

glm::float_t Charts::BandSeries::getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const
{
    if(TR_VERIFY(index < data.size())) {
        const RangeDatum & datum = data[index];
        const glm::vec2 datumPositionMin = dataToScreenRaw(glm::dvec2(datum.abscissa, datum.ordinate.min));
        const glm::vec2 datumPositionMax = dataToScreenRaw(glm::dvec2(datum.abscissa, datum.ordinate.max));
        const glm::vec2 datumPositionDiff = (datumPositionMax - datumPositionMin);
        const float t = glm::dot(position - datumPositionMin, datumPositionDiff) / Utils::lengthSquared(datumPositionDiff);
        if(t < 0) {
            return Utils::distanceSquaredProj(datumPositionMin, position, proj);
        } else if(t > 1) {
            return Utils::distanceSquaredProj(datumPositionMax, position, proj);
        } else {
            return Utils::distanceSquaredProj(datumPositionMin + (t * datumPositionDiff), position, proj);
        }
    } else {
        return std::numeric_limits<glm::float_t>::max();
    }
}

Charts::RangeDatum Charts::BandSeries::blendDatums(const Charts::RangeDatum & a, const Charts::RangeDatum & b, const double t) const
{
    return RangeDatum(glm::mix(a.abscissa, b.abscissa, t), Range(glm::mix(a.ordinate.min, b.ordinate.min, t), glm::mix(a.ordinate.max, b.ordinate.max, t)));
}

Charts::Range Charts::BandSeries::getDatumOrdinateRange(const Charts::RangeDatum & datum) const
{
    return datum.ordinate;
}

void Charts::BandSeries::dispose(void)
{
    GeneratedBandSeries::dispose();
    program.reset();
}

#endif
