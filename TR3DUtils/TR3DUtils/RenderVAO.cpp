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

#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/Log.hpp>

#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/Debug.hpp>

using namespace TR3DUtils;

RenderVAO::RenderVAO(const std::vector<std::shared_ptr<const RenderBuffer>> & buffers, const GLenum primitiveType)
		: buffers(buffers), primitiveType(primitiveType), vaoId(0)
{
    initExtensions();
	if (hasGLVertexArray()) {
		glGenVertexArraysOES(1, &vaoId);
        if(TR_VERIFY(vaoId)) {
            glBindVertexArrayOES(vaoId);
            bindBuffers();
            glBindVertexArrayOES(0);
        }
	}
}

RenderVAO::~RenderVAO(void)
{
	dispose();
}

void RenderVAO::dispose(void)
{
	if(vaoId != 0) {
		if (hasGLVertexArray()) {
			glDeleteVertexArraysOES(1, &vaoId);
		}
		vaoId = 0;
	}
}

bool RenderVAO::isUsable(void) const
{
    bool ok = true;
    if(hasGLVertexArray()) {
        ok = ok && (vaoId != 0);
    }
    for(const auto & buffer : buffers) {
        ok = ok && buffer->isUsable();
    }
    return ok;
}

void RenderVAO::draw(void) const
{
	draw(0, GLsizei(getVertexCount()));
}

void RenderVAO::draw(const GLint vertexStart, const GLsizei vertexCount) const
{
	if (vertexCount > 0 && TR_VERIFY(size_t(vertexStart + vertexCount) <= getVertexCount())) {
		if (hasGLVertexArray()) {
            if(TR_VERIFY(vaoId)) {
                if(Debug::isGLValidationEnabled()) {
                    TR_ASSERT(glIsVertexArrayOES(vaoId));
                }
                glBindVertexArrayOES(vaoId);
            }
		} else {
			bindBuffers();
		}
		glDrawArrays(primitiveType, vertexStart, vertexCount);
	}
}

size_t RenderVAO::getVertexCount() const
{
	size_t vertexCount = 0;
	for (auto buffer : buffers) {
        if(buffer) {
            vertexCount = std::max(vertexCount, buffer->getVertexCount());
        }
	}
	return vertexCount;
}

void RenderVAO::bindBuffers(void) const
{
	for (size_t i = 0; i != this->buffers.size(); ++i) {
		auto buffer = this->buffers[i];
        if(buffer) {
            buffer->bind();
            glEnableVertexAttribArray(GLuint(i));
            glVertexAttribPointer(GLuint(i), GLint(buffer->getVertexSize()), GL_FLOAT, GL_FALSE, 0, NULL);
        }
	}
}
