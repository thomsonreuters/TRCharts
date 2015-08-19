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

#ifndef TRCharts_Impl_LineSeriesImpl_cpp
#define TRCharts_Impl_LineSeriesImpl_cpp

#include <TRCharts/Impl/LineSeriesImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TRCharts/LineStyleSource.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/Utils.hpp>

#include <glm/gtx/string_cast.hpp>


Charts::LineSeries::LineSeries(void)
    :lineStyle(LineStyle(1, LineMode::Solid)), useDatumLineStyles(false)
{
}


Charts::LineSeries::~LineSeries(void)
{
}

void Charts::LineSeries::setLineStyle(const LineStyle & value)
{
    if(this->lineStyle != value) {
        newVersion();
        this->lineStyle = value;
    }
}

const Charts::LineStyle & Charts::LineSeries::getLineStyle(void) const
{
	return this->lineStyle;
}

const std::shared_ptr<Charts::LineStyleSource> & Charts::LineSeries::getLineStyleSource(void) const
{
	return this->datumLineStyleSource;
}

void Charts::LineSeries::setLineStyleSource(const std::shared_ptr<Charts::LineStyleSource> & value)
{
	this->datumLineStyleSource = value;
	markDirty();
}

void Charts::LineSeries::createVertices(const IndexRange & indexRange, std::vector<glm::vec2> & vertices) const
{
    if(TR_VERIFY(IndexRange::validWithin(indexRange, IndexRange(0, data.size())))) {
        for(size_t i = indexRange.begin; i != size_t(indexRange.end); ++i) {
            const ScalarDatum & value = data[i];
            vertices.push_back(createVertex(value.abscissa, value.ordinate));
        }
    }
}

void Charts::LineSeries::createDatumColors(const IndexRange & indexRange, std::vector<glm::vec4> & colors) const
{
    if(TR_VERIFY(IndexRange::validWithin(indexRange, IndexRange(0, datumColors.size())))) {
        for(size_t i = indexRange.begin; i != size_t(indexRange.end); ++i) {
            colors.push_back(datumColors[i]);
        }
    }
}

void Charts::LineSeries::createDatumLineParams(const IndexRange & indexRange, std::vector<glm::vec2> & lineParams) const
{
    if(TR_VERIFY(IndexRange::validWithin(indexRange, IndexRange(0, datumLineStyles.size())))) {
        for(size_t i = indexRange.begin; i != size_t(indexRange.end); ++i) {
            lineParams.push_back(createLineParams(datumLineStyles[i]));
        }
    }
}

void Charts::LineSeries::loadAdditionalData(void)
{
    if(this->getDataSource() && datumLineStyleSource) {
        for(const IndexRange & rawRange : dirtyRanges) {
            const IndexRange indexRange = IndexRange::clamp(rawRange, dataSourceIndexRange);
            if(size_t(indexRange.end) != datumLineStyles.size()) {
                datumLineStyles.resize(std::max(indexRange.end, dataSourceIndexRange.end));
            }
            const size_t numDatums = indexRange.end - indexRange.begin;
            TR3DUtils::Log::Debug("Loading %zu datum line styles", numDatums);
            const std::vector<LineStyle> rawLineStyles = this->datumLineStyleSource->getLineStyles(this->getSharedPtr(), indexRange, lineStyle);
            const size_t copyDatumCount = std::min(numDatums, rawLineStyles.size());
            // explicitly allowed to return more/less data than requested.
            std::copy(rawLineStyles.begin(), rawLineStyles.begin() + copyDatumCount, datumLineStyles.begin() + indexRange.begin);
        }
        useDatumLineStyles = true;
    } else {
        datumLineStyles.clear();
        useDatumLineStyles = false;
    }
}

