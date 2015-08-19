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

#ifndef TRCharts_Impl_PointSeriesImpl_cpp
#define TRCharts_Impl_PointSeriesImpl_cpp

#include <TRCharts/Impl/PointSeriesImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/Utils.hpp>


Charts::PointSeries::PointSeries(void)
	:pointStyle(1.0)
{
}


Charts::PointSeries::~PointSeries(void)
{
}


const Charts::PointStyle & Charts::PointSeries::getPointStyle(void) const
{
	return this->pointStyle;
}


void Charts::PointSeries::setPointStyle(const Charts::PointStyle & value)
{
    if(this->pointStyle != value) {
        newVersion();
        this->pointStyle = value;
    }
}

void Charts::PointSeries::createVertices(std::vector<glm::vec2> & vertices)
{
    for(const ScalarDatum & value : data) {
        vertices.push_back(createVertex(value.abscissa, value.ordinate));
    }
}

void Charts::PointSeries::createDatumColors(std::vector<glm::vec4> & colors)
{
    colors = datumColors;
}

void Charts::PointSeries::preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args)
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
    vao = context.createVAO(buffers, GL_POINTS);
    TR3DUtils::RenderProgram::DefineMap defineMap;
    defineMap.insert(Series::getConstantPointSizeProgramDefine());
    if(useDatumColors) {
        defineMap.insert(Series::getDatumColorsProgramDefine());
    }
    program = context.getNamedProgram(Series::getSimpleSeriesProgramName(), defineMap);
}

void Charts::PointSeries::render(TR3DUtils::RenderContext & context, const RenderArgs & args) const
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
        program->bindUniform("pointSize", glm::float_t(this->pointStyle.diameter * args.contentScaleFactor));
        vao->draw();
        afterRender(context, args);
    }
}

Charts::Range Charts::PointSeries::getAbscissaRange(void) const
{
    Range result = Range::identity();
    for(const ScalarDatum & datum : data) {
        result.min = std::min(result.min, datum.abscissa);
        result.max = std::max(result.max, datum.abscissa);
    }
    return result;
}

Charts::Range Charts::PointSeries::getOrdinateRange(void) const
{
    Range result = Range::identity();
    for(const ScalarDatum & datum : data) {
        result.min = std::min(result.min, datum.ordinate);
        result.max = std::max(result.max, datum.ordinate);
    }
    return result;
}

glm::float_t Charts::PointSeries::getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const
{
    if(TR_VERIFY(index < data.size())) {
        const ScalarDatum & datum = data[index];
        const glm::vec2 datumPosition = dataToScreenRaw(glm::dvec2(datum.abscissa, datum.ordinate));
        return Utils::distanceSquaredProj(datumPosition, position, proj);
    } else {
        return std::numeric_limits<glm::float_t>::max();
    }
}

Charts::ScalarDatum Charts::PointSeries::blendDatums(const Charts::ScalarDatum & a, const Charts::ScalarDatum & b, const double t) const
{
    return a;
}

Charts::Range Charts::PointSeries::getDatumOrdinateRange(const Charts::ScalarDatum & datum) const
{
    return Range(datum.ordinate, datum.ordinate);
}

void Charts::PointSeries::dispose(void)
{
    GeneratedPointSeries::dispose();
    vao.reset();
    program.reset();
}

#endif
