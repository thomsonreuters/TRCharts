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

#include <TR3DUtils/RenderTexture.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/Debug.hpp>

using namespace TR3DUtils;

RenderTexture::RenderTexture(void)
	:textureId(0)
{
	glGenTextures(1, &textureId);
    TR_ASSERT(textureId > 0);
}

RenderTexture::~RenderTexture(void)
{
	dispose();
}

void RenderTexture::dispose(void)
{
	if(textureId != 0) {
		glDeleteTextures(1, &textureId);
		textureId = 0;
	}
}

bool RenderTexture::isUsable(void) const
{
    return textureId != 0;
}

void RenderTexture::setWrapping(const GLenum wrapS, const GLenum wrapT)
{
	if(TR_VERIFY(textureId != 0)) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void RenderTexture::setFiltering(const GLenum minFilter, const GLenum magFilter)
{
	if(TR_VERIFY(textureId != 0)) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void RenderTexture::uploadData(const GLenum format, const GLenum type, const GLsizei width, GLsizei height, const void * const data)
{
	if(TR_VERIFY(textureId != 0)) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);
        glBindTexture(GL_TEXTURE_2D, 0);
        size = glm::vec2 { width, height };
    }
}

const glm::vec2 & RenderTexture::getSize(void) const
{
	return size;
}

void RenderTexture::bind(const GLuint at) const
{
	if(TR_VERIFY(textureId != 0)) {
        if(Debug::isGLValidationEnabled()) {
            TR_ASSERT(glIsTexture(textureId));
        }
        glActiveTexture(GL_TEXTURE0 + at);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
}

GLuint RenderTexture::getTextureId(void) const
{
	return textureId;
}

void RenderTexture::setSize(const glm::vec2 & size)
{
	this->size = size;
}