/*Charts::LineSeries::RenderBlock Charts::LineSeries::createBlock(TR3DUtils::RenderContext & context, const RenderArgs & args, const IndexRange & indexRange, const LineStyle & lineStyle)
{
    Charts::LineSeries::RenderBlock result;
    result.indexRange = indexRange;
    result.lineStyle = lineStyle;
    if(TR_VERIFY(Utils::isIndexRangeValid(indexRange, data.size()))) {
        std::vector<glm::vec2> values;
        createVertices(indexRange, values);
        std::vector<std::shared_ptr<const TR3DUtils::RenderBuffer>> buffers;
        buffers.push_back(context.createBuffer(2, values.size(), glm::value_ptr(values[0])));
        if(useDatumColors) {
            std::vector<glm::vec4> colors;
            createDatumColors(indexRange, colors);
            if(TR_VERIFY(values.size() == colors.size())) {
                buffers.push_back(context.createBuffer(4, colors.size(), glm::value_ptr(colors[0])));
            } else {
                useDatumColors = false;
            }
        } else {
            buffers.push_back(nullptr);
        }
        if(lineStyle.mode != LineMode::Solid) {
            std::vector<glm::vec2> lengths;
            glm::vec2 totalLength(0.f);
            glm::vec2 lastVertex;
            bool first = true;
            for(const glm::vec2 & vertex : values) {
                if(!first) {
                    const glm::vec2 difference = vertex - lastVertex;
                    const glm::float_t length = glm::length(difference);
                    if(!Utils::approxEqual(length, 0.f, 0.00001f)) {
                        const glm::vec2 direction = difference / length;
                        const glm::float_t projAbscissa = glm::abs(glm::dot(direction, abscissaAxisDirection));
                        const glm::float_t projOrdinate = glm::abs(glm::dot(direction, ordinateAxisDirection));
                        totalLength += glm::vec2(length * projAbscissa, length * projOrdinate);
                    }
                } else {
                    first = false;
                }
                lengths.push_back(totalLength);
                lastVertex = vertex;
            }
            buffers.push_back(context.createBuffer(2, lengths.size(), glm::value_ptr(lengths[0])));
        }
        result.vao = context.createVAO(buffers, GL_LINE_STRIP);
        TR3DUtils::RenderProgram::DefineMap defineMap;
        if(useDatumColors) {
            defineMap.insert(Series::getDatumColorsProgramDefine());
        }
        switch(lineStyle.mode) {
            case LineMode::Dashed:
                defineMap.insert(Series::getDashedLinesProgramDefine());
            case LineMode::Solid:
            default:
                break;
        }
        result.program = context.getNamedProgram(Series::getSimpleSeriesProgramName(), defineMap);
    }
    return result;
}*/

void Charts::LineSeries::preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args)
{
    const IndexRange indexRange(0, data.size());
    std::vector<glm::vec2> values;
    createVertices(indexRange, values);
    std::vector<std::shared_ptr<const TR3DUtils::RenderBuffer>> buffers;
    buffers.push_back(context.createBuffer(2, values.size(), glm::value_ptr(values[0])));
    if(useDatumColors) {
        std::vector<glm::vec4> colors;
        createDatumColors(indexRange, colors);
        if(TR_VERIFY(values.size() == colors.size())) {
            buffers.push_back(context.createBuffer(4, colors.size(), glm::value_ptr(colors[0])));
        } else {
            useDatumColors = false;
        }
    }
    if(!useDatumColors) {
        // must add an empty color buffer, because attributes are identified by index (messy)
        buffers.push_back(nullptr);
    }
    std::vector<glm::vec2> lengths;
    glm::vec2 totalLength(0.f);
    glm::vec2 lastVertex;
    bool first = true;
    for(const glm::vec2 & vertex : values) {
        if(!first) {
            const glm::vec2 difference = vertex - lastVertex;
            const glm::float_t length = glm::length(difference);
            if(!Utils::approxEqual(length, 0.f, 0.00001f)) {
                const glm::vec2 direction = difference / length;
                const glm::float_t projAbscissa = glm::abs(glm::dot(direction, abscissaAxisDirection));
                const glm::float_t projOrdinate = glm::abs(glm::dot(direction, ordinateAxisDirection));
                totalLength += glm::vec2(length * projAbscissa, length * projOrdinate);
            }
        } else {
            first = false;
        }
        lengths.push_back(totalLength);
        lastVertex = vertex;
    }
    buffers.push_back(context.createBuffer(2, lengths.size(), glm::value_ptr(lengths[0])));
    if(useDatumLineStyles) {
        std::vector<glm::vec2> lineParams;
        createDatumLineParams(indexRange, lineParams);
        if(TR_VERIFY(values.size() == lineParams.size())) {
            buffers.push_back(context.createBuffer(2, lineParams.size(), glm::value_ptr(lineParams[0])));
        } else {
            useDatumLineStyles = false;
        }
    }
    vao = context.createVAO(buffers, GL_LINE_STRIP);
    TR3DUtils::RenderProgram::DefineMap defineMap;
    if(useDatumColors) {
        defineMap.insert(Series::getDatumColorsProgramDefine());
    }
    if(useDatumLineStyles) {
        defineMap.insert(Series::getDatumLineParamsProgramDefine());
    } else {
        defineMap.insert(Series::getConstantLineParamsProgramDefine());
    }
    program = context.getNamedProgram(Series::getSimpleSeriesProgramName(), defineMap);
}

