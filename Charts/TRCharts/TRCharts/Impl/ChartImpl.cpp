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

#ifndef TRCharts_Impl_ChartImpl_cpp
#define TRCharts_Impl_ChartImpl_cpp

#include <TRCharts/Impl/ChartImpl.hpp>
#include <TRCharts/Impl/AxisImpl.hpp>
#include <TRCharts/Impl/SeriesImpl.hpp>
#include <TRCharts/Impl/DecorationImpl.hpp>
#include <TRCharts/Impl/ConstraintImpl.hpp>
#include <TRCharts/Impl/AnimationImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TRCharts/Series.hpp>
#include <TRCharts/Axis.hpp>
#include <TRCharts/AnimationDelegate.hpp>
#include <TR3DUtils/Log.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/QuadRenderer.hpp>

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

//#include <array>

Charts::Chart::Chart(void)
		: renderContext(std::make_shared<TR3DUtils::RenderContext>()), preUpdated(false), preRendered(false), updated(false), lastCleanVersion(1), margin(), size(), contentScaleFactor(1.0), resizeMode(ResizeMode::Rescale), offset(0), scale(1.0), tmpTranslateOffset(0.0), tmpScaleOffset(0.0), tmpScale(1.0), tmpConstraintOffset(0.0), backgroundColor(), fillColor(), doRelayout(true), lastTick(0.0)
{
}

Charts::Chart::~Chart(void)
{
	if (title) {
		title->detach();
	}
	for (const auto & axis : axisList) {
		axis->detach();
	}
	for (const auto & series : seriesList) {
		series->detach();
	}
	for (const auto & decoration : decorationList) {
		decoration->detach();
	}
	for (const auto & constraint : constraintList) {
		constraint->detach();
	}
    for (const auto & animation : activeAnimationList) {
        animation->detach();
    }
}

const std::shared_ptr<Charts::Label> & Charts::Chart::getTitle(void) const
{
	return this->title;
}

void Charts::Chart::setTitle(const std::shared_ptr<Charts::Label> & value)
{
	if (this->title != value) {
		if (this->title) {
			this->title->detach();
		}
		if (value) {
			value->attach();
		}
		newVersion();
		this->title = value;
	}
}

const Charts::Color & Charts::Chart::getBackgroundColor(void) const
{
	return this->backgroundColor;
}

void Charts::Chart::setBackgroundColor(const Charts::Color & value)
{
	if (this->backgroundColor != value) {
		newVersion();
		this->backgroundColor = value;
	}
}

const Charts::Color & Charts::Chart::getFillColor(void) const
{
	return this->fillColor;
}

void Charts::Chart::setFillColor(const Charts::Color & value)
{
	if (this->fillColor != value) {
		newVersion();
		this->fillColor = value;
	}
}

const Charts::Margin & Charts::Chart::getMargin(void) const
{
	return this->margin;
}

void Charts::Chart::setMargin(const Charts::Margin & value)
{
	if (this->margin != value) {
		newVersion();
		this->margin = value;
	}
}

Charts::Transform Charts::Chart::getTransform(void) const
{
	return Charts::Transform(Utils::dvec2ToPointFlipped(offset, 0.0),
                             Utils::dvec2ToPoint(scale));
}

void Charts::Chart::setTransform(const Charts::Transform & value)
{
	const glm::dvec2 newOffset = Utils::pointToDVec2Flipped(value.offset, 0.0);
	const glm::dvec2 newScale = Utils::pointToDVec2(value.scale);
	if (this->offset != newOffset || this->scale != newScale) {
		newVersion();
		this->offset = newOffset;
        this->scale = newScale;
	}
}

const std::vector<std::shared_ptr<Charts::Axis>> & Charts::Chart::getAxisList(void) const
{
	return this->axisList;
}

const std::vector<std::shared_ptr<Charts::Series>> & Charts::Chart::getSeriesList(void) const
{
	return this->seriesList;
}

const std::vector<std::shared_ptr<Charts::Decoration>> & Charts::Chart::getDecorationList(void) const
{
	return this->decorationList;
}

