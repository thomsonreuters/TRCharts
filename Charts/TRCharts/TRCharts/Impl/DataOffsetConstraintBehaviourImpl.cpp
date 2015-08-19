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

#ifndef Charts_Impl_DataOffsetConstraintBehaviourImpl_cpp
#define Charts_Impl_DataOffsetConstraintBehaviourImpl_cpp

#include <TRCharts/Impl/DataOffsetConstraintBehaviourImpl.hpp>
#include <TRCharts/Axis.hpp>
#include <TRCharts/Chart.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>

#include <array>
#include <algorithm>


Charts::DataOffsetConstraintBehaviour::DataOffsetConstraintBehaviour(void)
    :GeneratedDataOffsetConstraintBehaviour(), axes(), edges({Edge::Left, Edge::Right, Edge::Bottom, Edge::Top}), multiplier(1.0)
{
}


Charts::DataOffsetConstraintBehaviour::~DataOffsetConstraintBehaviour(void)
{
}


const std::vector<std::shared_ptr<Charts::Axis>> & Charts::DataOffsetConstraintBehaviour::getAxes(void) const
{
	return this->axes;
}


void Charts::DataOffsetConstraintBehaviour::setAxes(const std::vector<std::shared_ptr<Charts::Axis>> & value)
{
	this->axes = value;
}


const std::vector<Charts::Edge> & Charts::DataOffsetConstraintBehaviour::getEdges(void) const
{
	return this->edges;
}


void Charts::DataOffsetConstraintBehaviour::setEdges(const std::vector<Charts::Edge> & value)
{
	this->edges = value;
}


double Charts::DataOffsetConstraintBehaviour::getMultiplier(void) const
{
	return this->multiplier;
}


void Charts::DataOffsetConstraintBehaviour::setMultiplier(double value)
{
	this->multiplier = value;
}

namespace
{
    double mixUntilApproxEqual(double from, double to, double factor, double epsilon)
    {
        const double mixed = glm::mix(from, to, factor);
        if(Charts::Utils::approxEqual(mixed, to, epsilon)) {
            return to;
        } else {
            return mixed;
        }
    }
}

Charts::Transform Charts::DataOffsetConstraintBehaviour::apply(const std::shared_ptr<Charts::Chart> & chart, const Charts::Size & size, const Charts::Transform & transform) const
{
    const double OFFSET_MIX_EPSILON = 1.0;
    const size_t directions = 2;
    const size_t edgeStride = 2;
    glm::dvec2 offset = Utils::pointToDVec2Flipped(transform.offset, 0.0);
    glm::dvec2 scale = Utils::pointToDVec2(transform.scale);
    const glm::dvec2 areaSize = Utils::sizeToDVec2(size);
    const std::array<Range, 2> layoutRanges = Axis::getLayoutRanges(axes);
    const Edge edges[4] = {Edge::Left, Edge::Right, Edge::Bottom, Edge::Top};
    for(size_t direction = 0; direction != directions; ++direction) {
        const Range & layoutRange = layoutRanges[direction];
        const DataTransform renderTransform(offset[direction], scale[direction]);
        const Range screenDataRange = DataTransform::applyRange(renderTransform, layoutRange);
        const double screenDataRangeLength = Range::length(screenDataRange);
        const double areaLength = areaSize[direction];
        // do not apply constraint if screen range is too small, user should also apply a scale constraint to restrict this.
        if(screenDataRangeLength > 0.0 && screenDataRangeLength >= areaLength) {
            const double areaLength = areaSize[direction];
            if((screenDataRange.min) > 0.0) {
                const Edge edge = edges[(direction * edgeStride) + 0];
                if(affectEdge(edge)) {
                    const double targetOffset = offset[direction] - screenDataRange.min;
                    offset[direction] = mixUntilApproxEqual(offset[direction], targetOffset, multiplier, OFFSET_MIX_EPSILON);
                }
            } else if((screenDataRange.max) < areaLength) {
                const Edge edge = edges[(direction * edgeStride) + 1];
                if(affectEdge(edge)) {
                    const double targetOffset = offset[direction] - (screenDataRange.max - areaLength);
                    offset[direction] = mixUntilApproxEqual(offset[direction], targetOffset, multiplier, OFFSET_MIX_EPSILON);
                }
            }
        }
    }
	return Transform(Utils::dvec2ToPointFlipped(offset, 0.0), Utils::dvec2ToPoint(scale));
}

bool Charts::DataOffsetConstraintBehaviour::affectEdge(Charts::Edge edge) const
{
    return std::find(edges.begin(), edges.end(), edge) != edges.end();
}


#endif
