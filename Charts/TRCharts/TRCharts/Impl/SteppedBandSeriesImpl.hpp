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

#ifndef TRCharts_Impl_SteppedBandSeriesImpl_hpp
#define TRCharts_Impl_SteppedBandSeriesImpl_hpp

#include <TRCharts/SteppedBandSeries.hpp>
#include <TRCharts/BandSeries.hpp>
#include <TRCharts/Impl/BandSeriesImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class SteppedBandSeries : public GeneratedSteppedBandSeries
	{
	public:
		SteppedBandSeries(void);

		virtual ~SteppedBandSeries(void);
        
        virtual void createVertices(std::vector<glm::vec2> & vertices);
        
        virtual void createDatumColors(std::vector<glm::vec4> & colors);
        
        virtual RangeDatum blendDatums(const RangeDatum & a, const RangeDatum & b, const double t) const;
        
	private:
	};
}

#endif