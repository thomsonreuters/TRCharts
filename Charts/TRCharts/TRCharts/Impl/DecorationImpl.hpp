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

#ifndef TRCharts_Impl_DecorationImpl_hpp
#define TRCharts_Impl_DecorationImpl_hpp

#include <TRCharts/Decoration.hpp>
#include <TRCharts/Color.hpp>
#include <TRCharts/ChartElement.hpp>
#include <TRCharts/Impl/ChartElementImpl.hpp>
#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Impl/RenderArgs.hpp>

#include <TR3DUtils/RenderContext.hpp>

namespace Charts
{

	
	class Decoration : public GeneratedDecoration
	{
	public:
		Decoration(void);

		virtual ~Decoration(void);
        
		virtual const Charts::Color & getColor(void) const;
        
		virtual void setColor(const Charts::Color & value);
        
		virtual void preRender(TR3DUtils::RenderContext & context, const RenderArgs & args) = 0;
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const = 0;

        virtual bool update(const RenderArgs & args);
        
    protected:
        virtual void beforeRender(TR3DUtils::RenderContext & context, const RenderArgs & args)const;
        
        virtual void afterRender(TR3DUtils::RenderContext & context, const RenderArgs & args) const;
        
	private:
		Charts::Color color;
	};
}

#endif
