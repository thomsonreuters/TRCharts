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

#include <TRCharts/Impl/DataTransformImpl.hpp>

#include <TRCharts/Range.hpp>

Charts::DataTransform::DataTransform(void)
	:GeneratedDataTransform()
{
}


Charts::DataTransform::DataTransform(double offset, double scale)
	:GeneratedDataTransform(offset, scale)
{
}

Charts::DataTransform Charts::DataTransform::concatenate(const Charts::DataTransform & dataTransform, const Charts::DataTransform & otherDataTransform)
{
    const double offset = (otherDataTransform.offset * dataTransform.scale) + dataTransform.offset;
    const double scale = dataTransform.scale * otherDataTransform.scale;
    return DataTransform(offset, scale);
}

Charts::DataTransform Charts::DataTransform::invert(const Charts::DataTransform & dataTransform)
{
    const double scale = 1.0 / dataTransform.scale;
    const double offset = -dataTransform.offset * scale;
    return DataTransform(offset, scale);
}

double Charts::DataTransform::apply(const Charts::DataTransform & dataTransform, double value)
{
    return (value * dataTransform.scale) + dataTransform.offset;
}

Charts::Range Charts::DataTransform::applyRange(const Charts::DataTransform & dataTransform, const Range & range)
{
    return Range(apply(dataTransform, range.min), apply(dataTransform, range.max));
}

double Charts::DataTransform::unapply(const Charts::DataTransform & dataTransform, double value)
{
    return (value - dataTransform.offset) / dataTransform.scale;
}

Charts::Range Charts::DataTransform::unapplyRange(const Charts::DataTransform & dataTransform, const Range & range)
{
    return Range(unapply(dataTransform, range.min), unapply(dataTransform, range.max));
}