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

#ifndef TRCharts_Impl_ContinuousAxisImpl_hpp
#define TRCharts_Impl_ContinuousAxisImpl_hpp

#include <TRCharts/ContinuousAxis.hpp>
#include <TRCharts/Axis.hpp>
#include <TRCharts/Range.hpp>
#include <TRCharts/Impl/AxisImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class RangeCalculator;

	
	class ContinuousAxis : public GeneratedContinuousAxis
	{
	public:
		ContinuousAxis(void);

		virtual ~ContinuousAxis(void);

		/*virtual const std::shared_ptr<Charts::ContinuousTickGenerator> & getTickGenerator(void) const;

		virtual void setTickGenerator(const std::shared_ptr<Charts::ContinuousTickGenerator> & value);*/

        virtual const DataTransform & getValueTransform(void) const;
        
        virtual void setValueTransform(const DataTransform & value);
        
		virtual const std::shared_ptr<Charts::AxisLayout> & getLayout(void) const;
        
		virtual void setLayout(const std::shared_ptr<Charts::AxisLayout> & value);
        
		virtual const std::shared_ptr<Charts::RangeCalculator> & getRangeCalculator(void) const;

		virtual void setRangeCalculator(const std::shared_ptr<Charts::RangeCalculator> & value);
        
		virtual double screenToData(double screen) const;
        
		virtual double dataToScreen(double data) const;
        
        // get the default (pre global offset/scale) screen position for the data value.
        virtual double dataToLayout(double data) const;
        
        virtual void resetDataRange(void);
        
        virtual void calculateDataRange(void);
        
        virtual void writeDataRange(const Range & range);
        
        virtual const Range & getDataRange(void) const;
        
        virtual void relayout(void);
        
		virtual bool update(const RenderArgs & args);
        
        virtual bool inScreenRange(const double screen) const;
        
        virtual const Range & getScreenDataRange(void) const;
        
        virtual Charts::DataTransform getRenderValueTransform(void) const;
        
        /** nonvirtual deliberately? */
        Tick createTick(double value, const std::string & label) const;
        
        //virtual double getRenderValueOffset(void) const;
        
        //virtual double getRenderValueScale(void) const;
        
        virtual Range getLayoutRange(void) const;
        
	protected:
        Range rawDataRange;
        Range dataRange;
        Range screenDataRange;
        bool relayoutRequired;
        
	private:
		std::shared_ptr<Charts::AxisLayout> layout;
		std::shared_ptr<Charts::RangeCalculator> rangeCalculator;
        DataTransform valueTransform;
	};
}

#endif
