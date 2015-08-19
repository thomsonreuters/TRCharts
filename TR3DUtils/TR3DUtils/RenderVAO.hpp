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

#ifndef TR3DUtils_RenderVAO_hpp
#define TR3DUtils_RenderVAO_hpp

#include <TR3DUtils/Common.hpp>
#include <TR3DUtils/Disposable.hpp>

namespace TR3DUtils
{
	class RenderBuffer;

	class RenderVAO : public Disposable
	{
	public:
		RenderVAO(const std::vector<std::shared_ptr<const RenderBuffer>> & buffers, GLenum primitiveType);

		virtual ~RenderVAO(void);

		virtual void dispose(void);

        bool isUsable(void) const;
        
		size_t getVertexCount(void) const;

		void draw(void) const;

		void draw(GLint vertexStart, GLsizei vertexCount) const;

	private:
		void bindBuffers(void) const;

	private:
		const std::vector<std::shared_ptr<const RenderBuffer>> buffers;

		const GLenum primitiveType;

		GLuint vaoId;
	};
}

#endif
