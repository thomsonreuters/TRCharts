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

#ifndef TRCharts_Impl_SteppedLineSeriesImpl_hpp
#define TRCharts_Impl_SteppedLineSeriesImpl_hpp

#include <TRCharts/SteppedLineSeries.hpp>
#include <TRCharts/LineSeries.hpp>
#include <TRCharts/Impl/LineSeriesImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class SteppedLineSeries : public GeneratedSteppedLineSeries
	{
	public:
		SteppedLineSeries(void);

		virtual ~SteppedLineSeries(void);
        
        virtual void createVertices(const IndexRange & indexRange, std::vector<glm::vec2> & vertices) const;
        
        virtual void createDatumColors(const IndexRange & indexRange, std::vector<glm::vec4> & colors) const;
        
        virtual void createDatumLineParams(const IndexRange & indexRange, std::vector<glm::vec2> & lineParams) const;
        
        virtual ScalarDatum blendDatums(const ScalarDatum & a, const ScalarDatum & b, const double t) const;
        
	private:
	};
}

#endif