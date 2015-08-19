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

#include <TR3DUtils/PointRenderer.hpp>
#include <TR3DUtils/RenderContext.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/Utils.hpp>

// NOTE: Generally inneficient, only use for drawing single dynamic points

using namespace TR3DUtils;

PointRenderer::PointRenderer(const std::weak_ptr<RenderContext> & context)
:context(context)
{
}

PointRenderer::~PointRenderer(void)
{
}

void PointRenderer::bind(void)
{
    if(!(vao && program)) {
        const std::shared_ptr<RenderContext> context = this->context.lock();
        if(TR_VERIFY(context)) {
            if(!vao) {
                std::vector<glm::float_t> ignoreData;
                ignoreData.push_back(1.f);
                const std::shared_ptr<RenderBuffer> buffer = context->createBuffer(1, ignoreData.size(), &(ignoreData[0]));
                vao = context->createVAO({buffer}, GL_POINTS);
            }
            if(!program) {
                program = context->getNamedProgram("trc3d.pointrenderer", RenderProgram::DefineMap());
            }
        }
    }
    if(program) {
        program->bind();
    }
}

void PointRenderer::bindModelViewProjection(const glm::mat4 & modelViewProjection) const
{
    if(TR_VERIFY(program)) {
        program->bindUniform("modelViewProjection", modelViewProjection);
    }
}

void PointRenderer::bindColor(const glm::vec4 & color) const
{
    if(TR_VERIFY(program)) {
        program->bindUniform("color", color);
    }
}

void PointRenderer::bindSize(glm::float_t size) const
{
    if(TR_VERIFY(program)) {
        program->bindUniform("pointSize", size);
    }
}

void PointRenderer::drawPoint(const glm::vec3 & position) const
{
    if(TR_VERIFY(program && vao)) {
        program->bindUniform("position", position);
        vao->draw();
    }
}

namespace
{
	bool staticInit = [](void) -> bool {
		return TR3DUtils::RenderContext::registerRenderProgram("trc3d.pointrenderer", TR3DUtils::RenderProgramDef(
R"**(
attribute float ignore;

uniform mat4 modelViewProjection;
uniform vec3 position;
uniform float pointSize;

void main()
{
    gl_Position = modelViewProjection * vec4(position, 1.0);
    gl_PointSize = pointSize;
}
)**",
R"**(
uniform lowp vec4 color;

void main()
{
    lowp float weight = step(length(gl_PointCoord - vec2(0.5)), 0.5);
    gl_FragColor = color * weight;
}
)**",
{"ignore"},
{"modelViewProjection", "position", "pointSize", "color"}));
	}();
}
