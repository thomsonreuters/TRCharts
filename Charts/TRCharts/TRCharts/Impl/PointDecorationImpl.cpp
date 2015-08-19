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

#ifndef TRCharts_Impl_PointDecorationImpl_cpp
#define TRCharts_Impl_PointDecorationImpl_cpp

#include <TRCharts/Impl/PointDecorationImpl.hpp>
#include <TRCharts/ContinuousAxis.hpp>
#include <TRCharts/Impl/ContinuousAxisImpl.hpp>
#include <TR3DUtils/PointRenderer.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>


Charts::PointDecoration::PointDecoration(void)
	:abscissaAxis(), ordinateAxis(), value(), pointStyle(1.0)
{
}


Charts::PointDecoration::~PointDecoration(void)
{
}


const std::shared_ptr<Charts::ContinuousAxis> & Charts::PointDecoration::getAbscissaAxis(void) const
{
	return this->abscissaAxis;
}


void Charts::PointDecoration::setAbscissaAxis(const std::shared_ptr<Charts::ContinuousAxis> & value)
{
    newVersion();
    this->abscissaAxis = value;
}


const std::shared_ptr<Charts::ContinuousAxis> & Charts::PointDecoration::getOrdinateAxis(void) const
{
	return this->ordinateAxis;
}


void Charts::PointDecoration::setOrdinateAxis(const std::shared_ptr<Charts::ContinuousAxis> & value)
{
    newVersion();
    this->ordinateAxis = value;
}


const Charts::Coordinates & Charts::PointDecoration::getValue(void) const
{
	return this->value;
}


void Charts::PointDecoration::setValue(const Charts::Coordinates & value)
{
    if(this->value != value) {
        newVersion();
        this->value = value;
    }
}

const Charts::PointStyle & Charts::PointDecoration::getPointStyle(void) const
{
	return this->pointStyle;
}


void Charts::PointDecoration::setPointStyle(const Charts::PointStyle & value)
{
    if(this->pointStyle != value) {
        newVersion();
        this->pointStyle = value;
    }
}

void Charts::PointDecoration::preRender(TR3DUtils::RenderContext & context, const RenderArgs & args)
{
    
}

void Charts::PointDecoration::render(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
    if(TR_VERIFY(abscissaAxis && ordinateAxis)) {
        beforeRender(context, args);
        const glm::float_t xScreenValue = abscissaAxis->dataToScreen(this->value.abscissa);
        const glm::float_t yScreenValue = ordinateAxis->dataToScreen(this->value.ordinate);
        if(abscissaAxis->inScreenRange(xScreenValue) && ordinateAxis->inScreenRange(yScreenValue)) {
            const glm::vec2 xAxisDirection = abscissaAxis->getAxisDirection();
            const glm::vec2 yAxisDirection = ordinateAxis->getAxisDirection();
            const std::shared_ptr<TR3DUtils::PointRenderer> pointRenderer = context.getPointRenderer();
            pointRenderer->bind();
            pointRenderer->bindModelViewProjection(args.projection);
            pointRenderer->bindColor(Utils::colorToVec4(getColor()) * Utils::opacityToAlpha(getOpacity()));
            pointRenderer->bindSize(this->pointStyle.diameter * args.contentScaleFactor);
            pointRenderer->drawPoint(glm::vec3((xAxisDirection * xScreenValue) + (yAxisDirection * yScreenValue), 0.f));
        }
        afterRender(context, args);
    }
}

#endif
