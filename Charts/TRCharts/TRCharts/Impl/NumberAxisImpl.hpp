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

#ifndef TRCharts_Impl_NumberAxisImpl_hpp
#define TRCharts_Impl_NumberAxisImpl_hpp

#include <TRCharts/NumberAxis.hpp>
#include <TRCharts/AbstractNumberAxis.hpp>
#include <TRCharts/Impl/AbstractNumberAxisImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class NumberTickCalculator;

	
	class NumberAxis : public GeneratedNumberAxis
	{
	public:
		NumberAxis(void);

		virtual ~NumberAxis(void);
        
		virtual const std::shared_ptr<Charts::NumberTickCalculator> & getTickCalculator(void) const;

		virtual void setTickCalculator(const std::shared_ptr<Charts::NumberTickCalculator> & value);
        
		virtual bool update(const RenderArgs & args);
        
		virtual std::vector<Tick> getTicks(void) const;
        
        virtual double getTickInterval(void) const;
        
        static const double MAXIMUM_TICKS;
        
    protected:
        double tickInterval;
        std::vector<Tick> ticks;
        
	private:        
		std::shared_ptr<Charts::NumberTickCalculator> tickCalculator;
	};
}

#endif