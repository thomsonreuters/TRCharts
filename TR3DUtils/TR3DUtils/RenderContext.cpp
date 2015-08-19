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

#include <TR3DUtils/RenderContext.hpp>
#include <TR3DUtils/Log.hpp>

#include <TR3DUtils/RenderVAO.hpp>
#include <TR3DUtils/RenderBuffer.hpp>
#include <TR3DUtils/RenderTexture.hpp>
#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/TextRenderer.hpp>
#include <TR3DUtils/LineRenderer.hpp>
#include <TR3DUtils/PointRenderer.hpp>
#include <TR3DUtils/QuadRenderer.hpp>

#include <map>

using namespace TR3DUtils;

namespace
{
	std::map<std::string, RenderProgramDef> & getRenderProgramRegistry(void)
	{
		static std::map<std::string, RenderProgramDef> registry;
		return registry;
	}
}

RenderContext::~RenderContext(void)
{
	dispose();
}

void RenderContext::dispose(void)
{
    TR3DUtils::Log::Warn("Disposing render context");
	clearTrash();
	for(auto tmp : objects) {
		if(auto ptr = tmp.lock()) {
			ptr->dispose();
		}
	}
	objects.clear();
    lineRenderer.reset();
    pointRenderer.reset();
    quadRenderer.reset();
    textRenderer.reset();
}

void RenderContext::clearTrash(void)
{
    // do not call getTextRenderer, because if the text renderer is not yet initialized
    // it shouldn't be (especially when this method is called because the render context
    // shared_ptr was just invalidated.)
    if(textRenderer) {
        textRenderer->clearTrash();
    }
    // must iterate like this, because deleting trash items may cause dependencies to be trashed.
	while(!trash.empty()) {
        auto ptr = trash.front();
        trash.pop();
		delete ptr;
	}
}

std::shared_ptr<LineRenderer> RenderContext::getLineRenderer(void)
{
    if(!lineRenderer) {
        lineRenderer.reset(new LineRenderer(shared_from_this()));
    }
	return lineRenderer;
}

std::shared_ptr<PointRenderer> RenderContext::getPointRenderer(void)
{
    if(!pointRenderer) {
        pointRenderer.reset(new PointRenderer(shared_from_this()));
    }
	return pointRenderer;
}

std::shared_ptr<QuadRenderer> RenderContext::getQuadRenderer(void)
{
    if(!quadRenderer) {
        quadRenderer.reset(new QuadRenderer(shared_from_this()));
    }
	return quadRenderer;
}

std::shared_ptr<TextRenderer> RenderContext::getTextRenderer(void)
{
    if(!textRenderer) {
        textRenderer.reset(new TextRenderer(shared_from_this()));
    }
	return textRenderer;
}

std::shared_ptr<RenderBuffer> RenderContext::createBuffer(const size_t vertexSize)
{
	const auto buffer = std::shared_ptr<RenderBuffer>(new RenderBuffer(vertexSize), createDisposer());
	objects.push_back(buffer);
	return buffer;
}

std::shared_ptr<RenderBuffer> RenderContext::createBuffer(const size_t vertexSize, const size_t vertexCount, const GLfloat * const data)
{
	const auto buffer = std::shared_ptr<RenderBuffer>(new RenderBuffer(vertexSize, vertexCount, data), createDisposer());
	objects.push_back(buffer);
	return buffer;
}

std::shared_ptr<RenderTexture> RenderContext::createTexture(void)
{
	const auto texture = std::shared_ptr<RenderTexture>(new RenderTexture(), createDisposer());
	objects.push_back(texture);
	return texture;
}

std::shared_ptr<RenderVAO> RenderContext::createVAO(const std::vector<std::shared_ptr<const RenderBuffer>> & buffers, const GLenum primitiveType)
{
	const auto vao = std::shared_ptr<RenderVAO>(new RenderVAO(buffers, primitiveType), createDisposer());
	objects.push_back(vao);
	return vao;
}

std::shared_ptr<RenderProgram> RenderContext::createProgram(const RenderProgramDef & def, const RenderProgram::DefineMap & defineMap)
{
	const auto program = std::shared_ptr<RenderProgram>(new RenderProgram(def, defineMap), createDisposer());
	objects.push_back(program);
	return program;
}