const std::vector<std::shared_ptr<Charts::Constraint>> & Charts::Chart::getConstraintList(void) const
{
	return this->constraintList;
}

const std::vector<std::shared_ptr<Charts::Animation>> & Charts::Chart::getActiveAnimationList(void) const
{
	return this->activeAnimationList;
}

const Charts::Size & Charts::Chart::getSize(void) const
{
	return this->size;
}

double Charts::Chart::getContentScaleFactor(void) const
{
	return this->contentScaleFactor;
}

void Charts::Chart::resize(const Charts::Size & size, double contentScaleFactor)
{
	if (this->size != size || this->contentScaleFactor != contentScaleFactor) {
		newVersion();
		this->size = size;
		this->contentScaleFactor = contentScaleFactor;
	}
}

void Charts::Chart::relayout(void)
{
    newVersion();
    this->doRelayout = true;
}

Charts::ResizeMode Charts::Chart::getResizeMode(void) const
{
	return this->resizeMode;
}

void Charts::Chart::setResizeMode(Charts::ResizeMode value)
{
	if (this->resizeMode != value) {
		newVersion();
		this->resizeMode = value;
	}
}

void Charts::Chart::addAxis(const std::shared_ptr<Charts::Axis> & axis)
{
    if(TR_VERIFY(axis)) {
        axis->attach();
        newVersion();
        this->axisList.push_back(axis);
    }
}

void Charts::Chart::addSeries(const std::shared_ptr<Charts::Series> & series)
{
    if(TR_VERIFY(series)) {
        series->attach();
        newVersion();
        this->seriesList.push_back(series);
    }
}

void Charts::Chart::addDecoration(const std::shared_ptr<Charts::Decoration> & decoration)
{
    if(TR_VERIFY(decoration)) {
        decoration->attach();
        newVersion();
        this->decorationList.push_back(decoration);
    }
}

void Charts::Chart::addConstraint(const std::shared_ptr<Charts::Constraint> & constraint)
{
    if(TR_VERIFY(constraint)) {
        constraint->attach();
        newVersion();
        this->constraintList.push_back(constraint);
    }
}

void Charts::Chart::removeAxis(const std::shared_ptr<Charts::Axis> & axis)
{
    if(TR_VERIFY(axis)) {
        const auto iter = std::find(axisList.begin(), axisList.end(), axis);
        if (iter != axisList.end()) {
            newVersion();
            (*iter)->detach();
            axisList.erase(iter);
        }
    }
}

void Charts::Chart::removeSeries(const std::shared_ptr<Charts::Series> & series)
{
    if(TR_VERIFY(series)) {
        const auto iter = std::find(seriesList.begin(), seriesList.end(), series);
        if (iter != seriesList.end()) {
            newVersion();
            (*iter)->detach();
            seriesList.erase(iter);
        }
    }
}

void Charts::Chart::removeDecoration(const std::shared_ptr<Charts::Decoration> & decoration)
{
    if(TR_VERIFY(decoration)) {
        const auto iter = std::find(decorationList.begin(), decorationList.end(), decoration);
        if (iter != decorationList.end()) {
            newVersion();
            (*iter)->detach();
            decorationList.erase(iter);
        }
    }
}

void Charts::Chart::removeConstraint(const std::shared_ptr<Charts::Constraint> & constraint)
{
    if(TR_VERIFY(constraint)) {
        const auto iter = std::find(constraintList.begin(), constraintList.end(), constraint);
        if (iter != constraintList.end()) {
            newVersion();
            (*iter)->detach();
            constraintList.erase(iter);
        }
    }
}

void Charts::Chart::applyAnimation(const std::shared_ptr<Charts::Animation> & animation)
{
    if(TR_VERIFY(animation)) {
        animation->attach();
        activeAnimationList.push_back(animation);
    }
}

