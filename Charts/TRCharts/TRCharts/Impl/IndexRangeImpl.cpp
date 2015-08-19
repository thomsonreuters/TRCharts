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

#include <TRCharts/Impl/IndexRangeImpl.hpp>


Charts::IndexRange::IndexRange(void)
	:GeneratedIndexRange()
{
}


Charts::IndexRange::IndexRange(long begin, long end)
	:GeneratedIndexRange(begin, end)
{
}

long Charts::IndexRange::length(const Charts::IndexRange & indexRange)
{
    return indexRange.end - indexRange.begin;
}

bool Charts::IndexRange::valid(const Charts::IndexRange & indexRange)
{
	return indexRange.begin <= indexRange.end;
}

bool Charts::IndexRange::validWithin(const Charts::IndexRange & indexRange, const Charts::IndexRange & otherIndexRange)
{
	return valid(indexRange) && (indexRange.begin >= otherIndexRange.begin) && (indexRange.end <= otherIndexRange.end);
}

bool Charts::IndexRange::positive(const Charts::IndexRange & indexRange)
{
	return indexRange.begin < indexRange.end;
}

Charts::IndexRange Charts::IndexRange::merge(const Charts::IndexRange & indexRange, const Charts::IndexRange & otherIndexRange)
{
	return IndexRange(std::min(indexRange.begin, otherIndexRange.begin), std::max(indexRange.end, otherIndexRange.end));
}

Charts::IndexRange Charts::IndexRange::clamp(const Charts::IndexRange & indexRange, const Charts::IndexRange & withinIndexRange)
{
	return IndexRange(std::max(withinIndexRange.begin, indexRange.begin), std::min(withinIndexRange.end, indexRange.end));
}

bool Charts::IndexRange::overlap(const Charts::IndexRange & indexRange, const Charts::IndexRange & otherIndexRange)
{
	return std::max(indexRange.begin, otherIndexRange.begin) <= std::min(indexRange.end, otherIndexRange.end);
}
