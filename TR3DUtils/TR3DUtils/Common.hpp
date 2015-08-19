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

#ifndef TR3DUtils_Common_hpp
#define TR3DUtils_Common_hpp

#ifdef __APPLE__
#include <OpenGLES/ES2/glext.h>
#include <TR3DUtils/GLExtensions.hpp>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <TR3DUtils/GLExtensions.hpp>
#endif

#include <vector>
#include <memory>
#include <cstddef>
#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#endif
