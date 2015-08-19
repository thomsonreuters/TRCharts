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

#ifndef TRCharts_Impl_AbstractNumberAxisImpl_hpp
#define TRCharts_Impl_AbstractNumberAxisImpl_hpp

#include <TRCharts/AbstractNumberAxis.hpp>
#include <TRCharts/ContinuousAxis.hpp>
#include <TRCharts/Impl/ContinuousAxisImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class NumberFormatter;

	
	class AbstractNumberAxis : public GeneratedAbstractNumberAxis
	{
	public:
		AbstractNumberAxis(void);

		virtual ~AbstractNumberAxis(void);

		virtual const std::shared_ptr<Charts::NumberFormatter> & getTickFormatter(void) const;

		virtual void setTickFormatter(const std::shared_ptr<Charts::NumberFormatter> & value);
        
    protected:
        Tick createTick(const double value) const;
        
	private:
		std::shared_ptr<Charts::NumberFormatter> tickFormatter;
	};
}

#endif