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

#ifndef TRCharts_Impl_SeriesImpl_hpp
#define TRCharts_Impl_SeriesImpl_hpp

#include <TRCharts/Series.hpp>
#include <TRCharts/ChartElement.hpp>
#include <TRCharts/Color.hpp>
#include <TRCharts/LineStyle.hpp>
#include <TRCharts/Point.hpp>
#include <TRCharts/Impl/ChartElementImpl.hpp>
#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Impl/RenderArgs.hpp>

#include <TR3DUtils/RenderContext.hpp>

namespace Charts
{
	class ContinuousAxis;
    
	class Series : public GeneratedSeries
	{
	public:
		Series(void);

		virtual ~Series(void);
        
        virtual void attach(void);
        
        virtual void detach(void);
        
		virtual const std::shared_ptr<Charts::ContinuousAxis> & getOrdinateAxis(void) const;

		virtual void setOrdinateAxis(const std::shared_ptr<Charts::ContinuousAxis> & value);
        
		virtual void setColor(const Charts::Color & color);
        
		virtual const Charts::Color & getColor(void) const;
        
		//virtual bool isSelectable(void) const;
        
		//virtual void setSelectable(bool value);
        
		//virtual bool select(const Charts::Point & position);
        
		virtual void markDirty(void);
        
		virtual void markRangeDirty(const Charts::IndexRange & range);
        
		virtual void loadData(void) = 0;
        
        virtual void writeDataRangeToAxes(void) const = 0;
        
		virtual bool update(const RenderArgs & args) = 0;

		virtual void preRender(TR3DUtils::RenderContext & context, const RenderArgs & args) = 0;

		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const = 0;
        
        virtual void dispose(void) = 0;
        
        /*virtual bool preSelect(const Charts::Point & position, SelectInfo & selectInfo) const = 0;
        
        virtual bool select(size_t datumIndex) = 0;
        
        virtual void deselect(void) = 0;*/
        
        static std::string getSimpleSeriesProgramName(void);
        
        static std::pair<std::string, std::string> getDatumColorsProgramDefine(void);
        
        static std::pair<std::string, std::string> getConstantPointSizeProgramDefine(void);
        
        static std::pair<std::string, std::string> getDatumPointSizeProgramDefine(void);
        
        static std::pair<std::string, std::string> getConstantLineParamsProgramDefine(void);
        
        static std::pair<std::string, std::string> getDatumLineParamsProgramDefine(void);
        
        virtual glm::vec2 createLineParams(const LineStyle lineStyle) const;
    
    protected:
        virtual void beforeRender(TR3DUtils::RenderContext & context, const RenderArgs & args)const;
        
        virtual void afterRender(TR3DUtils::RenderContext & context, const RenderArgs & args) const;
        
    public:
        static const long NO_SELECTION;
    
    protected:
		std::vector<IndexRange> dirtyRanges;
        
	private:
		std::shared_ptr<Charts::ContinuousAxis> ordinateAxis;
        Color color;
        bool selectable;
	};
}

#endif
