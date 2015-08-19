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

#ifndef TRCharts_Impl_AxisImpl_cpp
#define TRCharts_Impl_AxisImpl_cpp

#include <TRCharts/Impl/AxisImpl.hpp>
#include <TRCharts/Impl/LabelImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/TextRenderer.hpp>
#include <TR3DUtils/LineRenderer.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/Log.hpp>

#include <cassert>
#include <glm/gtc/matrix_transform.hpp>

Charts::Axis::Axis(void)
: edge(Edge::Left), title(), axisColor(), axisLineStyle(1.0, LineMode::Solid), gridColor(), gridLineStyle(1.0, LineMode::Solid), tickColor(), tickOffset(0), tickSize(0), tickLineStyle(1.0, LineMode::Solid), tickLabelOffset(0), tickLabelColor(), titleAlign(), titleRotate(), gridVisible(false), tickLabelFont(), renderTransform(0.0, 1.0), dirty(true), tickLabelMaxSize()
{
}

Charts::Axis::~Axis(void)
{
	if (title) {
		title->detach();
	}
}

Charts::Edge Charts::Axis::getEdge(void) const
{
	return this->edge;
}

void Charts::Axis::setEdge(Charts::Edge value)
{
	this->edge = value;
	this->dirty = true;
}

const std::shared_ptr<Charts::Label> & Charts::Axis::getTitle(void) const
{
	return this->title;
}

void Charts::Axis::setTitle(const std::shared_ptr<Charts::Label> & value)
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

void Charts::Axis::setAxisColor(const Charts::Color & value)
{
	if (this->axisColor != value) {
		newVersion();
		this->axisColor = value;
	}
}

const Charts::Color & Charts::Axis::getAxisColor(void) const
{
	return this->axisColor;
}

void Charts::Axis::setAxisLineStyle(const Charts::LineStyle & value)
{
	if (this->axisLineStyle != value) {
		newVersion();
		this->axisLineStyle = value;
        if(value.mode != LineMode::Solid) {
            TR3DUtils::Log::Warn("Non-solid axis line style is not supported");
        }
	}
}

const Charts::LineStyle & Charts::Axis::getAxisLineStyle(void) const
{
	return this->axisLineStyle;
}

bool Charts::Axis::isGridVisible(void) const
{
	return this->gridVisible;
}

void Charts::Axis::setGridVisible(bool value)
{
	if (this->gridVisible != value) {
		newVersion();
		this->gridVisible = value;
	}
}

void Charts::Axis::setGridColor(const Charts::Color & value)
{
	if (this->gridColor != value) {
		newVersion();
		this->gridColor = value;
	}
}

const Charts::Color & Charts::Axis::getGridColor(void) const
{
	return this->gridColor;
}

void Charts::Axis::setGridLineStyle(const Charts::LineStyle & value)
{
	if (this->gridLineStyle != value) {
		newVersion();
		this->gridLineStyle = value;
        if(value.mode != LineMode::Solid) {
            TR3DUtils::Log::Warn("Non-solid grid line style is not supported");
        }
	}
}

const Charts::LineStyle & Charts::Axis::getGridLineStyle(void) const
{
	return this->gridLineStyle;
}

void Charts::Axis::setTickColor(const Charts::Color & value)
{
	if (this->tickColor != value) {
		newVersion();
		this->tickColor = value;
	}
}

const Charts::Color & Charts::Axis::getTickColor(void) const
{
	return this->tickColor;
}

void Charts::Axis::setTickLineStyle(const Charts::LineStyle & value)
{
	if (this->tickLineStyle != value) {
		newVersion();
		this->tickLineStyle = value;
        if(value.mode != LineMode::Solid) {
            TR3DUtils::Log::Warn("Non-solid tick line style is not supported");
        }
	}
}

const Charts::LineStyle & Charts::Axis::getTickLineStyle(void) const
{
	return this->tickLineStyle;
}

double Charts::Axis::getTickOffset(void) const
{
	return this->tickOffset;
}

void Charts::Axis::setTickOffset(double value)
{
	if (this->tickOffset != value) {
		newVersion();
		this->tickOffset = value;
	}
}

