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

#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/Log.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/Debug.hpp>

using namespace TR3DUtils;

RenderBuffer::RenderBuffer(const size_t vertexSize)
		: vertexSize(vertexSize), bufferId(0)
{
	glGenBuffers(1, &bufferId);
}

RenderBuffer::RenderBuffer(const size_t vertexSize, const size_t vertexCount, const GLfloat * const data)
		: RenderBuffer(vertexSize)
{
	uploadData(vertexCount, data);
}

RenderBuffer::~RenderBuffer(void)
{
	dispose();
}

void RenderBuffer::dispose(void)
{
	if(bufferId != 0) {
		glDeleteBuffers(1, &bufferId);
		bufferId = 0;
	}
}

bool RenderBuffer::isUsable(void) const
{
    return bufferId != 0;
}

void RenderBuffer::bind(void) const
{
    if(Debug::isGLValidationEnabled()) {
        TR_ASSERT(glIsBuffer(bufferId));
    }
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

size_t RenderBuffer::getVertexSize(void) const
{
	return vertexSize;
}

size_t RenderBuffer::getVertexCount(void) const
{
	return vertexCount;
}

void RenderBuffer::uploadData(const size_t vertexCount, const GLfloat * const data)
{
	this->vertexCount = vertexCount;
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize * sizeof(GLfloat), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
