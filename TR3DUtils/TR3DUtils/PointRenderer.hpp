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

#ifndef TR3DUtils_PointRenderer_hpp
#define TR3DUtils_PointRenderer_hpp

#include <TR3DUtils/Common.hpp>

#include <memory>
#include <string>

namespace TR3DUtils
{
    class RenderContext;
    class RenderVAO;
    class RenderProgram;
    
    class PointRenderer
    {
    public:
        PointRenderer(const std::weak_ptr<RenderContext> & context);
        
        virtual ~PointRenderer(void);
        
        void bind(void);
        
        void bindModelViewProjection(const glm::mat4 & modelViewProjection) const;
        
        void bindColor(const glm::vec4 & color) const;
        
        void bindSize(glm::float_t size) const;
        
        void drawPoint(const glm::vec3 & position) const;
        
    private:
        const std::weak_ptr<RenderContext> context;
        
        std::shared_ptr<RenderVAO> vao;
        std::shared_ptr<const RenderProgram> program;
    };
}

#endif

