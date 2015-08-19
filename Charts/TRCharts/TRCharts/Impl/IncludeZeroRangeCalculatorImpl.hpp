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

#ifndef Charts_Impl_IncludeZeroRangeCalculatorImpl_hpp
#define Charts_Impl_IncludeZeroRangeCalculatorImpl_hpp

#include <TRCharts/IncludeZeroRangeCalculator.hpp>
#include <TRCharts/Range.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class RangeCalculator;

	
	class IncludeZeroRangeCalculator : public GeneratedIncludeZeroRangeCalculator
	{
	public:
		IncludeZeroRangeCalculator(void);

		virtual ~IncludeZeroRangeCalculator(void);

		virtual const std::shared_ptr<Charts::RangeCalculator> & getRangeCalculator(void) const;

		virtual void setRangeCalculator(const std::shared_ptr<Charts::RangeCalculator> & value);

		virtual Charts::Range calculateRange(const Charts::Range & dataRange) const;

	private:
		std::shared_ptr<Charts::RangeCalculator> rangeCalculator;
	};
}

#endif