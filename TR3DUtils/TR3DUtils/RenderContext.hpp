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

#ifndef TR3DUtils_RenderContext_hpp
#define TR3DUtils_RenderContext_hpp

#include <TR3DUtils/Common.hpp>
#include <TR3DUtils/Disposable.hpp>
#include <TR3DUtils/RenderProgram.hpp>

#include <map>
#include <queue>

namespace TR3DUtils
{
	class RenderBuffer;
	class RenderTexture;
	class RenderVAO;
	class TextRenderer;
	class LineRenderer;
	class PointRenderer;
	class QuadRenderer;
    
	class RenderContext : public Disposable, public std::enable_shared_from_this<RenderContext>
	{
	public:        
		virtual ~RenderContext(void);

		virtual void dispose(void);
        
		void clearTrash(void);
        
        std::shared_ptr<LineRenderer> getLineRenderer(void);
        
        std::shared_ptr<PointRenderer> getPointRenderer(void);
        
        std::shared_ptr<QuadRenderer> getQuadRenderer(void);
        
        std::shared_ptr<TextRenderer> getTextRenderer(void);
        
		std::shared_ptr<RenderBuffer> createBuffer(size_t vertexSize);

		std::shared_ptr<RenderBuffer> createBuffer(size_t vertexSize, size_t vertexCount, const GLfloat * data);

		std::shared_ptr<RenderTexture> createTexture(void);

		std::shared_ptr<RenderVAO> createVAO(const std::vector<std::shared_ptr<const RenderBuffer>> & buffers, GLenum primitiveType);

		std::shared_ptr<RenderProgram> createProgram(const RenderProgramDef & def, const RenderProgram::DefineMap & defineMap);
                
		std::shared_ptr<const RenderProgram> getNamedProgram(const std::string & name, const RenderProgram::DefineMap & defineMap);
        
		static bool registerRenderProgram(const std::string & name, const RenderProgramDef & def);

		static const RenderProgramDef & getRegisteredRenderProgram(const std::string & name);

        static void logFramebufferInfo(void);
        
	private:
        typedef std::pair<std::string, RenderProgram::DefineMap> NamedProgramKey;
        
        std::shared_ptr<LineRenderer> lineRenderer;
        
        std::shared_ptr<PointRenderer> pointRenderer;
        
        std::shared_ptr<QuadRenderer> quadRenderer;
        
        std::shared_ptr<TextRenderer> textRenderer;
        
		std::vector<std::weak_ptr<Disposable>> objects;

		std::map<NamedProgramKey, std::weak_ptr<const RenderProgram>> namedPrograms;

		std::queue<Disposable *> trash;

		std::function<void(Disposable *)> createDisposer(void);
	};
}

#endif
