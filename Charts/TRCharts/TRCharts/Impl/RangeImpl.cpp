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

#include <TRCharts/Impl/RangeImpl.hpp>

#include <limits>


Charts::Range::Range(void)
	:GeneratedRange()
{
}


Charts::Range::Range(double min, double max)
	:GeneratedRange(min, max)
{
}

double Charts::Range::length(const Charts::Range & range)
{
    return range.max - range.min;
}

bool Charts::Range::valid(const Charts::Range & range)
{
	return range.min <= range.max;
}

bool Charts::Range::positive(const Charts::Range & range)
{
	return range.min < range.max;
}

Charts::Range Charts::Range::merge(const Charts::Range & range, const Charts::Range & otherRange)
{
	return Range(std::min(range.min, otherRange.min), std::max(range.max, otherRange.max));
}

Charts::Range Charts::Range::clamp(const Charts::Range & range, const Charts::Range & withinRange)
{
	return Range(std::max(withinRange.min, range.min), std::min(withinRange.max, range.max));
}

bool Charts::Range::overlap(const Charts::Range & range, const Charts::Range & otherRange)
{
	return std::max(range.min, otherRange.min) <= std::min(range.max, otherRange.max);
}

Charts::Range Charts::Range::identity(void)
{
	return Range(std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());
}