/*void Charts::Chart::cancelAnimation(const std::shared_ptr<Charts::Animation> & animation, bool finish)
{
    if(TR_VERIFY(animation)) {
        auto iter = activeAnimations.end();
        for(auto tmp = activeAnimations.begin(); tmp != activeAnimations.end(); ++tmp) {
            if(tmp->second == animation) {
                iter = tmp;
                break;
            }
        }
        if (iter != activeAnimations.end()) {
            if (finish) {
#warning messy, review
                iter->first = -1;
            } else {
                iter->second->detach();
                activeAnimations.erase(iter);
            }
        }
    }
}

void Charts::Chart::cancelAllAnimations(bool finish)
{
    for(auto & record : activeAnimations) {
        if(finish) {
#warning messy, review
            record.first = -1;
        } else {
            if(TR_VERIFY(record.second)) {
                record.second->detach();
            }
        }
    }
    if(!finish) {
        activeAnimations.clear();
    }
}*/

namespace
{
	void addAxisInternalMargin(Charts::Margin & margin, const std::shared_ptr<Charts::Axis> & axis)
	{
		if (TR_VERIFY(axis)) {
			if (axis->isEnabled()) {
				const double tmp = axis->getInternalMargin();
				switch (axis->getEdge()) {
                    case Charts::Edge::Left:
                        margin.left = std::max(margin.left, tmp);
                        break;
                    case Charts::Edge::Right:
                        margin.right = std::max(margin.right, tmp);
                        break;
                    case Charts::Edge::Bottom:
                        margin.bottom = std::max(margin.bottom, tmp);
                        break;
                    case Charts::Edge::Top:
                        margin.top = std::max(margin.top, tmp);
                        break;
                    default:
                        TR_ASSERT_NOT_REACHED();
                        break;
				}
			}
		}
	}
    
    /*std::array<Charts::Range, 2> getLayoutRanges(const std::vector<std::shared_ptr<Charts::Axis>> & axisList)
    {
        std::array<Charts::Range, 2> result;
        result[0] = Charts::Range::identity();
        result[1] = Charts::Range::identity();
        for (auto axis : axisList) {
            const Charts::Range range = axis->getLayoutRange();
            switch (axis->getEdge()) {
                case Charts::Edge::Top:
                case Charts::Edge::Bottom:
                    result[0] = Charts::Range::merge(result[0], range);
                    break;
                case Charts::Edge::Left:
                case Charts::Edge::Right:
                    result[1] = Charts::Range::merge(result[1], range);
                    break;
                default:
                    TR_ASSERT_NOT_REACHED();
                    break;
            }
        }
        return result;
    }*/
}

void Charts::Chart::preUpdate(void)
{
	if (!preUpdated) {
		for (auto series : seriesList) {
			series->loadData();
		}
        for (auto axis : axisList) {
            axis->resetDataRange();
        }
        for (auto series : seriesList) {
            if (series->isEnabled()) {
                series->writeDataRangeToAxes();
            }
        }
        for (auto axis : axisList) {
            axis->calculateDataRange();
        }
		preUpdated = true;
	}
}

void Charts::Chart::applyAnimations(void)
{
    const double tick = ((double)clock()) / CLOCKS_PER_SEC;
    if(lastTick == 0.0) {
        lastTick = tick;
    }
    const double elapsed = (tick - lastTick);
    lastTick = tick;
    if(!activeAnimationList.empty() && elapsed > 0.0) {
        for(const auto & animation : activeAnimationList) {
            if(TR_VERIFY(animation)) {
                animation->update(elapsed);
            }
        }
        for(const auto & animation : activeAnimationList) {
            if(TR_VERIFY(animation)) {
                animation->postUpdate();
            }
        }
        std::vector<std::shared_ptr<Animation>> newActiveAnimationList;
        for(const auto & animation : activeAnimationList) {
            if(TR_VERIFY(animation)) {
                if(animation->doRemove()) {
                    animation->detach();
                } else {
                    newActiveAnimationList.push_back(animation);
                }
            }
        }
        activeAnimationList = newActiveAnimationList;
    }
}

void Charts::Chart::applyConstraints(void)
{
    Transform transform = this->getTransform();
    for(const auto & constraint : constraintList) {
        if(TR_VERIFY(constraint)) {
            transform = constraint->apply(getSharedPtr(), Utils::vec2ToSize(this->renderArgs.areaSize), transform);
        }
    }
    this->setTransform(transform);
}

