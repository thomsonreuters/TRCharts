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

#ifndef TR3DUtils_QuadRenderer_hpp
#define TR3DUtils_QuadRenderer_hpp

#include <TR3DUtils/Common.hpp>

#include <memory>
#include <string>

namespace TR3DUtils
{
    class RenderContext;
    class RenderVAO;
    class RenderProgram;
    
    class QuadRenderer
    {
    public:
        QuadRenderer(const std::weak_ptr<RenderContext> & context);
        
        virtual ~QuadRenderer(void);
        
        void bind(void);
        
        void bindModelViewProjection(const glm::mat4 & modelViewProjection) const;
        
        void bindColor(const glm::vec4 & color) const;
        
        void drawQuad(const glm::vec3 & start, const glm::vec2 & size) const;
        
    private:
        const std::weak_ptr<RenderContext> context;
        
        std::shared_ptr<RenderVAO> vao;
        std::shared_ptr<const RenderProgram> program;
    };
}

#endif

