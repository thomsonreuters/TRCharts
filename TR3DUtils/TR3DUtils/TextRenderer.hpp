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

#ifndef TR3DUtils_TextRenderer_hpp
#define TR3DUtils_TextRenderer_hpp

#include <TR3DUtils/Common.hpp>

#include <string>
#include <map>

namespace TR3DUtils
{
	class RenderContext;
	class TextFactory;
	class RenderTexture;
	class RenderVAO;
	class RenderProgram;

	class TextRenderer
	{
	public:
		TextRenderer(const std::weak_ptr<RenderContext> & context);

		virtual ~TextRenderer(void);

        virtual void clearTrash(void);
        
		virtual std::shared_ptr<RenderTexture> getTextTexture(const std::string & text, const std::string & fontName, size_t fontSize) const;

		virtual void drawText(const glm::mat4 & modelViewProjection, const std::string & text, const std::string & fontName, size_t fontSize, const glm::vec3 & position, glm::float_t rotation, const glm::vec2 & align, const glm::vec4 & color, glm::float_t scale) const;

	private:
        typedef size_t Tick;
		typedef std::tuple<std::string, size_t> FontKey;
		typedef std::tuple<std::string, FontKey> TextureKey;
        typedef std::tuple<std::shared_ptr<RenderTexture>, Tick> TextureRecord;

        Tick currentTick;
        
		mutable std::shared_ptr<RenderVAO> vao;
		mutable std::shared_ptr<const RenderProgram> program;

		mutable std::map<TextureKey, TextureRecord> textures;

		const std::weak_ptr<RenderContext> context;
		const std::shared_ptr<TextFactory> factory;
        
        static const Tick VALIDITY_TICKS;
	};
}

#endif

