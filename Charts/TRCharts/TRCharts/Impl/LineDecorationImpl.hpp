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

#ifndef TRCharts_Impl_LineDecorationImpl_hpp
#define TRCharts_Impl_LineDecorationImpl_hpp

#include <TRCharts/LineDecoration.hpp>
#include <TRCharts/Decoration.hpp>
#include <TRCharts/LineStyle.hpp>
#include <TRCharts/Impl/DecorationImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class ContinuousAxis;

	
	class LineDecoration : public GeneratedLineDecoration
	{
	public:
		LineDecoration(void);

		virtual ~LineDecoration(void);

		virtual const std::shared_ptr<Charts::ContinuousAxis> & getAxis(void) const;

		virtual void setAxis(const std::shared_ptr<Charts::ContinuousAxis> & value);

		virtual double getValue(void) const;

		virtual void setValue(double value);

		virtual const Charts::LineStyle & getLineStyle(void) const;

		virtual void setLineStyle(const Charts::LineStyle & value);
        
		virtual void preRender(TR3DUtils::RenderContext & context, const RenderArgs & args);
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const;

	private:        
		std::shared_ptr<Charts::ContinuousAxis> axis;
		double value;
        Charts::LineStyle lineStyle;
	};
}

#endif
