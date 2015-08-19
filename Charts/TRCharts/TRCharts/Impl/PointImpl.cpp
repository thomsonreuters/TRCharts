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

#include <TRCharts/Impl/PointImpl.hpp>


Charts::Point::Point(void)
	:GeneratedPoint()
{
}


Charts::Point::Point(double x, double y)
	:GeneratedPoint(x, y)
{
}

Charts::Point Charts::Point::add(const Point & point, const Point & otherPoint)
{
    return Point(point.x + otherPoint.x, point.y + otherPoint.y);
}

Charts::Point Charts::Point::subtract(const Point & point, const Point & otherPoint)
{
    return Point(point.x - otherPoint.x, point.y - otherPoint.y);
}

Charts::Point Charts::Point::multiply(const Point & point, const Point & otherPoint)
{
    return Point(point.x * otherPoint.x, point.y * otherPoint.y);
}

Charts::Point Charts::Point::divide(const Point & point, const Point & otherPoint)
{
    return Point(point.x / otherPoint.x, point.y / otherPoint.y);
}
