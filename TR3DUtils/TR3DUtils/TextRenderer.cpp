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

#include <TR3DUtils/TextRenderer.hpp>
#include <TR3DUtils/TextFactory.hpp>
#include <TR3DUtils/RenderContext.hpp>
#include <TR3DUtils/Log.hpp>
#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/RenderTexture.hpp>
#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/Utils.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace TR3DUtils;

const TextRenderer::Tick TextRenderer::VALIDITY_TICKS = 10;

namespace
{
	const glm::vec2 vertexPositions[6] = { glm::vec2 { 0.0f, 0.0f }, glm::vec2 { 1.0f, 0.0f }, glm::vec2 { 0.0f, 1.0f }, glm::vec2 { 0.0f, 1.0f }, glm::vec2 { 1.0f, 0.0f }, glm::vec2 { 1.0f, 1.0f } };
}

TextRenderer::TextRenderer(const std::weak_ptr<RenderContext> & context)
		: context(context), factory(std::make_shared < TextFactory > (context)), currentTick(0)
{
}

TextRenderer::~TextRenderer(void)
{
}

void TextRenderer::clearTrash(void)
{
	++currentTick;
	for (auto iter = textures.begin(); iter != textures.end();) {
		const TextureRecord & record = iter->second;
		if ((std::get < 1 > (record) + VALIDITY_TICKS) < currentTick) {
			iter = textures.erase(iter);
		} else {
			++iter;
		}
	}
}

void TextRenderer::drawText(const glm::mat4 & modelViewProjection, const std::string & text, const std::string & fontName, size_t fontSize, const glm::vec3 & position, glm::float_t rotation, const glm::vec2 & align, const glm::vec4 & color, const glm::float_t scale) const
{
	if (!(vao && program)) {
		const std::shared_ptr<RenderContext> context = this->context.lock();
		if(TR_VERIFY(context)) {
            if (!vao) {
                const std::shared_ptr<RenderBuffer> positionBuffer = context->createBuffer(2, 6, glm::value_ptr(vertexPositions[0]));
                const std::shared_ptr<RenderBuffer> texCoordBuffer = context->createBuffer(2, 6, glm::value_ptr(vertexPositions[0]));
                vao = context->createVAO( { positionBuffer, texCoordBuffer }, GL_TRIANGLES);
            }
            if (!program) {
                program = context->getNamedProgram("trc3d.textrenderer.precomputed", RenderProgram::DefineMap());
            }
        }
	}
	const std::shared_ptr<RenderTexture> texture = getTextTexture(text, fontName, fontSize * scale);
	if (texture) {
		const glm::mat2 alignRotation = glm::mat2(glm::rotate(glm::mat4(), rotation, glm::vec3(0.f, 0.f, 1.f)));
		const glm::mat2 positionRotation = glm::mat2(glm::translate(glm::rotate(glm::translate(glm::mat4(), glm::vec3(0.5f)), rotation, glm::vec3(0.f, 0.f, 1.f)), glm::vec3(-0.5f)));
		const std::shared_ptr<RenderTexture> texture = getTextTexture(text, fontName, fontSize * scale);
		if (TR_VERIFY(vao && program)) {
			const glm::vec2 textureSize = texture->getSize() / scale;
			texture->bind(0);
			program->bind();
			program->bindUniform("modelViewProjection", modelViewProjection);
			program->bindUniform("offset", glm::vec3(Utils::roundToPixels(glm::vec2(position) - (alignRotation * (align * textureSize)), scale), position.z));
			program->bindUniform("size", textureSize);
			program->bindUniform("texture", 0);
			program->bindUniform("color", color);
			program->bindUniform("rotation", positionRotation);
			vao->draw();
		}
	}
}

std::shared_ptr<RenderTexture> TextRenderer::getTextTexture(const std::string & text, const std::string & fontName, size_t fontSize) const
{
	const TextureKey textureKey = TextureKey(text, FontKey(fontName, fontSize));
	const auto iter = textures.find(textureKey);
	std::shared_ptr<RenderTexture> texture;
	if (iter != textures.end()) {
		TextureRecord & record = iter->second;
		texture = std::get < 0 > (record);
        if(texture->isUsable()) {
            ++std::get < 1 > (record);
        } else {
            Log::Error("Got an unusable text texture, regenerating");
            texture = nullptr;
        }
	}
	if (!texture) {
		texture = factory->createTextTexture(text, fontName, fontSize);
		textures[textureKey] = TextureRecord(texture, currentTick);
	}
	return texture;
}

namespace
{
	bool staticInit = [](void) -> bool {
		return TR3DUtils::RenderContext::registerRenderProgram("trc3d.textrenderer.precomputed", TR3DUtils::RenderProgramDef(
						R"**(
attribute vec2 position;
attribute vec2 texCoord;

uniform mat2 rotation;
uniform mat4 modelViewProjection;

uniform vec3 offset;
uniform vec2 size;

varying mediump vec2 fragmentTexCoord;

void main()
{
	gl_Position = modelViewProjection * vec4(vec3(rotation * (position * size), 0) + offset, 1);
	fragmentTexCoord = texCoord;
}
)**",
						R"**(
varying mediump vec2 fragmentTexCoord;

uniform sampler2D texture;

uniform lowp vec4 color;

void main()
{
	gl_FragColor = texture2D(texture, fragmentTexCoord).a * color;
}
)**",
						{	"position", "texCoord"},
						{	"modelViewProjection", "offset", "size", "texture", "color", "rotation"}));
	}();
}