double Charts::Axis::getTickSize(void) const
{
	return this->tickSize;
}

void Charts::Axis::setTickSize(double value)
{
	if (this->tickSize != value) {
		newVersion();
		this->tickSize = value;
	}
}

const Charts::Color & Charts::Axis::getTickLabelColor(void) const
{
	return this->tickLabelColor;
}

void Charts::Axis::setTickLabelColor(const Charts::Color & value)
{
	if (this->tickLabelColor != value) {
		newVersion();
		this->tickLabelColor = value;
	}
}

const Charts::Font & Charts::Axis::getTickLabelFont(void) const
{
	return this->tickLabelFont;
}

void Charts::Axis::setTickLabelFont(const Charts::Font & value)
{
	if (this->tickLabelFont != value) {
		newVersion();
		this->tickLabelFont = value;
	}
}

double Charts::Axis::getTickLabelMaxSize(void) const
{
	return this->tickLabelMaxSize;
}

void Charts::Axis::setTickLabelMaxSize(double value)
{
	if (this->tickLabelMaxSize != value) {
		newVersion();
		this->tickLabelMaxSize = value;
	}
}

double Charts::Axis::getTickLabelOffset(void) const
{
	return this->tickLabelOffset;
}

void Charts::Axis::setTickLabelOffset(double value)
{
	if (this->tickLabelOffset != value) {
		newVersion();
		this->tickLabelOffset = value;
	}
}

void Charts::Axis::resetDataRange(void)
{
}

void Charts::Axis::calculateDataRange(void)
{
}

void Charts::Axis::relayout(void)
{
}

bool Charts::Axis::update(const RenderArgs & args)
{
	//TR_ASSERT(isEnabled());
	bool changed = versionChanged();
	if (title) {
		changed = changed || title->versionChanged();
	}
	if (screenSize != args.screenSize || this->margin != args.margin || dirty) {
		screenSize = args.screenSize;
		margin = args.margin;
		titleMarginOffsetMask.left = titleMarginOffsetMask.right = titleMarginOffsetMask.bottom = titleMarginOffsetMask.top = 0;
		switch (edge) {
		case Edge::Left:
			screenStart = margin.bottom;
			screenLength = screenSize.y - (margin.bottom + margin.top);
			axisStart = glm::vec2(margin.left, margin.bottom);
			gridStart = margin.left;
			gridLength = screenSize.x - (margin.left + margin.right);
			tickAlign = glm::vec2(1.f, .5f);
			titleAlign = glm::vec2(.5f, 0.f);
			titleRotate = 90;
			titleMarginOffsetMask.bottom = 1.0;
			break;
		case Edge::Right:
			screenStart = margin.bottom;
			screenLength = screenSize.y - (margin.bottom + margin.top);
			axisStart = glm::vec2(screenSize.x - margin.right, margin.bottom);
			gridStart = screenSize.x - margin.right;
			gridLength = screenSize.x - (margin.left + margin.right);
			tickAlign = glm::vec2(0.f, .5f);
			titleAlign = glm::vec2(.5f, 0.f);
			titleRotate = -90;
			titleMarginOffsetMask.bottom = 1.0;
			break;
		case Edge::Bottom:
			screenStart = margin.left;
			screenLength = screenSize.x - (margin.left + margin.right);
			axisStart = glm::vec2(margin.left, margin.bottom);
			gridStart = margin.bottom;
			gridLength = screenSize.y - (margin.bottom + margin.top);
			tickAlign = glm::vec2(.5f, 1.f);
			titleAlign = glm::vec2(0.5f, 1.f);
			titleMarginOffsetMask.bottom = 1.0;
			break;
		case Edge::Top:
			screenStart = margin.left;
			screenLength = screenSize.x - (margin.left + margin.right);
			axisStart = glm::vec2(margin.left, screenSize.y - margin.top);
			gridStart = screenSize.y - margin.top;
			gridLength = screenSize.y - (margin.bottom + margin.top);
			tickAlign = glm::vec2(.5f, 0.f);
			titleAlign = glm::vec2(0.5f, 0.f);
			titleMarginOffsetMask.top = 1.0;
			break;
		}
		changed = true;
	}
	const double newRenderOffset = glm::dot(glm::dvec2(getAxisDirection()), args.offset);
	const double newRenderScale = glm::dot(glm::dvec2(getAxisDirection()), args.scale);
    const DataTransform newRenderTransform(newRenderOffset, newRenderScale);
	if (this->renderTransform != newRenderTransform) {
		this->renderTransform = newRenderTransform;
		changed = true;
	}
	markVersion();
	if (title) {
		title->markVersion();
	}
	dirty = false;
	return changed;
}

