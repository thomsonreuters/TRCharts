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

#include <TR3DUtils/RenderProgram.hpp>
#include <TR3DUtils/Log.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/Debug.hpp>

#include <glm/gtx/string_cast.hpp>
#include <sstream>

using namespace TR3DUtils;

RenderProgramDef::RenderProgramDef(void)
{
}

RenderProgramDef::RenderProgramDef(const std::string & vertexShaderSource, const std::string & fragmentShaderSource, const std::vector<std::string> & attributeNames, const std::vector<std::string> & uniformNames)
	:vertexShaderSource(vertexShaderSource), fragmentShaderSource(fragmentShaderSource), attributeNames(attributeNames), uniformNames(uniformNames)
{
}

RenderProgram::RenderProgram(const RenderProgramDef & def, const DefineMap & defineMap)
	:RenderProgram(applyDefineMap(def.vertexShaderSource, defineMap), applyDefineMap(def.fragmentShaderSource, defineMap), def.attributeNames, def.uniformNames)
{
}

RenderProgram::RenderProgram(const std::string & vertexShaderSource, const std::string & fragmentShaderSource, const std::vector<std::string> & attributeNames, const std::vector<std::string> & uniformNames)
{
	programId = glCreateProgram();

	vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	size_t i = 0;
	for (const std::string & attributeName : attributeNames) {
		glBindAttribLocation(programId, GLuint(i), attributeName.c_str());
		Log::Trace("Bound attribute \"%s\" at #%d", attributeName.c_str(), (int) i);
		++i;
	}

	linkProgram(programId);

	//validateProgram(programId);

	for (const std::string & name : uniformNames) {
		const GLint location = glGetUniformLocation(programId, name.c_str());
		Log::Trace("Got uniform \"%s\" at #%i", name.c_str(), location);
		uniforms[name] = location;
	}
}

RenderProgram::~RenderProgram(void)
{
	dispose();
}

void RenderProgram::dispose(void)
{
	if(programId != 0) {
		glDeleteProgram(programId);
		programId = 0;
	}
	if(vertexShaderId != 0) {
		glDeleteShader(vertexShaderId);
		fragmentShaderId = 0;
	}
	if(fragmentShaderId != 0) {
		glDeleteShader(fragmentShaderId);
		fragmentShaderId = 0;
	}
}

bool RenderProgram::isUsable(void) const
{
    return programId != 0;
}

GLuint RenderProgram::getUniformLocation(const std::string & name) const
{
	const std::map<std::string, GLuint>::const_iterator iter = uniforms.find(name);
	if (iter != uniforms.end()) {
		return iter->second;
	} else {
		return -1;
	}
}

void RenderProgram::bind(void) const
{
    if(TR_VERIFY(programId)) {
        if(Debug::isGLValidationEnabled()) {
            TR_ASSERT(glIsProgram(programId));
        }
        glUseProgram(programId);
    }
}

void RenderProgram::bindUniform(const std::string & name, const glm::int_t value) const
{
	glUniform1i(getUniformLocation(name), value);
}

void RenderProgram::bindUniform(const std::string & name, const glm::float_t value) const
{
	glUniform1f(getUniformLocation(name), value);
}

void RenderProgram::bindUniform(const std::string & name, const glm::vec2 & value) const
{
	glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void RenderProgram::bindUniform(const std::string & name, const glm::vec3 & value) const
{
	glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void RenderProgram::bindUniform(const std::string & name, const glm::vec4 & value) const
{
	glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void RenderProgram::bindUniform(const std::string & name, const glm::mat2 & value) const
{
	glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void RenderProgram::bindUniform(const std::string & name, const glm::mat3 & value) const
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void RenderProgram::bindUniform(const std::string & name, const glm::mat4 & value) const
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

std::string RenderProgram::applyDefineMap(const std::string & source, const DefineMap & defineMap)
{
    std::stringstream result;
    for(const auto & pair : defineMap) {
        result << "#define " << pair.first << " " << pair.second << "\n";
    }
    result << source;
    return result.str();
}

GLuint RenderProgram::compileShader(const GLenum type, const std::string & source)
{
	const GLuint shader = glCreateShader(type);
	const char * sourceCstr = source.c_str();
	glShaderSource(shader, 1, &sourceCstr, NULL);
	glCompileShader(shader);

#if 1
	GLint logLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		GLchar * log = new GLchar[logLength];
        glGetShaderInfoLog(shader, logLength, &logLength, log);
        Log::Error("Shader compile log:\n%s", log);
        delete[] log;
	}
#endif

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == 0) {
		Log::Error("Failed to compile shader");
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

bool RenderProgram::linkProgram(const GLuint programId)
{
	glLinkProgram(programId);

	GLint status;
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	if (status == 0) {
		Log::Error("Failed to link program\n");
		GLint logLength;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0) {
            GLchar * log = new GLchar[logLength];
			glGetProgramInfoLog(programId, logLength, &logLength, log);
			Log::Error("Program link log:\n%s\n", log);
            delete[] log;
		}
		return false;
	}
	return true;
}

bool RenderProgram::validateProgram(const GLuint programId)
{
	glValidateProgram(programId);

	GLint logLength;
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
        GLchar * log = new GLchar[logLength];
		glGetProgramInfoLog(programId, logLength, &logLength, log);
		Log::Info("Program validate log:\n%s", log);
        delete[] log;
	}

	GLint status;
	glGetProgramiv(programId, GL_VALIDATE_STATUS, &status);
	if (status == 0) {
		return false;
	}
	return true;
}