std::shared_ptr<const RenderProgram> RenderContext::getNamedProgram(const std::string & name, const RenderProgram::DefineMap & defineMap)
{
    const NamedProgramKey key = std::make_pair(name, defineMap);
	const auto iter = namedPrograms.find(key);
	if(iter != namedPrograms.end()) {
		if(const std::shared_ptr<const RenderProgram> renderProgram = iter->second.lock()) {
			return renderProgram;
		}
	}
    Log::Debug("Creating named program (name: %s)", name.c_str());
	const std::shared_ptr<const RenderProgram> newProgram = createProgram(getRegisteredRenderProgram(name), defineMap);
	namedPrograms[key] = newProgram;
	return newProgram;
}

bool RenderContext::registerRenderProgram(const std::string & name, const RenderProgramDef & def)
{
	getRenderProgramRegistry()[name] = def;
	return true;
}

const RenderProgramDef & RenderContext::getRegisteredRenderProgram(const std::string & name)
{
	const std::map<std::string, RenderProgramDef> & registry = getRenderProgramRegistry();
	const auto iter = registry.find(name);
	if(iter != registry.end()) {
		return iter->second;
	} else {
		throw std::logic_error("Registered program " + name + " not found");
	}
}

std::function<void(Disposable *)> RenderContext::createDisposer(void)
{
	const std::weak_ptr<RenderContext> self = shared_from_this();
	return [self](Disposable * const o) -> void {
		if(const std::shared_ptr<RenderContext> context = self.lock()) {
			context->trash.push(o);
		} else {
			Log::Warn("Dependent disposable destroyed after render context destroyed");
			delete o;
		}
	};
}

void RenderContext::logFramebufferInfo(void)
{
    enum {
        BUFFER_COLOR,
        BUFFER_DEPTH,
        BUFFER_STENCIL,
        NUM_BUFFERS
    };
    GLint oldRenderBuffer;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
    GLint names[NUM_BUFFERS] = {};
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, names + BUFFER_COLOR);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, names + BUFFER_DEPTH);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, names + BUFFER_STENCIL);
    if(names[BUFFER_COLOR] > 0) {
        enum {
            SIZE_RED,
            SIZE_GREEN,
            SIZE_BLUE,
            SIZE_ALPHA,
            NUM_SIZES
        };
        GLint sizes[NUM_SIZES] = {};
        glBindRenderbuffer(GL_RENDERBUFFER, names[BUFFER_COLOR]);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_RED_SIZE, sizes + SIZE_RED);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_GREEN_SIZE, sizes + SIZE_GREEN);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_BLUE_SIZE, sizes + SIZE_BLUE);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_ALPHA_SIZE, sizes + SIZE_ALPHA);
        Log::Info("Color buffer bits: %d, %d, %d, %d", sizes[SIZE_RED], sizes[SIZE_GREEN], sizes[SIZE_BLUE], sizes[SIZE_ALPHA]);
    } else {
        Log::Info("No color buffer!");
    }
    if(names[BUFFER_DEPTH] > 0) {
        enum {
            SIZE_DEPTH,
            NUM_SIZES
        };
        GLint sizes[NUM_SIZES] = {};
        glBindRenderbuffer(GL_RENDERBUFFER, names[BUFFER_DEPTH]);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_DEPTH_SIZE, sizes + SIZE_DEPTH);
        Log::Info("Depth buffer bits: %d", sizes[SIZE_DEPTH]);
    } else {
        Log::Info("No depth buffer!");
    }
    if(names[BUFFER_STENCIL] > 0) {
        enum {
            SIZE_STENCIL,
            NUM_SIZES
        };
        GLint sizes[NUM_SIZES] = {};
        glBindRenderbuffer(GL_RENDERBUFFER, names[BUFFER_STENCIL]);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_STENCIL_SIZE, sizes + SIZE_STENCIL);
        Log::Info("Stencil buffer bits: %d", sizes[SIZE_STENCIL]);
    } else {
        Log::Info("No stencil buffer!");
    }
    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
}
