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
/* NOTE: This file is autogenerated, do not edit this file directly.*/

#include <TRCharts/Size.hpp>
#include <TRCharts/Size.hpp>


Charts::GeneratedSize::GeneratedSize(void)
	:width(0.0), height(0.0)
{
}


Charts::GeneratedSize::GeneratedSize(double width, double height)
	:width(width), height(height)
{
}


bool Charts::GeneratedSize::operator==(const GeneratedSize & other) const
{
	bool result = true;
	result = result && (this->width == other.width);
	result = result && (this->height == other.height);
	return result;
}


bool Charts::GeneratedSize::operator!=(const GeneratedSize & other) const
{
	return !(*this == other);
}


std::ostream & Charts::operator<<(std::ostream & to, const GeneratedSize & from)
{
	to << "Size[";
	to << "width: " << from.width << ", ";
	to << "height: " << from.height;
	to << "]";
	return to;
}