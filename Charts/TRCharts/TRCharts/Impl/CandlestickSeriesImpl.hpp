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

#ifndef TRCharts_Impl_CandlestickSeriesImpl_hpp
#define TRCharts_Impl_CandlestickSeriesImpl_hpp

#include <TRCharts/CandlestickSeries.hpp>
#include <TRCharts/ContinuousSeries.hpp>
#include <TRCharts/OHLCDatum.hpp>
#include <TRCharts/Impl/ContinuousSeriesImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class CandlestickSeries : public GeneratedCandlestickSeries
	{
	public:
		CandlestickSeries(void);

		virtual ~CandlestickSeries(void);
        
		virtual void preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args);
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const;
        
        virtual Range getAbscissaRange(void) const;
        
        virtual Range getOrdinateRange(void) const;
        
        virtual glm::float_t getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const;
        
        virtual OHLCDatum blendDatums(const OHLCDatum & a, const OHLCDatum & b, const double t) const;
        
        virtual Range getDatumOrdinateRange(const OHLCDatum & datum) const;
        
        virtual void dispose(void);
        
	private:
	};
}

#endif
