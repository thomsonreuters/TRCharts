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

#ifndef TRCharts_Impl_AreaSeriesImpl_cpp
#define TRCharts_Impl_AreaSeriesImpl_cpp

#include <TRCharts/Impl/AreaSeriesImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/Utils.hpp>


Charts::AreaSeries::AreaSeries(void)
{
}


Charts::AreaSeries::~AreaSeries(void)
{
}

void Charts::AreaSeries::createVertices(std::vector<glm::vec2> & vertices)
{
    bool isFirst = true;
    for(const ScalarDatum & value : data) {
        if(isFirst) {
            isFirst = false;
        } else {
            const glm::vec2 a = createVertex(value.abscissa, 0.0);
            const glm::vec2 b = createVertex(value.abscissa, value.ordinate);
            vertices.push_back(a);
            vertices.push_back(b);
        }
        const glm::vec2 c = createVertex(value.abscissa, 0.0);
        const glm::vec2 d = createVertex(value.abscissa, value.ordinate);
        vertices.push_back(c);
        vertices.push_back(d);
    }
}

void Charts::AreaSeries::createDatumColors(std::vector<glm::vec4> & colors)
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

void Charts::AreaSeries::preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args)
{
    std::vector<glm::vec2> values;
    createVertices(values);
    std::vector<std::shared_ptr<const TR3DUtils::RenderBuffer>> buffers;
    buffers.push_back(context.createBuffer(2, values.size(), glm::value_ptr(values[0])));
    if(useDatumColors) {
        TR3DUtils::Log::Debug("Using custom colors");
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


void Charts::AreaSeries::render(TR3DUtils::RenderContext & context, const RenderArgs & args) const
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

Charts::Range Charts::AreaSeries::getAbscissaRange(void) const
{
    Range result = Range::identity();
    for(const ScalarDatum & datum : data) {
        result.min = std::min(result.min, datum.abscissa);
        result.max = std::max(result.max, datum.abscissa);
    }
    return result;
}

Charts::Range Charts::AreaSeries::getOrdinateRange(void) const
{
    Range result = Range::identity();
    for(const ScalarDatum & datum : data) {
        result.min = std::min(result.min, datum.ordinate);
        result.max = std::max(result.max, datum.ordinate);
    }
    return result;
}

glm::float_t Charts::AreaSeries::getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const
{
    // this is wrong, it works only for stepped area series
    assert(false);
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


Charts::ScalarDatum Charts::AreaSeries::blendDatums(const Charts::ScalarDatum & a, const Charts::ScalarDatum & b, const double t) const
{
    return ScalarDatum(glm::mix(a.abscissa, b.abscissa, t), glm::mix(a.ordinate, b.ordinate, t));
}

Charts::Range Charts::AreaSeries::getDatumOrdinateRange(const Charts::ScalarDatum & datum) const
{
    return Range(0.f, datum.ordinate);
}

void Charts::AreaSeries::dispose(void)
{
    GeneratedAreaSeries::dispose();
    vao.reset();
    program.reset();
}

#endif