void Charts::LineSeries::render(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
    if(TR_VERIFY(vao && program)) {
        beforeRender(context, args);
        program->bind();
        program->bindUniform("modelViewProjection", args.projection);
        program->bindUniform("color", Utils::colorToVec4(getColor()));
        program->bindUniform("lineStyleParams", createLineParams(getLineStyle()));
        program->bindUniform("offset", getRenderOffset());
        program->bindUniform("abscissaAxis", abscissaAxisDirection);
        program->bindUniform("ordinateAxis", ordinateAxisDirection);
        program->bindUniform("valueScale", getRenderValueScale());
        program->bindUniform("valueOffset", getRenderValueOffset());
        program->bindUniform("opacity", glm::float_t(getOpacity() / 255.0));
        glLineWidth(lineStyle.thickness * args.contentScaleFactor);
        vao->draw();
        afterRender(context, args);
    }
}

Charts::Range Charts::LineSeries::getAbscissaRange(void) const
{
    Range result = Range::identity();
    for(const ScalarDatum & datum : data) {
        result.min = std::min(result.min, datum.abscissa);
        result.max = std::max(result.max, datum.abscissa);
    }
    return result;
}

Charts::Range Charts::LineSeries::getOrdinateRange(void) const
{
    Range result = Range::identity();
    for(const ScalarDatum & datum : data) {
        result.min = std::min(result.min, datum.ordinate);
        result.max = std::max(result.max, datum.ordinate);
    }
    return result;
}

glm::float_t Charts::LineSeries::getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const
{
    if(TR_VERIFY(index < data.size())) {
        const ScalarDatum & datum = data[index];
        const glm::vec2 datumPosition = dataToScreenRaw(glm::dvec2(datum.abscissa, datum.ordinate));
        return Utils::distanceSquaredProj(datumPosition, position, proj);
    } else {
        return std::numeric_limits<glm::float_t>::max();
    }
}

Charts::ScalarDatum Charts::LineSeries::blendDatums(const Charts::ScalarDatum & a, const Charts::ScalarDatum & b, const double t) const
{
    return ScalarDatum(glm::mix(a.abscissa, b.abscissa, t), glm::mix(a.ordinate, b.ordinate, t));
}

Charts::Range Charts::LineSeries::getDatumOrdinateRange(const Charts::ScalarDatum & datum) const
{
    return Range(datum.ordinate, datum.ordinate);
}

void Charts::LineSeries::dispose(void)
{
    GeneratedLineSeries::dispose();
    vao.reset();
    program.reset();
}

#endif
