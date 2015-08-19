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

#ifndef TRCharts_Impl_SeriesImpl_cpp
#define TRCharts_Impl_SeriesImpl_cpp

#include <TRCharts/Impl/SeriesImpl.hpp>
#include <TRCharts/ContinuousAxis.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/RenderProgram.hpp>


Charts::Series::Series(void)
	:selectable(false)
{
	markDirty();
}


Charts::Series::~Series(void)
{
}

const std::shared_ptr<Charts::ContinuousAxis> & Charts::Series::getOrdinateAxis(void) const
{
	return this->ordinateAxis;
}

void Charts::Series::setOrdinateAxis(const std::shared_ptr<Charts::ContinuousAxis> & value)
{
	this->ordinateAxis = value;
	markDirty();
}

void Charts::Series::setColor(const Charts::Color & value)
{
    if(this->color != value) {
        newVersion();
        this->color = value;
    }
}

const Charts::Color & Charts::Series::getColor(void) const
{
	return this->color;
}

void Charts::Series::markDirty(void)
{
    dirtyRanges.clear();
	dirtyRanges.push_back(IndexRange(std::numeric_limits<long>::min(), std::numeric_limits<long>::max()));
}

void Charts::Series::markRangeDirty(const Charts::IndexRange & range)
{
    std::vector<IndexRange> newRanges;
    Charts::IndexRange mergedRange = range;
    for(const Charts::IndexRange & existingRange : dirtyRanges) {
        if(IndexRange::overlap(existingRange, mergedRange)) {
            mergedRange = IndexRange::merge(existingRange, mergedRange);
        } else {
            newRanges.push_back(existingRange);
        }
    }
    newRanges.push_back(mergedRange);
    dirtyRanges = newRanges;
}

void Charts::Series::attach(void)
{
    GeneratedSeries::attach();
    dispose();
}

void Charts::Series::detach(void)
{
    GeneratedSeries::detach();
    dispose();
}

void Charts::Series::beforeRender(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(args.areaStart.x * args.contentScaleFactor, args.areaStart.y * args.contentScaleFactor, args.areaSize.x * args.contentScaleFactor, args.areaSize.y * args.contentScaleFactor);
}

void Charts::Series::afterRender(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
    glDisable(GL_SCISSOR_TEST);
}

std::string Charts::Series::getSimpleSeriesProgramName(void)
{
    return "trcharts.simpleseries";
}

std::pair<std::string, std::string> Charts::Series::getDatumColorsProgramDefine(void)
{
    return std::make_pair("DATUM_COLORS_ENABLED", "1");
}

std::pair<std::string, std::string> Charts::Series::getConstantPointSizeProgramDefine(void)
{
    return std::make_pair("CONSTANT_POINT_SIZE_ENABLED", "1");
}

std::pair<std::string, std::string> Charts::Series::getDatumPointSizeProgramDefine(void)
{
    return std::make_pair("DATUM_POINT_SIZE_ENABLED", "1");
}

std::pair<std::string, std::string> Charts::Series::getConstantLineParamsProgramDefine(void)
{
    return std::make_pair("CONSTANT_LINE_PARAMS_ENABLED", "1");
}

std::pair<std::string, std::string> Charts::Series::getDatumLineParamsProgramDefine(void)
{
    return std::make_pair("DATUM_LINE_PARAMS_ENABLED", "1");
}

glm::vec2 Charts::Series::createLineParams(const LineStyle lineStyle) const
{
    switch(lineStyle.mode) {
        case LineMode::Dashed:
            return glm::vec2(0.08, 0.5);
        case LineMode::Solid:
        default:
            return glm::vec2(0.0, 0.0);
    }
}

const long Charts::Series::NO_SELECTION = -1;

namespace
{
    const std::string commonSource =
    R"**(
#define LINE_PARAMS_WAVELENGTH 0
#define LINE_PARAMS_CUTOFF 1

#ifdef CONSTANT_POINT_SIZE_ENABLED
#define POINT_SIZE_ENABLED
#endif
    
#ifdef DATUM_POINT_SIZE_ENABLED
#define POINT_SIZE_ENABLED
#endif
    
#ifdef CONSTANT_LINE_PARAMS_ENABLED
#define LINE_PARAMS_ENABLED
#endif
    
#ifdef DATUM_LINE_PARAMS_ENABLED
#define LINE_PARAMS_ENABLED
#endif
    
)**";
    
    const std::string vertexSource =
    R"**(
