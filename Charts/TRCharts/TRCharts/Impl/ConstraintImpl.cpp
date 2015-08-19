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

#ifndef Charts_Impl_ConstraintImpl_cpp
#define Charts_Impl_ConstraintImpl_cpp

#include <TRCharts/Impl/ConstraintImpl.hpp>
#include <TRCharts/ConstraintBehaviour.hpp>


Charts::Constraint::Constraint(void)
	:GeneratedConstraint(), behaviour()
{
}


Charts::Constraint::~Constraint(void)
{
}


const std::shared_ptr<Charts::ConstraintBehaviour> & Charts::Constraint::getBehaviour(void) const
{
	return this->behaviour;
}


void Charts::Constraint::setBehaviour(const std::shared_ptr<Charts::ConstraintBehaviour> & value)
{
	this->behaviour = value;
}

Charts::Transform Charts::Constraint::apply(const std::shared_ptr<Charts::Chart> & chart, const Charts::Size & size, const Charts::Transform & transform) const
{
    if(this->isEnabled() && this->behaviour) {
        return this->behaviour->apply(chart, size, transform);
    } else {
        return transform;
    }
}

#endif