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

#ifndef TRCharts_Impl_DateAxisImpl_hpp
#define TRCharts_Impl_DateAxisImpl_hpp

#include <TRCharts/DateAxis.hpp>
#include <TRCharts/DateInterval.hpp>
#include <TRCharts/Impl/ContinuousAxisImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class DateTickCalculator;

	
	class DateAxis : public GeneratedDateAxis
	{
	public:
		DateAxis(void);

		virtual ~DateAxis(void);
        
		virtual const std::shared_ptr<Charts::DateFormatter> & getTickFormatter(void) const;
        
		virtual void setTickFormatter(const std::shared_ptr<Charts::DateFormatter> & value);
        
		virtual const std::shared_ptr<Charts::DateTickCalculator> & getTickCalculator(void) const;

		virtual void setTickCalculator(const std::shared_ptr<Charts::DateTickCalculator> & value);
        
        virtual double getOffsetSeconds(void) const;
        
        virtual void setOffsetSeconds(double value);
        
		virtual bool update(const RenderArgs & args);
        
		virtual std::vector<Tick> getTicks(void) const;
        
        const Charts::DateInterval & getTickInterval(void) const;
        
        static const double MAXIMUM_TICKS;
        
    protected:
        Tick createTick(double value) const;
        
        DateInterval tickInterval;
        std::vector<Tick> ticks;
        
    private:
        double offsetSeconds;
		std::shared_ptr<Charts::DateFormatter> tickFormatter;
		std::shared_ptr<Charts::DateTickCalculator> tickCalculator;
	};
}

#endif