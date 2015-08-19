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

#ifndef TRCharts_Impl_DrawableImpl_hpp
#define TRCharts_Impl_DrawableImpl_hpp

#include <TRCharts/Drawable.hpp>
#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Impl/AttachableImpl.hpp>

namespace Charts
{

	
	class Drawable : public GeneratedDrawable
	{
	public:
		Drawable(void);

		virtual ~Drawable(void);
        
		virtual bool isVisible(void) const;

		virtual void setVisible(bool value);
        
		virtual double getOpacity(void) const;
        
		virtual void setOpacity(double value);
        
	private:
		bool visible;
        double opacity;
	};
}

#endif