void Charts::Axis::preRender(TR3DUtils::RenderContext & context, const RenderArgs & args)
{
 	//TR_ASSERT(isEnabled());
	if (!vao) {
		const std::vector<glm::float_t> vertices = { 0.f, 1.f };
		const std::shared_ptr<TR3DUtils::RenderBuffer> buffer = context.createBuffer(1, vertices.size(), &(vertices[0]));
		vao = context.createVAO( { buffer }, GL_LINES);
	}
	if (!program) {
		program = context.getNamedProgram("trcharts.axis", TR3DUtils::RenderProgram::DefineMap());
	}
}

void Charts::Axis::render(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
	renderGrid(context, args);
	renderAxis(context, args);
}

void Charts::Axis::renderGrid(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
	//TR_ASSERT(isEnabled());
	if (gridVisible && TR_VERIFY(vao && program)) {
        const double alpha =  Utils::opacityToAlpha(getOpacity());
		program->bind();
		program->bindUniform("modelViewProjection", args.projection);
		glLineWidth(this->gridLineStyle.thickness * args.contentScaleFactor);
		program->bindUniform("axis", getGridDirection() * gridLength);
		program->bindUniform("lineColor", Utils::colorToVec4(gridColor) * alpha);
		const std::vector<Tick> ticks = getTicks();
		for (const Tick & tick : ticks) {
			const glm::vec2 pos = axisStart + getAxisDirection() * glm::float_t(tick.position);
			program->bindUniform("start", TR3DUtils::Utils::roundToPixels(pos, args.contentScaleFactor));
			vao->draw();
		}
	}
}

void Charts::Axis::renderAxis(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
	//TR_ASSERT(isEnabled());
	if (TR_VERIFY(vao && program)) {
        const double alpha =  Utils::opacityToAlpha(getOpacity());
        const glm::vec2 axisDirection = getAxisDirection();
        const glm::vec2 gridDirection = getGridDirection();
		const std::vector<Tick> ticks = getTicks();
		program->bind();
		program->bindUniform("modelViewProjection", args.projection);
		glLineWidth(this->tickLineStyle.thickness * args.contentScaleFactor);
		program->bindUniform("axis", gridDirection * glm::float_t(tickSize));
		program->bindUniform("lineColor", Utils::colorToVec4(tickColor) * alpha);
		for (const Tick & tick : ticks) {
			const glm::vec2 pos = axisStart + (axisDirection * glm::float_t(tick.position)) - (gridDirection * glm::float_t(tickOffset + tickSize));
			program->bindUniform("start", TR3DUtils::Utils::roundToPixels(pos, args.contentScaleFactor));
			vao->draw();
		}
		program->bindUniform("start", TR3DUtils::Utils::roundToPixels(axisStart, args.contentScaleFactor));
		program->bindUniform("axis", axisDirection * screenLength);
		program->bindUniform("lineColor", Utils::colorToVec4(axisColor));
		glLineWidth(this->axisLineStyle.thickness * args.contentScaleFactor);
		vao->draw();
		const std::shared_ptr<TR3DUtils::TextRenderer> textRenderer = context.getTextRenderer();
		for (const Tick & tick : ticks) {
			const glm::vec2 pos = axisStart + (axisDirection * glm::float_t(tick.position)) - (gridDirection * glm::float_t(tickOffset + tickSize + tickLabelOffset));
			textRenderer->drawText(args.projection, tick.label, tickLabelFont.name, tickLabelFont.size, glm::vec3(pos, 0.f), 0, tickAlign, Utils::colorToVec4(tickLabelColor) * alpha, args.contentScaleFactor);
		}
		if (title && title->isEnabled() && title->isVisible()) {
			// TODO move into label::render method
			const std::string & label = title->getText();
			const Charts::Font & font = title->getFont();
			const Charts::Margin & margin = title->getMargin();
			// ugly
			const double marginOffset = (margin.left * titleMarginOffsetMask.left) + (margin.right * titleMarginOffsetMask.right) + (margin.bottom * titleMarginOffsetMask.bottom) + (margin.top * titleMarginOffsetMask.top);
			textRenderer->drawText(args.projection, label, font.name, font.size, glm::vec3(axisStart + (axisDirection * screenLength * .5f) + gridDirection * -glm::float_t(tickOffset + tickSize + tickLabelOffset + tickLabelMaxSize + marginOffset), 0.f), titleRotate, titleAlign, Utils::colorToVec4(title->getColor()), args.contentScaleFactor);
		}
	}
}

