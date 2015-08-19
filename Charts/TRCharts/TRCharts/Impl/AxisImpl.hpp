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

#ifndef TRCharts_Impl_AxisImpl_hpp
#define TRCharts_Impl_AxisImpl_hpp

#include <TRCharts/Axis.hpp>
#include <TRCharts/Range.hpp>
#include <TRCharts/Edge.hpp>
#include <TRCharts/ChartElement.hpp>
#include <TRCharts/GestureState.hpp>
#include <TRCharts/DataTransform.hpp>
#include <TRCharts/Label.hpp>
#include <TRCharts/Impl/ChartElementImpl.hpp>
#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Impl/RenderArgs.hpp>

#include <TR3DUtils/RenderContext.hpp>

#include <array>

namespace Charts
{	
	class Axis : public GeneratedAxis
	{
    public:
        struct Tick
        {
            double position;
            std::string label;
        };
        
	public:
		Axis(void);
        
		virtual ~Axis(void);
        
        virtual void attach(void);
        
        virtual void detach(void);

		virtual Charts::Edge getEdge(void) const;

		virtual void setEdge(Charts::Edge value);
        
		virtual const std::shared_ptr<Charts::Label>  & getTitle(void) const;
        
		virtual void setTitle(const std::shared_ptr<Charts::Label>  & value);
        
		virtual void setAxisColor(const Charts::Color & value);

		virtual const Charts::Color & getAxisColor(void) const;

		virtual void setAxisLineStyle(const LineStyle & value);

		virtual const LineStyle & getAxisLineStyle(void) const;
        
		virtual bool isGridVisible(void) const;
        
		virtual void setGridVisible(bool value);
        
		virtual void setGridColor(const Charts::Color & value);
        
		virtual const Charts::Color & getGridColor(void) const;
        
		virtual void setGridLineStyle(const LineStyle & value);
        
		virtual const LineStyle & getGridLineStyle(void) const;
        
		virtual void setTickColor(const Charts::Color & value);
        
		virtual const Charts::Color & getTickColor(void) const;
        
		virtual void setTickLineStyle(const LineStyle & value);
        
		virtual const LineStyle & getTickLineStyle(void) const;
        
		virtual double getTickOffset(void) const;
        
		virtual void setTickOffset(double value);
        
		virtual double getTickSize(void) const;

		virtual void setTickSize(double value);
        
		virtual const Charts::Color & getTickLabelColor(void) const;
        
		virtual void setTickLabelColor(const Charts::Color & value);
        
		virtual const Charts::Font & getTickLabelFont(void) const;
        
		virtual void setTickLabelFont(const Charts::Font & value);
        
		virtual double getTickLabelMaxSize(void) const;
        
		virtual void setTickLabelMaxSize(double value);
        
		virtual double getTickLabelOffset(void) const;
        
		virtual void setTickLabelOffset(double value);
        
        virtual void resetDataRange(void);
        
		virtual void calculateDataRange(void);
        
        virtual void relayout(void);
        
		virtual bool update(const RenderArgs & args);
        
        // TODO: should return a reference
		virtual std::vector<Tick> getTicks(void) const = 0;

		virtual void preRender(TR3DUtils::RenderContext & context, const RenderArgs & args);
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const;
        
		virtual void renderGrid(TR3DUtils::RenderContext & context, const RenderArgs & args) const;

		virtual void renderAxis(TR3DUtils::RenderContext & context, const RenderArgs & args) const;

		virtual glm::float_t getScreenStart(void) const;
        
		virtual double getScreenLength(void) const;
        
		virtual glm::vec2 getAxisDirection(void) const;
        
        virtual glm::float_t getGridStart(void) const;
        
        virtual glm::float_t getGridLength(void) const;
        
		virtual glm::vec2 getGridDirection(void) const;
        
        virtual const DataTransform & getRenderTransform(void) const;
        
        virtual void dampMotion(void);
        
        virtual double getInternalMargin(void) const;
        
        virtual Range getLayoutRange(void) const = 0;
        
        virtual void dispose(void);
        
        static std::array<Charts::Range, 2> getLayoutRanges(const std::vector<std::shared_ptr<Charts::Axis>> & axisList);
                
	protected:
        glm::float_t screenStart;
        glm::float_t screenLength;
        glm::vec2 screenSize;
        Margin margin;
        glm::vec2 axisStart;
        glm::float_t gridStart;
        glm::float_t gridLength;
        glm::vec2 tickAlign;
        glm::vec2 titleAlign;
        glm::float_t titleRotate;
        bool gridVisible;
        DataTransform renderTransform;
        Margin titleMarginOffsetMask;

	private:        
        std::shared_ptr<Charts::Label> title;
		Charts::Edge edge;
		Charts::Color axisColor;
        Charts::LineStyle axisLineStyle;
		Charts::Color gridColor;
		Charts::LineStyle gridLineStyle;
		Charts::Color tickColor;
		Charts::LineStyle tickLineStyle;
		double tickOffset;
		double tickSize;
        Charts::Color tickLabelColor;
        Charts::Font tickLabelFont;
        double tickLabelMaxSize;
        double tickLabelOffset;
        bool dirty;

		std::shared_ptr<const TR3DUtils::RenderProgram> program;
		std::shared_ptr<TR3DUtils::RenderVAO> vao;
	};
}

#endif
