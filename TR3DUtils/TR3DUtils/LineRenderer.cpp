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

#include <TR3DUtils/LineRenderer.hpp>
#include <TR3DUtils/RenderContext.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/Utils.hpp>

// NOTE: Generally inneficient, only use for drawing single dynamic lines

using namespace TR3DUtils;

LineRenderer::LineRenderer(const std::weak_ptr<RenderContext> & context)
:context(context)
{
}

LineRenderer::~LineRenderer(void)
{
}

void LineRenderer::bind(Mode mode)
{
    if(!(vao && programs[mode])) {
        const std::shared_ptr<RenderContext> context = this->context.lock();
        if(TR_VERIFY(context)) {
            if(!vao) {
                std::vector<glm::float_t> positionData;
                positionData.push_back(0.f);
                positionData.push_back(1.f);
                const std::shared_ptr<RenderBuffer> buffer = context->createBuffer(1, positionData.size(), &(positionData[0]));
                vao = context->createVAO({buffer}, GL_LINES);
            }
            if(!programs[mode]) {
                RenderProgram::DefineMap defineMap;
                switch(mode) {
                    case MODE_SOLID:
                        defineMap["SOLID_LINE"] = "";
                        break;
                    case MODE_DASHED:
                        defineMap["DASHED_LINE"] = "";
                        break;
                    default:
                        throw std::logic_error("Bad line mode");
                }
                programs[mode] = context->getNamedProgram("trc3d.linerenderer", defineMap);
            }
        }
    }
    if(TR_VERIFY(programs[mode])) {
        program = programs[mode];
        program->bind();
    }
}

void LineRenderer::bindModelViewProjection(const glm::mat4 & modelViewProjection) const
{
    if(TR_VERIFY(program)) {
        program->bindUniform("uModelViewProjection", modelViewProjection);
    }
}

void LineRenderer::bindColor(const glm::vec4 & color) const
{
    if(TR_VERIFY(program)) {
        program->bindUniform("uColor", color);
    }
}

void LineRenderer::drawLine(const glm::vec3 & start, const glm::vec3 & finish) const
{
    if(TR_VERIFY(program && vao)) {
        program->bindUniform("uStart", start);
        program->bindUniform("uFinish", finish);
        program->bindUniform("uLength", glm::distance(start, finish));
        vao->draw();
    }
}


namespace
{
	bool staticInit = [](void) -> bool {
		return TR3DUtils::RenderContext::registerRenderProgram("trc3d.linerenderer", TR3DUtils::RenderProgramDef(
R"**(
                                                                                                                 
attribute float aPosition;

uniform mat4 uModelViewProjection;
uniform vec3 uStart;
uniform vec3 uFinish;
                                                                                                                 
#ifndef SOLID_LINE
uniform float uLength;
varying mediump float vLength;
#endif

void main()
{
#ifndef SOLID_LINE
    vLength = aPosition * uLength;
#endif
    gl_Position = uModelViewProjection * vec4(mix(uStart, uFinish, aPosition), 1.0);
}
)**",
R"**(
uniform lowp vec4 uColor;
                                                               
#ifndef SOLID_LINE
varying mediump float vLength;
#endif

void main()
{
    lowp float weight = 1.0;
#ifdef DASHED_LINE
    lowp float pattern = fract(vLength * 0.08);
    weight *= step(0.5, pattern);
#endif
    gl_FragColor = vec4(uColor.xyz, uColor.a * weight);
}
)**",
{"aPosition"},
{"uModelViewProjection", "uStart", "uFinish", "uLength", "uColor"}));
	}();
}
