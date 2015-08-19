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

#ifndef TRCharts_Impl_PointDecorationImpl_hpp
#define TRCharts_Impl_PointDecorationImpl_hpp

#include <TRCharts/PointDecoration.hpp>
#include <TRCharts/Decoration.hpp>
#include <TRCharts/Point.hpp>
#include <TRCharts/Impl/DecorationImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class ContinuousAxis;

	
	class PointDecoration : public GeneratedPointDecoration
	{
	public:
		PointDecoration(void);

		virtual ~PointDecoration(void);

		virtual const std::shared_ptr<Charts::ContinuousAxis> & getAbscissaAxis(void) const;

		virtual void setAbscissaAxis(const std::shared_ptr<Charts::ContinuousAxis> & value);

		virtual const std::shared_ptr<Charts::ContinuousAxis> & getOrdinateAxis(void) const;

		virtual void setOrdinateAxis(const std::shared_ptr<Charts::ContinuousAxis> & value);
        
		virtual const Coordinates & getValue(void) const;
        
		virtual void setValue(const Coordinates & value);

		virtual const Charts::PointStyle & getPointStyle(void) const;

		virtual void setPointStyle(const Charts::PointStyle & value);

		virtual void preRender(TR3DUtils::RenderContext & context, const RenderArgs & args);
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const;
        
	private:        
		std::shared_ptr<Charts::ContinuousAxis> abscissaAxis;
		std::shared_ptr<Charts::ContinuousAxis> ordinateAxis;
		Coordinates value;
        Charts::PointStyle pointStyle;

	};
}

#endif
