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

#ifndef Charts_Impl_MarginImpl_hpp
#define Charts_Impl_MarginImpl_hpp

#include <TRCharts/Margin.hpp>

namespace Charts
{
	
	struct Margin : public GeneratedMargin
	{
		Margin(void);

		Margin(double left, double right, double bottom, double top);
        
        static Margin add(const Margin & margin, const Margin & otherMargin);
	};
}

#endif