#include <iostream>

bool Charts::Chart::update(void)
{
	preUpdate();
	const glm::float_t width = this->size.width;
	const glm::float_t height = this->size.height;
	if (!TR_VERIFY(width > 0.0 && height > 0.0)) {
		return false;
	}
	bool changed = false;
	if (title) {
		changed = changed || title->versionChanged();
	}
	Margin internalMargin;
	for (auto axis : axisList) {
		addAxisInternalMargin(internalMargin, axis);
	}
	renderArgs.margin = Margin::add(margin, internalMargin);

	if (renderArgs.screenSize.x != width || renderArgs.screenSize.y != height) {
        if(!doRelayout) {
            const glm::vec2 marginProjection(renderArgs.margin.left + renderArgs.margin.right, renderArgs.margin.top + renderArgs.margin.bottom);
            const glm::vec2 newSize(width - marginProjection.x, height - marginProjection.y);
            if (resizeMode == ResizeMode::Rescale) {
                if (renderArgs.screenSize.x > 0.0 && renderArgs.screenSize.y > 0.0) {
                    const glm::vec2 oldSize(renderArgs.screenSize.x - marginProjection.x, renderArgs.screenSize.y - marginProjection.y);
                    scale *= (newSize / oldSize);
                } else {
                    offset = glm::vec2(0.f);
                    scale = newSize;
                }
            } else if (resizeMode == ResizeMode::Relayout) {
                offset = glm::vec2(0.f);
                scale = newSize;
            }
        }
		renderArgs.screenSize = glm::vec2(width, height);
		renderArgs.contentScaleFactor = contentScaleFactor;
		renderArgs.projection = glm::ortho(0.f, renderArgs.screenSize.x, 0.f, renderArgs.screenSize.y, -1000.f, +1000.f);
	}
    
	if (glm::float_t(contentScaleFactor) != renderArgs.contentScaleFactor) {
		renderArgs.contentScaleFactor = contentScaleFactor;
	}

	renderArgs.areaStart = glm::vec2(renderArgs.margin.left, renderArgs.margin.bottom);
	renderArgs.areaSize = renderArgs.screenSize - glm::vec2(renderArgs.margin.left + renderArgs.margin.right, renderArgs.margin.top + renderArgs.margin.bottom);
    
    if (doRelayout) {
        offset = glm::dvec2(0.f);
        scale = renderArgs.areaSize;
        doRelayout = false;
    } else {
        applyAnimations();
        applyConstraints();
    }
    
    // must check this AFTER applying animations and constraints
    changed = changed || versionChanged();

	renderArgs.offset = offset;
	renderArgs.scale = scale;
    
	renderArgs.clearColor = Utils::colorToVec4(backgroundColor);
    
	for (auto axis : axisList) {
		//if (axis->isEnabled()) {
			changed |= axis->update(renderArgs);
		//}
	}
	for (auto series : seriesList) {
		//if (series->isEnabled()) {
			changed |= series->update(renderArgs);
		//}
	}
	for (auto decoration : decorationList) {
		//if (decoration->isEnabled()) {
			changed |= decoration->update(renderArgs);
		//}
	}
	if (!preRendered) {
		// we mark the chart as changed if it has not been pre-rendered, the purpose of the update changed value is
		// conditional rendering and if we update twice before calling render we will still need to render again.
		changed = true;
	}
    if(changed) {
        preRendered = false;
    }
	preUpdated = false;
	markVersion();
	if (title) {
		title->markVersion();
	}
	updated = true;
	return changed;
}

void Charts::Chart::preRender(void) const
{
	if (!TR_VERIFY(updated)) {
		return;
	}
	if (!preRendered) {
		renderContext->clearTrash();
		for (auto axis : axisList) {
			//if (axis->isEnabled()) {
				axis->preRender(*renderContext, renderArgs);
			//}
		}
		for (auto series : seriesList) {
			//if (series->isEnabled()) {
				series->preRender(*renderContext, renderArgs);
			//}
		}
		for (const auto decoration : decorationList) {
			//if (decoration->isEnabled()) {
				decoration->preRender(*renderContext, renderArgs);
			//}
		}
		preRendered = true;
	}
}