glm::float_t Charts::Axis::getScreenStart(void) const
{
	return screenStart;
}

double Charts::Axis::getScreenLength(void) const
{
	return screenLength;
}

glm::vec2 Charts::Axis::getAxisDirection(void) const
{
    switch (this->edge) {
		case Edge::Left:
		case Edge::Right:
			return glm::vec2(0, 1);
		case Edge::Bottom:
		case Edge::Top:
			return glm::vec2(1, 0);
        default:
            TR_ASSERT_NOT_REACHED();
            return glm::vec2(1, 0);
    }
}

glm::vec2 Charts::Axis::getGridDirection(void) const
{
    switch (this->edge) {
		case Edge::Left:
			return glm::vec2(1, 0);
		case Edge::Right:
			return glm::vec2(-1, 0);
		case Edge::Bottom:
			return glm::vec2(0, 1);
		case Edge::Top:
			return glm::vec2(0, -1);
        default:
            TR_ASSERT_NOT_REACHED();
            return glm::vec2(1, 0);
    }
}

glm::float_t Charts::Axis::getGridLength(void) const
{
	return gridLength;
}

glm::float_t Charts::Axis::getGridStart(void) const
{
	return gridStart;
}

const Charts::DataTransform & Charts::Axis::getRenderTransform(void) const
{
	return renderTransform;
}

void Charts::Axis::dispose(void)
{
    vao.reset();
    program.reset();
}

void Charts::Axis::attach(void)
{
    GeneratedAxis::attach();
    dispose();
}

void Charts::Axis::detach(void)
{
    GeneratedAxis::detach();
    dispose();
}

void Charts::Axis::dampMotion(void)
{

}

double Charts::Axis::getInternalMargin(void) const
{
	double margin = tickOffset + tickSize + tickLabelOffset + tickLabelMaxSize;
	if (title && title->isEnabled()) {
		margin += title->getFullHeight();
	}
	return margin;
}

std::array<Charts::Range, 2> Charts::Axis::getLayoutRanges(const std::vector<std::shared_ptr<Charts::Axis>> & axisList)
{
    std::array<Charts::Range, 2> result;
    result[0] = Charts::Range::identity();
    result[1] = Charts::Range::identity();
    for (auto axis : axisList) {
        if(TR_VERIFY(axis)) {
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
    }
    return result;
}

namespace
{
	bool staticInit = [](void) -> bool {
		return TR3DUtils::RenderContext::registerRenderProgram("trcharts.axis", TR3DUtils::RenderProgramDef(
						R"**(
attribute float weight;

varying lowp vec4 f_color_n;

uniform mediump vec2 start;
uniform mediump vec2 axis;
uniform mediump mat4 modelViewProjection;
uniform mediump vec4 lineColor;

void main()
{

	gl_Position = modelViewProjection * vec4(start + (weight * axis), 0, 1);
    f_color_n = lineColor;
}
)**",
						R"**(
varying lowp vec4 f_color_n;
void main()
{	
	gl_FragColor = f_color_n;
}
)**",
						{	"weight"},
						{	"start", "axis", "modelViewProjection","lineColor"}));
	}();
}

#endif
