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

#ifndef Charts_Impl_DataScaleConstraintBehaviourImpl_cpp
#define Charts_Impl_DataScaleConstraintBehaviourImpl_cpp

#include <TRCharts/Impl/DataScaleConstraintBehaviourImpl.hpp>
#include <TRCharts/Axis.hpp>
#include <TRCharts/Chart.hpp>
#include <TRCharts/Impl/Utils.hpp>


Charts::DataScaleConstraintBehaviour::DataScaleConstraintBehaviour(void)
	:GeneratedDataScaleConstraintBehaviour(), axes()
{
}


Charts::DataScaleConstraintBehaviour::~DataScaleConstraintBehaviour(void)
{
}


const std::vector<std::shared_ptr<Charts::Axis>> & Charts::DataScaleConstraintBehaviour::getAxes(void) const
{
	return this->axes;
}


void Charts::DataScaleConstraintBehaviour::setAxes(const std::vector<std::shared_ptr<Charts::Axis>> & value)
{
	this->axes = value;
}


Charts::Transform Charts::DataScaleConstraintBehaviour::apply(const std::shared_ptr<Charts::Chart> & chart, const Charts::Size & size, const Charts::Transform & transform) const
{
    const size_t directions = 2;
    glm::dvec2 offset = Utils::pointToDVec2Flipped(transform.offset, 0.0);
    glm::dvec2 scale = Utils::pointToDVec2(transform.scale);
    const glm::dvec2 areaSize = Utils::sizeToDVec2(size);
    const std::array<Range, 2> layoutRanges = Axis::getLayoutRanges(axes);
    for(size_t direction = 0; direction != directions; ++direction) {
        const Range & layoutRange = layoutRanges[direction];
        const DataTransform renderTransform(offset[direction], scale[direction]);
        const Range screenDataRange = DataTransform::applyRange(renderTransform, layoutRange);
        const double screenDataRangeLength = Range::length(screenDataRange);
        const double areaLength = areaSize[direction];
        if(screenDataRangeLength > 0.0) {
            if(screenDataRangeLength < areaLength) {
                const double targetScale = areaLength / Range::length(layoutRange);
                scale[direction] = targetScale;
                offset[direction] = -layoutRange.min * targetScale;
            }
        }
    }
    return Transform(Utils::dvec2ToPointFlipped(offset, 0.0), Utils::dvec2ToPoint(scale));
}


#endif