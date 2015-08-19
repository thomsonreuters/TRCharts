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

#include <TRCharts/Impl/MarginImpl.hpp>


Charts::Margin::Margin(void)
	:GeneratedMargin()
{
}


Charts::Margin::Margin(double left, double right, double bottom, double top)
	:GeneratedMargin(left, right, bottom, top)
{
}


Charts::Margin Charts::Margin::add(const Margin & margin, const Margin & otherMargin)
{
	return Charts::Margin(margin.left + otherMargin.left, margin.right + otherMargin.right, margin.bottom + otherMargin.bottom, margin.top + otherMargin.top);
}