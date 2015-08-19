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

#ifndef TRCharts_Impl_SteppedAreaSeriesImpl_hpp
#define TRCharts_Impl_SteppedAreaSeriesImpl_hpp

#include <TRCharts/SteppedAreaSeries.hpp>
#include <TRCharts/AreaSeries.hpp>
#include <TRCharts/Impl/AreaSeriesImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class SteppedAreaSeries : public GeneratedSteppedAreaSeries
	{
	public:
		SteppedAreaSeries(void);

		virtual ~SteppedAreaSeries(void);
        
        virtual void createVertices(std::vector<glm::vec2> & vertices);
        
        virtual void createDatumColors(std::vector<glm::vec4> & colours);
        
        virtual glm::float_t getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const;
        
        virtual ScalarDatum blendDatums(const ScalarDatum & a, const ScalarDatum & b, const double t) const;
        
	private:

	};
}

#endif