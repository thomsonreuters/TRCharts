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

#ifndef TRCharts_Impl_ChartElementImpl_hpp
#define TRCharts_Impl_ChartElementImpl_hpp

#include <TRCharts/ChartElement.hpp>
#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Impl/RenderArgs.hpp>
#include <TRCharts/Impl/DrawableImpl.hpp>

#include <TR3DUtils/RenderContext.hpp>

namespace Charts
{

	
	class ChartElement : public GeneratedChartElement
	{
	public:
		ChartElement(void);

		virtual ~ChartElement(void);
        
        virtual void attach(void);
        
		virtual long getDrawOrder(void) const;
        
		virtual void setDrawOrder(long value);
                        
		virtual void preRender(TR3DUtils::RenderContext & context, const RenderArgs & args) = 0;
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const = 0;
        
	private:
        long drawOrder;
	};
}

#endif
