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

#ifndef TR3DUtils_RenderTexture_hpp
#define TR3DUtils_RenderTexture_hpp

#include <TR3DUtils/Common.hpp>
#include <TR3DUtils/Disposable.hpp>

namespace TR3DUtils
{
	class RenderTexture : public Disposable
	{
	private:
		GLuint textureId;

		glm::vec2 size;

	public:
		RenderTexture(void);

		virtual ~RenderTexture(void);

		virtual void dispose(void);
        
        bool isUsable(void) const;

		void setWrapping(GLenum wrapS, GLenum wrapT);

		void setFiltering(GLenum minFilter, GLenum magFilter);

		void uploadData(GLenum format, GLenum type, GLsizei width, GLsizei height, const void * data);

		const glm::vec2 & getSize(void) const;

		void bind(GLuint at) const;

		GLuint getTextureId(void) const;

		void setSize(const glm::vec2 & size);

		typedef std::shared_ptr<RenderTexture> Ptr;

		typedef std::shared_ptr<const RenderTexture> ConstPtr;
	};
}

#endif
