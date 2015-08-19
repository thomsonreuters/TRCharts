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

#ifndef TRCharts_Impl_CandlestickSeriesImpl_cpp
#define TRCharts_Impl_CandlestickSeriesImpl_cpp

#include <TRCharts/Impl/CandlestickSeriesImpl.hpp>


Charts::CandlestickSeries::CandlestickSeries(void)
{
}


Charts::CandlestickSeries::~CandlestickSeries(void)
{
}

void Charts::CandlestickSeries::preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args)
{
}

void Charts::CandlestickSeries::render(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
}

Charts::Range Charts::CandlestickSeries::getAbscissaRange(void) const
{
    return Range();
}

Charts::Range Charts::CandlestickSeries::getOrdinateRange(void) const
{
    return Range();
}

glm::float_t Charts::CandlestickSeries::getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const
{
    return std::numeric_limits<glm::float_t>::max();
}

Charts::OHLCDatum Charts::CandlestickSeries::blendDatums(const Charts::OHLCDatum & a, const Charts::OHLCDatum & b, const double t) const
{
    return a;
}

Charts::Range Charts::CandlestickSeries::getDatumOrdinateRange(const Charts::OHLCDatum & datum) const
{
    return Range();
}

void Charts::CandlestickSeries::dispose(void)
{
    GeneratedCandlestickSeries::dispose();
}

#endif
