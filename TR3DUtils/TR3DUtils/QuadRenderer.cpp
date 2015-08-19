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

#include <TR3DUtils/QuadRenderer.hpp>
#include <TR3DUtils/RenderContext.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/Utils.hpp>

// NOTE: Generally inneficient, only use for drawing single dynamic quads

using namespace TR3DUtils;

QuadRenderer::QuadRenderer(const std::weak_ptr<RenderContext> & context)
:context(context)
{
}

QuadRenderer::~QuadRenderer(void)
{
}

void QuadRenderer::bind(void)
{
    if(!(vao && program)) {
        const std::shared_ptr<RenderContext> context = this->context.lock();
        if(TR_VERIFY(context)) {
            if(!vao) {
                std::vector<glm::vec2> positionData;
                positionData.push_back(glm::vec2(0.f, 0.f));
                positionData.push_back(glm::vec2(0.f, 1.f));
                positionData.push_back(glm::vec2(1.f, 0.f));
                positionData.push_back(glm::vec2(1.f, 1.f));
                const std::shared_ptr<RenderBuffer> buffer = context->createBuffer(2, positionData.size(), glm::value_ptr(positionData[0]));
                vao = context->createVAO({buffer}, GL_TRIANGLE_STRIP);
            }
            if(!program) {
                program = context->getNamedProgram("trc3d.quadrenderer", RenderProgram::DefineMap());
            }
        }
    }
    if(program) {
        program->bind();
    }
}

void QuadRenderer::bindModelViewProjection(const glm::mat4 & modelViewProjection) const
{
    if(TR_VERIFY(program)) {
        program->bindUniform("modelViewProjection", modelViewProjection);
    }
}

void QuadRenderer::bindColor(const glm::vec4 & color) const
{
    if(TR_VERIFY(program)) {
        program->bindUniform("color", color);
    }
}

void QuadRenderer::drawQuad(const glm::vec3 & start, const glm::vec2 & size) const
{
    if(TR_VERIFY(program && vao)) {
        program->bindUniform("start", start);
        program->bindUniform("size", size);
        vao->draw();
    }
}


namespace
{
	bool staticInit = [](void) -> bool {
		return TR3DUtils::RenderContext::registerRenderProgram("trc3d.quadrenderer", TR3DUtils::RenderProgramDef(
R"**(
attribute vec2 position;

uniform mat4 modelViewProjection;
uniform vec3 start;
uniform vec2 size;

void main()
{
    gl_Position = modelViewProjection * vec4(vec3(position * size, 0.0) + start, 1.0);
}
)**",
R"**(
uniform lowp vec4 color;

void main()
{
    gl_FragColor = color;
}
)**",
{"position"},
{"modelViewProjection", "start", "size", "color"}));
	}();
}
