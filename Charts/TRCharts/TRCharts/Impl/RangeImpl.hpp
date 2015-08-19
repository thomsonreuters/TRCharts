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

#ifndef Charts_Impl_RangeImpl_hpp
#define Charts_Impl_RangeImpl_hpp

#include <TRCharts/Range.hpp>

namespace Charts
{
	
	struct Range : public GeneratedRange
	{
		Range(void);

		Range(double min, double max);

		static double length(const Charts::Range & range);

		static bool valid(const Charts::Range & range);

		static bool positive(const Charts::Range & range);

		static Charts::Range merge(const Charts::Range & range, const Charts::Range & otherRange);
        
		static Charts::Range clamp(const Charts::Range & range, const Charts::Range & withinRange);
        
		static bool overlap(const Charts::Range & range, const Charts::Range & otherRange);
        
        static Charts::Range identity(void);
	};
}

#endif