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

#ifndef TRCharts_Impl_LabelImpl_hpp
#define TRCharts_Impl_LabelImpl_hpp

#include <TRCharts/Label.hpp>
#include <TRCharts/Drawable.hpp>
#include <TRCharts/Color.hpp>
#include <TRCharts/Font.hpp>
#include <TRCharts/Margin.hpp>
#include <TRCharts/Size.hpp>
#include <TRCharts/Impl/DrawableImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class Label : public GeneratedLabel
	{
	public:
		Label(void);

		virtual ~Label(void);

		virtual const std::string & getText(void) const;

		virtual void setText(const std::string & value);

		virtual const Charts::Color & getColor(void) const;

		virtual void setColor(const Charts::Color & value);

		virtual const Charts::Font & getFont(void) const;

		virtual void setFont(const Charts::Font & value);

		virtual const Charts::Margin & getMargin(void) const;

		virtual void setMargin(const Charts::Margin & value);

		virtual const Charts::Size & getSize(void) const;

		virtual void setSize(const Charts::Size & value);
        
        virtual double getFullHeight(void) const;
        
        virtual double getFullWidth(void) const;

	private:
		std::string text;
		Charts::Color color;
		Charts::Font font;
		Charts::Margin margin;
		Charts::Size size;
	};
}

#endif