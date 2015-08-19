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

#include <TR3DUtils/GLExtensions.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/Log.hpp>

#include <sstream>
#include <set>

#ifndef __APPLE__
#ifndef GL_GLEXT_PROTOTYPES
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES = nullptr;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES = nullptr;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES = nullptr;
PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES = nullptr;
#endif
#endif


namespace
{
    bool inited = false;
    std::set<std::string> extensions;
}

void TR3DUtils::initExtensions(void)
{
    if(!inited) {
        if(const GLubyte * tmp = TR_VERIFY(glGetString(GL_EXTENSIONS))) {
            std::istringstream iss(std::string((const char *)tmp));
            do {
                std::string ext;
                iss >> ext;
                extensions.insert(ext);
                Log::Trace("Got extension: %s", ext.c_str());
            } while(iss);
        }
#ifndef __APPLE__
#ifndef GL_GLEXT_PROTOTYPES
        if(extensions.find("GL_OES_vertex_array_object") != extensions.end()) {
            glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC) eglGetProcAddress("glGenVertexArraysOES");
            glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC) eglGetProcAddress("glBindVertexArrayOES");
            glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC) eglGetProcAddress("glDeleteVertexArraysOES");
            glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC) eglGetProcAddress("glIsVertexArrayOES");
        } else {
            Log::Warn("Vertex array objects are not supported");
        }
#endif
#endif
    }
    inited = true;
}

bool TR3DUtils::hasGLVertexArray(void)
{
#ifndef __APPLE__
    return glGenVertexArraysOES && glBindVertexArrayOES && glDeleteVertexArraysOES && glIsVertexArrayOES;
#else
    return true;
#endif
}

bool TR3DUtils::hasExtension(const char * extension)
{
    return extensions.find(extension) != extensions.end();
}