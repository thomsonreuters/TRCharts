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

#ifndef TRCharts_Impl_FixedRangeCalculatorImpl_hpp
#define TRCharts_Impl_FixedRangeCalculatorImpl_hpp

#include <TRCharts/FixedRangeCalculator.hpp>
#include <TRCharts/RangeCalculator.hpp>
#include <TRCharts/Range.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class FixedRangeCalculator : public GeneratedFixedRangeCalculator
	{
	public:
		FixedRangeCalculator(void);

		virtual ~FixedRangeCalculator(void);

		virtual const Charts::Range & getRange(void) const;

		virtual void setRange(const Charts::Range & value);

		virtual Charts::Range calculateRange(const Charts::Range & dataRange) const;

	private:
		Charts::Range range;
	};
}

#endif