attribute highp vec2 value;
    
uniform mediump vec4 color;
uniform highp vec2 valueOffset;
uniform highp vec2 valueScale;
uniform mediump mat4 modelViewProjection;
uniform mediump vec2 offset;
uniform highp vec2 abscissaAxis;
uniform highp vec2 ordinateAxis;
uniform lowp float opacity;

varying highp vec2 fragmentValue;
varying mediump vec4 fragmentColor;

#ifdef CONSTANT_POINT_SIZE_ENABLED
uniform mediump float pointSize;
#endif
    
#ifdef DATUM_COLORS_ENABLED
attribute vec4 datumColor;
#endif
    
#ifdef LINE_PARAMS_ENABLED
attribute vec2 totalLength;
varying highp vec2 fragmentTotalLength;
varying lowp vec2 fragmentLineParams;
#endif
#ifdef DATUM_LINE_PARAMS_ENABLED
attribute vec2 datumLineParams;
#else
uniform vec2 lineParams;
#endif

void main()
{
    highp vec2 displayValue = (value * valueScale) + valueOffset;
    highp vec2 position = (displayValue.x * abscissaAxis) + (displayValue.y * ordinateAxis);
    gl_Position = modelViewProjection * vec4(offset + position, 0.0, 1);
    fragmentValue = displayValue;
#ifdef CONSTANT_POINT_SIZE_ENABLED
    gl_PointSize = pointSize;
#endif
#ifdef DATUM_COLORS_ENABLED
    fragmentColor = datumColor * opacity;
#else
    fragmentColor = color * opacity;
#endif
#ifdef LINE_PARAMS_ENABLED
#ifdef DATUM_LINE_PARAMS_ENABLED
    fragmentLineParams = datumLineParams;
#else
    fragmentLineParams = lineParams;
#endif
#endif
#ifdef LINE_PARAMS_ENABLED
    fragmentTotalLength = totalLength * valueScale;
#endif
}
)**";
    
    const std::string fragmentSource =
R"**(
uniform mediump vec2 valueMin;
uniform mediump vec2 valueMax;

varying highp vec2 fragmentValue;
varying mediump vec4 fragmentColor;
    
#ifdef LINE_PARAMS_ENABLED
varying highp vec2 fragmentTotalLength;
varying lowp vec2 fragmentLineParams;
#endif

void main()
{
    lowp vec2 weight = vec2(1.0);
#ifdef POINT_SIZE_ENABLED
    weight *= step(length(gl_PointCoord - vec2(0.5)), 0.5);
#endif
#ifdef LINE_PARAMS_ENABLED
    lowp float pattern = fract((fragmentTotalLength.x + fragmentTotalLength.y) * fragmentLineParams[LINE_PARAMS_WAVELENGTH]);
    weight *= step(fragmentLineParams[LINE_PARAMS_CUTOFF], pattern);
#endif
    gl_FragColor = vec4(fragmentColor.xyz, fragmentColor.a * (weight.x * weight.y));
}
)**";
    
    const std::vector<std::string> uniforms = {"modelViewProjection", "color", "offset", "abscissaAxis", "ordinateAxis", "valueOffset", "valueScale", "pointSize", "lineParams", "opacity"};
    
    const std::vector<std::string> attributes = {"value", "datumColor", "totalLength", "fragmentLineParams"};
    
    bool staticInit = [](void) -> bool {
        bool result = true;
        result = result && TR3DUtils::RenderContext::registerRenderProgram(Charts::Series::getSimpleSeriesProgramName(),
                                                                       TR3DUtils::RenderProgramDef(commonSource + vertexSource,
                                                                                               commonSource + fragmentSource,
                                                                                               attributes,
                                                                                               uniforms));
        return result;
    }();
    
}

#endif
