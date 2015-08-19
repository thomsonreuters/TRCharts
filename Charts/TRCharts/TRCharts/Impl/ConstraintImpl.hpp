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

#ifndef Charts_Impl_ConstraintImpl_hpp
#define Charts_Impl_ConstraintImpl_hpp

#include <TRCharts/Constraint.hpp>
#include <TRCharts/Attachable.hpp>
#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Transform.hpp>
#include <TRCharts/Size.hpp>

namespace Charts
{
    class Chart;
	class ConstraintBehaviour;

	
	class Constraint : public GeneratedConstraint
	{
	public:
		Constraint(void);

		virtual ~Constraint(void);

		virtual const std::shared_ptr<Charts::ConstraintBehaviour> & getBehaviour(void) const;

		virtual void setBehaviour(const std::shared_ptr<Charts::ConstraintBehaviour> & value);
        
		virtual Charts::Transform apply(const std::shared_ptr<Charts::Chart> & chart, const Charts::Size & size, const Charts::Transform & transform) const;
        
	private:
		std::shared_ptr<Charts::ConstraintBehaviour> behaviour;
	};
}

#endif