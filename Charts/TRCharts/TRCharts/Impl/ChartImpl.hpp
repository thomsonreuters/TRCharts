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

#ifndef TRCharts_Impl_ChartImpl_hpp
#define TRCharts_Impl_ChartImpl_hpp

#include <TRCharts/Chart.hpp>
#include <TRCharts/Color.hpp>
#include <TRCharts/Margin.hpp>
#include <TRCharts/GestureState.hpp>
#include <TRCharts/Impl/LabelImpl.hpp>
#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Impl/RenderArgs.hpp>
#include <TRCharts/Impl/DrawableImpl.hpp>

#include <TR3DUtils/RenderContext.hpp>

namespace Charts
{
	class Series;
	class Axis;
    class Decoration;
    class Animation;
    class Constraint;
	
	class Chart : public GeneratedChart
	{
	public:
		Chart(void);

		virtual ~Chart(void);

		virtual const std::shared_ptr<Charts::Label> & getTitle(void) const;

		virtual void setTitle(const std::shared_ptr<Charts::Label> & value);

		virtual const Charts::Color & getBackgroundColor(void) const;

		virtual void setBackgroundColor(const Charts::Color & value);
        
		virtual const Charts::Color & getFillColor(void) const;
        
		virtual void setFillColor(const Charts::Color & value);
        
		virtual const Charts::Margin & getMargin(void) const;

		virtual void setMargin(const Charts::Margin & value);
        
		virtual const Size & getSize(void) const;
        
		virtual double getContentScaleFactor(void) const;
        
		virtual void resize(const Size & size, double contentScaleFactor);
        
		virtual void relayout(void);
        
		virtual ResizeMode getResizeMode(void) const;
        
		virtual void setResizeMode(ResizeMode value);
        
		virtual Transform getTransform(void) const;
        
		virtual void setTransform(const Transform & value);
        
		virtual const std::vector<std::shared_ptr<Charts::Axis>> & getAxisList(void) const;

		virtual const std::vector<std::shared_ptr<Charts::Series>> & getSeriesList(void) const;
        
		virtual const std::vector<std::shared_ptr<Charts::Decoration>> & getDecorationList(void) const;
        
		virtual const std::vector<std::shared_ptr<Charts::Constraint>> & getConstraintList(void) const;
        
		virtual const std::vector<std::shared_ptr<Charts::Animation>> & getActiveAnimationList(void) const;
        
		virtual void addAxis(const std::shared_ptr<Charts::Axis> & axis);

		virtual void addSeries(const std::shared_ptr<Charts::Series> & series);
        
		virtual void addConstraint(const std::shared_ptr<Charts::Constraint> & constraint);
        
		virtual void addDecoration(const std::shared_ptr<Charts::Decoration> & decoration);
        
		virtual void removeAxis(const std::shared_ptr<Charts::Axis> & axis);

		virtual void removeSeries(const std::shared_ptr<Charts::Series> & series);
        
		virtual void removeDecoration(const std::shared_ptr<Charts::Decoration> & decoration);
        
        virtual void removeConstraint(const std::shared_ptr<Charts::Constraint> & constraint);
        
		virtual void applyAnimation(const std::shared_ptr<Charts::Animation> & animation);
        
		virtual void preUpdate(void);
        
		virtual bool update(void);
        
        virtual void applyAnimations(void);
        
        virtual void applyConstraints(void);
        
		virtual void preRender(void) const;

		virtual void render(void) const;
        
		virtual void renderRegion(const Charts::Point & position, const Charts::Size & size, double scale) const;
        
		virtual void dispose(void);
        
		//virtual bool select(const Charts::Point & position);
        
		//virtual void handleTranslation(Charts::GestureState state, const Charts::Point & startPosition, const Charts::Point & translation);
        
		//virtual void handleScale(Charts::GestureState state, const Charts::Point & startPosition, double scale, const Charts::Point & primaryAxis);
        
        virtual void handleTouches(const std::vector<Charts::Touch> & touches);
        
        virtual const std::vector<Charts::Touch> & getLastTouches(void) const;
        
        virtual bool versionChanged(void) const;
        
        virtual void markVersion(void);
        
    protected:
        virtual void renderImpl(const RenderArgs & renderArgs) const;
        Version lastCleanVersion;
        
	private:
        std::shared_ptr<Charts::Label> title;
		Charts::Color backgroundColor;
		Charts::Color fillColor;
		Charts::Margin margin;
        Charts::Size size;
        double contentScaleFactor;
        ResizeMode resizeMode;
		std::vector<std::shared_ptr<Charts::Axis>> axisList;
		std::vector<std::shared_ptr<Charts::Series>> seriesList;
		std::vector<std::shared_ptr<Charts::Decoration>> decorationList;
		std::vector<std::shared_ptr<Charts::Constraint>> constraintList;
        std::vector<std::shared_ptr<Charts::Animation>> activeAnimationList;
        std::vector<Charts::Touch> lastTouches;
        
        glm::dvec2 tmpTranslateOffset;
        glm::dvec2 tmpScaleOffset;
        glm::dvec2 tmpScale;
        
        glm::dvec2 tmpConstraintOffset;
        
        glm::dvec2 offset;
        glm::dvec2 scale;

		RenderArgs renderArgs;
		const std::shared_ptr<TR3DUtils::RenderContext> renderContext;
        
        double lastTick;
        
		mutable bool preUpdated;
		mutable bool preRendered;
        bool updated;
        
        bool doRelayout;
	};
}

#endif
