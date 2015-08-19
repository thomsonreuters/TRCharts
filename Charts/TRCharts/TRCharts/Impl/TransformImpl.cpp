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

#include <TRCharts/Impl/TransformImpl.hpp>


Charts::Transform::Transform(void)
	:GeneratedTransform()
{
}


Charts::Transform::Transform(const Charts::Point & offset, const Charts::Point & scale)
	:GeneratedTransform(offset, scale)
{
}

Charts::Transform Charts::Transform::concatenate(const Charts::Transform & transform, const Charts::Transform & otherTransform)
{
    const Point offset = Point::add(Point::multiply(otherTransform.offset, transform.scale), transform.offset);
    const Point scale = Point::multiply(transform.scale, otherTransform.scale);
    return Transform(offset, scale);
}