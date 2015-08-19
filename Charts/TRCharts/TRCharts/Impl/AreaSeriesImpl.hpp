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

#ifndef TRCharts_Impl_AreaSeriesImpl_hpp
#define TRCharts_Impl_AreaSeriesImpl_hpp

#include <TRCharts/AreaSeries.hpp>
#include <TRCharts/ContinuousSeries.hpp>
#include <TRCharts/ScalarDatum.hpp>
#include <TRCharts/Impl/ContinuousSeriesImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class AreaSeries : public GeneratedAreaSeries
	{
	public:
		AreaSeries(void);

		virtual ~AreaSeries(void);
        
        virtual void createVertices(std::vector<glm::vec2> & vertices);
        
        virtual void createDatumColors(std::vector<glm::vec4> & colours);
        
		virtual void preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args);
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const;
        
        virtual Range getAbscissaRange(void) const;
        
        virtual Range getOrdinateRange(void) const;
        
        virtual glm::float_t getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const;
        
        virtual ScalarDatum blendDatums(const ScalarDatum & a, const ScalarDatum & b, const double t) const;
        
        virtual Range getDatumOrdinateRange(const ScalarDatum & datum) const;
        
        virtual void dispose(void);
        
	private:        
		std::shared_ptr<const TR3DUtils::RenderProgram> program;
		std::shared_ptr<TR3DUtils::RenderVAO> vao;
	};
}

#endif