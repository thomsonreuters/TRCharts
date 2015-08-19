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

#ifndef Charts_Impl_IndexRangeImpl_hpp
#define Charts_Impl_IndexRangeImpl_hpp

#include <TRCharts/IndexRange.hpp>

namespace Charts
{
	
	struct IndexRange : public GeneratedIndexRange
	{
		IndexRange(void);

		IndexRange(long begin, long end);

		static long length(const Charts::IndexRange & indexRange);

		static bool valid(const Charts::IndexRange & indexRange);

		static bool validWithin(const Charts::IndexRange & indexRange, const Charts::IndexRange & otherIndexRange);

		static bool positive(const Charts::IndexRange & indexRange);

		static Charts::IndexRange merge(const Charts::IndexRange & indexRange, const Charts::IndexRange & otherIndexRange);
        
		static Charts::IndexRange clamp(const Charts::IndexRange & indexRange, const Charts::IndexRange & withinIndexRange);

		static bool overlap(const Charts::IndexRange & indexRange, const Charts::IndexRange & otherIndexRange);
	};
}

#endif