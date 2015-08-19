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

#ifndef TRCharts_Impl_LineDecorationImpl_cpp
#define TRCharts_Impl_LineDecorationImpl_cpp

#include <TRCharts/Impl/LineDecorationImpl.hpp>
#include <TRCharts/ContinuousAxis.hpp>
#include <TRCharts/Impl/ContinuousAxisImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>

#include <TR3DUtils/LineRenderer.hpp>
#include <TR3DUtils/Utils.hpp>


Charts::LineDecoration::LineDecoration(void)
:axis(), value(), lineStyle(1.0, LineMode::Solid)
{
}


Charts::LineDecoration::~LineDecoration(void)
{
}


const std::shared_ptr<Charts::ContinuousAxis> & Charts::LineDecoration::getAxis(void) const
{
	return this->axis;
}


void Charts::LineDecoration::setAxis(const std::shared_ptr<Charts::ContinuousAxis> & value)
{
    newVersion();
    this->axis = value;
}


double Charts::LineDecoration::getValue(void) const
{
	return this->value;
}


void Charts::LineDecoration::setValue(double value)
{
    if(this->value != value) {
        newVersion();
        this->value = value;
    }
}


const Charts::LineStyle & Charts::LineDecoration::getLineStyle(void) const
{
	return this->lineStyle;
}


void Charts::LineDecoration::setLineStyle(const Charts::LineStyle & value)
{
    if(this->lineStyle != value) {
        newVersion();
        this->lineStyle = value;
    }
}


void Charts::LineDecoration::preRender(TR3DUtils::RenderContext & context, const RenderArgs & args)
{
    
}

void Charts::LineDecoration::render(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
    if(TR_VERIFY(axis)) {
        beforeRender(context, args);
        const glm::float_t screenValue = axis->dataToScreen(this->value);
        if(axis->inScreenRange(screenValue)) {
            const glm::vec2 axisDirection = axis->getAxisDirection();
            const glm::vec2 gridDirection = axis->getGridDirection();
            const glm::float_t gridStart = axis->getGridStart();
            const glm::float_t gridLength = axis->getGridLength();
            const glm::vec2 start = (axisDirection * screenValue) + gridDirection * gridStart;
            const glm::vec2 end = (axisDirection * screenValue) + gridDirection * (gridStart + gridLength);
            const std::shared_ptr<TR3DUtils::LineRenderer> lineRenderer = context.getLineRenderer();
            glLineWidth(this->lineStyle.thickness * args.contentScaleFactor);
            lineRenderer->bind(TR3DUtils::LineRenderer::Mode(lineStyle.mode));
            lineRenderer->bindModelViewProjection(args.projection);
            lineRenderer->bindColor(Utils::colorToVec4(getColor()) * Utils::opacityToAlpha(getOpacity()));
            lineRenderer->drawLine(glm::vec3(start, 0.f), glm::vec3(end, 0.f));
        }
        afterRender(context, args);
    }
}

#endif