void Charts::Chart::render(void) const
{
	renderImpl(renderArgs);
}

void Charts::Chart::renderRegion(const Charts::Point & position, const Charts::Size & size, double scale) const
{
	RenderArgs tmpRenderArgs = renderArgs;

	const glm::vec2 halfExtents = (Utils::sizeToVec2(size) * 0.5f);    // * glm::vec2(1.f, -1.f);
	const glm::vec2 midPoint = Utils::pointToVec2Flipped(position, renderArgs.screenSize.y) + (halfExtents * glm::vec2(1.f, -1.f));

	const glm::vec2 scaledHalfExtents = halfExtents / glm::float_t(scale);

	const glm::vec2 lo = midPoint - scaledHalfExtents;
	const glm::vec2 hi = midPoint + scaledHalfExtents;

	tmpRenderArgs.projection = glm::ortho(lo.x, hi.x, lo.y, hi.y, -1000.f, +1000.f);
	tmpRenderArgs.contentScaleFactor *= scale;

	renderImpl(tmpRenderArgs);
}

void Charts::Chart::renderImpl(const RenderArgs & renderArgs) const
{
	if (!TR_VERIFY(updated)) {
		return;
	}
	preRender();
	glClearColor(renderArgs.clearColor.x, renderArgs.clearColor.y, renderArgs.clearColor.z, renderArgs.clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (fillColor.alpha > 0.0) {
		const std::shared_ptr<TR3DUtils::QuadRenderer> quadRenderer = renderContext->getQuadRenderer();
		quadRenderer->bind();
		quadRenderer->bindModelViewProjection(renderArgs.projection);
		quadRenderer->bindColor(Utils::colorToVec4(fillColor));
		quadRenderer->drawQuad(glm::vec3(renderArgs.areaStart, 0.0), renderArgs.areaSize);
	}
	for (const auto axis : axisList) {
		if (axis->isEnabled() && axis->isVisible()) {
			axis->renderGrid(*renderContext, renderArgs);
		}
	}
	std::vector<std::shared_ptr<ChartElement>> elements;
	elements.insert(elements.end(), seriesList.begin(), seriesList.end());
	elements.insert(elements.end(), decorationList.begin(), decorationList.end());
	std::stable_sort(elements.begin(), elements.end(), [](const std::shared_ptr<ChartElement> & a, const std::shared_ptr<ChartElement> & b) -> bool {
		return a->getDrawOrder() < b->getDrawOrder();
	});
	for (const auto element : elements) {
		if (element->isEnabled() && element->isVisible()) {
			element->render(*renderContext, renderArgs);
		}
	}
	for (const auto axis : axisList) {
		if (axis->isEnabled() && axis->isVisible()) {
			axis->renderAxis(*renderContext, renderArgs);
		}
	}
    glDisable(GL_BLEND);
}

void Charts::Chart::dispose(void)
{
    newVersion();
    for(const auto & axis : axisList) {
        axis->dispose();
    }
    for(const auto & series : seriesList) {
        series->dispose();
    }
	renderContext->dispose();
    preRendered = false;
}

#include <iostream>

/*void Charts::Chart::handleTranslation(Charts::GestureState state, const Charts::Point & startPosition, const Charts::Point & translation)
{
	newVersion();
	if (state == GestureState::Cancelled) {
		this->tmpTranslateOffset = glm::dvec2(0.0);
	} else if (state == GestureState::Ended) {
		this->offset += tmpTranslateOffset;
		this->tmpTranslateOffset = glm::dvec2(0.0);
	} else {
		this->tmpTranslateOffset = Utils::pointToDVec2Flipped(translation, 0.0);
        const std::array<Range, 2> layoutRanges = getLayoutRanges(axisList);
        for(size_t direction = 0; direction != 2; ++direction) {
            const double resultOffset = (this->tmpTranslateOffset[direction] + this->offset[direction]);
            const double resultScale = (this->scale[direction] * this->tmpScale[direction]);
            const DataTransform renderTransform(resultOffset, resultScale);
            const Range layoutRange = DataTransform::apply(renderTransform, layoutRanges[direction]);
            if(layoutRange.min > 0.0) {
                this->tmpTranslateOffset[direction] -= layoutRange.min;
            } else if(layoutRange.max < renderArgs.areaSize[direction]) {
                this->tmpTranslateOffset[direction] += (renderArgs.areaSize[direction] - layoutRange.max);
            }
        }
	}
}*/

/*void Charts::Chart::handleScale(Charts::GestureState state, const Charts::Point & startPosition, double scale, const Charts::Point & primaryAxis)
{
	newVersion();
	if (state == GestureState::Cancelled) {
		this->tmpScale = glm::dvec2(1.0);
		this->tmpScaleOffset = glm::dvec2(0.0);
	} else if (state == GestureState::Ended) {
		this->scale *= tmpScale;
		this->offset += tmpScaleOffset;
		this->tmpScale = glm::dvec2(1.0);
		this->tmpScaleOffset = glm::dvec2(0.0);
	} else {
		const glm::dvec2 rawPrimaryAxis = Utils::pointToDVec2Flipped(primaryAxis, 0.0);
		const glm::dvec2 xAxis = glm::dvec2(1.0, 0.0);
		const glm::dvec2 yAxis = glm::dvec2(0.0, 1.0);
		const double xProj = glm::mix(1.0, scale, glm::abs(glm::dot(xAxis, rawPrimaryAxis)));
		const double yProj = glm::mix(1.0, scale, glm::abs(glm::dot(yAxis, rawPrimaryAxis)));
		const glm::dvec2 newScale = ((xAxis * xProj) + (yAxis * yProj));
		const glm::dvec2 start = (Utils::pointToDVec2Flipped(startPosition, renderArgs.screenSize.y) - glm::dvec2(renderArgs.margin.left, renderArgs.margin.bottom));
		this->tmpScale = newScale;
        this->tmpScaleOffset = (-((start - this->offset) * newScale) + start) - this->offset;
        for(size_t direction = 0; direction != 2; ++direction) {
            if((this->tmpScale[direction] * this->scale[direction]) < renderArgs.areaSize[direction]) {
                this->tmpScale[direction] = renderArgs.areaSize[direction] / this->scale[direction];
            }
        }
        const std::array<Range, 2> layoutRanges = getLayoutRanges(axisList);
        for(size_t direction = 0; direction != 2; ++direction) {
            const double resultOffset = (this->tmpScaleOffset[direction] + this->offset[direction]);
            const double resultScale = (this->scale[direction] * this->tmpScale[direction]);
            const DataTransform renderTransform(resultOffset, resultScale);
            const Range layoutRange = DataTransform::apply(renderTransform, layoutRanges[direction]);
            if(layoutRange.min > 0.0) {
                this->tmpScaleOffset[direction] -= layoutRange.min;
            } else if(layoutRange.max < renderArgs.areaSize[direction]) {
                this->tmpScaleOffset[direction] += (renderArgs.areaSize[direction] - layoutRange.max);
            }
        }
	}
	//dampMotion();
}*/

namespace
{
    struct TransformedTouch
    {
        glm::dvec2 position;
        glm::dvec2 lastPosition;
    };
    
    std::vector<TransformedTouch> transformTouches(const std::vector<Charts::Touch> & touches, const Charts::RenderArgs & renderArgs)
    {
        std::vector<TransformedTouch> transformedTouches;
        const glm::dvec2 margin = glm::dvec2(renderArgs.margin.left, renderArgs.margin.bottom);
        for(const Charts::Touch & touch : touches) {
            const glm::dvec2 position = Charts::Utils::pointToDVec2Flipped(touch.position, renderArgs.screenSize.y) - margin;
            const glm::dvec2 lastPosition = Charts::Utils::pointToDVec2Flipped(touch.lastPosition, renderArgs.screenSize.y) - margin;
            transformedTouches.push_back(TransformedTouch{position, lastPosition});
        }
        return transformedTouches;
    }
    
    glm::dvec2 findPrimaryAxis(const std::vector<TransformedTouch> & touches)
    {
        double sumX = 0;
        double sumY = 0;
        double sumXY = 0;
        double sumXX = 0;
        double sumYY = 0;
        for(const TransformedTouch & touch : touches) {
            const glm::dvec2 & point = touch.position;
            sumX += point.x;
            sumY += point.y;
            sumXY += point.x * point.y;
            sumXX += point.x * point.x;
            sumYY += point.y * point.y;
        }
        const size_t n = touches.size();
        const double slopeX = (sumXY - ((sumX * sumY) / n)) / (sumXX - ((sumX * sumX) / n));
        const double slopeY = (sumXY - ((sumY * sumX) / n)) / (sumYY - ((sumY * sumY) / n));
        glm::dvec2 axis;
        if(isnan(slopeY) || (fabs(slopeX) > fabs(slopeY))) {
            axis = glm::dvec2(-1, slopeX);
        } else {
            axis = glm::dvec2(slopeY, -1);
        }
        axis = glm::normalize(axis);
        if(isnan(axis.x) || isnan(axis.y) || std::isinf(axis.x) || std::isinf(axis.y)) {
            axis = glm::dvec2(0, 1);
        }
        return axis;
    }
}

#include <iostream>

void Charts::Chart::handleTouches(const std::vector<Charts::Touch> & touches)
{
    const double LENGTH_EPSILON = 0.00000001;
    newVersion();
    const std::vector<TransformedTouch> transformedTouches = transformTouches(touches, renderArgs);
    const size_t numTouches = transformedTouches.size();
    if(numTouches > 0) {
        glm::dvec2 positionSum;
        glm::dvec2 lastPositionSum;
        for(const TransformedTouch & touch : transformedTouches) {
            positionSum += touch.position;
            lastPositionSum += touch.lastPosition;
        }
        const glm::dvec2 origin = positionSum / double(numTouches);
        const glm::dvec2 lastOrigin = lastPositionSum / double(numTouches);
        const glm::dvec2 translation = origin - lastOrigin;
        this->offset += translation;
        if(numTouches > 1) {
            const glm::dvec2 primaryAxis = findPrimaryAxis(transformedTouches);
            // TODO: messy, can probably project directly onto the primary axis.
            double radius = 0.0;
            double lastRadius = 0.0;
            for(const TransformedTouch & touch : transformedTouches) {
                radius = glm::max(radius, glm::length(touch.position - origin));
                lastRadius = glm::max(lastRadius, glm::length(touch.lastPosition -  lastOrigin));
            }
            const double scale = radius / lastRadius;
            const glm::dvec2 xAxis = glm::dvec2(1.0, 0.0);
            const glm::dvec2 yAxis = glm::dvec2(0.0, 1.0);
            const double xProj = glm::mix(1.0, scale, glm::abs(glm::dot(xAxis, primaryAxis)));
            const double yProj = glm::mix(1.0, scale, glm::abs(glm::dot(yAxis, primaryAxis)));
            glm::dvec2 scaleChange = ((xAxis * xProj) + (yAxis * yProj));
            for(size_t i = 0; i != 2; ++i) {
                if(TR3DUtils::Utils::approxEqual(scaleChange[i], 0.0, LENGTH_EPSILON)) {
                    scaleChange[i] = 1.0;
                }
            }
            this->scale *= scaleChange;
            this->offset += (-((origin - this->offset) * scaleChange) + origin) - this->offset;
        }
        lastTouches = touches;
    }
}

const std::vector<Charts::Touch> & Charts::Chart::getLastTouches(void) const
{
    return lastTouches;
}

bool Charts::Chart::versionChanged(void) const
{
	return lastCleanVersion != getVersion();
}

void Charts::Chart::markVersion(void)
{
	lastCleanVersion = getVersion();
}

#endif
