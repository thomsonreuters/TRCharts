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

#ifndef TRCharts_Impl_RenderArgs_hpp
#define TRCharts_Impl_RenderArgs_hpp

#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Margin.hpp>
#include <TR3DUtils/Common.hpp>

namespace Charts
{
	struct RenderArgs
	{
		glm::vec2 screenSize;
        
        glm::vec2 areaStart;
        glm::vec2 areaSize;
        
        glm::dvec2 offset;
        glm::dvec2 scale;
        
        glm::float_t contentScaleFactor;
        
		glm::mat4 projection;

        glm::vec4 clearColor;
        
        // TODO: review inclusion
		Margin margin;
        
        RenderArgs(void)
        :screenSize(), areaStart(), areaSize(), contentScaleFactor(1), projection(), clearColor(), margin()
        {
        }
	};
}

#endif
