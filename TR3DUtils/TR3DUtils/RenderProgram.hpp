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

#ifndef TR3DUtils_RenderProgram_hpp
#define TR3DUtils_RenderProgram_hpp

#include <TR3DUtils/Common.hpp>
#include <TR3DUtils/Disposable.hpp>

#include <string>
#include <map>

namespace TR3DUtils
{
	class RenderProgramDef
	{
	public:
		RenderProgramDef(void);

		RenderProgramDef(const std::string & vertexShaderSource, const std::string & fragmentShaderSource, const std::vector<std::string> & attributeNames, const std::vector<std::string> & uniformNames);

		std::string vertexShaderSource;
		std::string fragmentShaderSource;
		std::vector<std::string> attributeNames;
		std::vector<std::string> uniformNames;
	};

	class RenderProgram : public Disposable
	{
    public:
        typedef std::map<std::string, std::string> DefineMap;

	public:
		RenderProgram(const RenderProgramDef & def, const DefineMap & defineMap);

		RenderProgram(const std::string & vertexShaderSource, const std::string & fragmentShaderSource, const std::vector<std::string> & attributeNames, const std::vector<std::string> & uniformNames);

		virtual ~RenderProgram(void);

		virtual void dispose(void);

        bool isUsable(void) const;
        
		GLuint getUniformLocation(const std::string & name) const;

		void bind(void) const;

		void bindUniform(const std::string & name, const glm::int_t value) const;

		void bindUniform(const std::string & name, const glm::float_t value) const;

		void bindUniform(const std::string & name, const glm::vec2 & value) const;

		void bindUniform(const std::string & name, const glm::vec3 & value) const;

		void bindUniform(const std::string & name, const glm::vec4 & value) const;
        
		void bindUniform(const std::string & name, const glm::mat2 & value) const;
        
		void bindUniform(const std::string & name, const glm::mat3 & value) const;

		void bindUniform(const std::string & name, const glm::mat4 & value) const;

        static std::string applyDefineMap(const std::string & source, const DefineMap & defineMap);
        
	private:
		static GLuint compileShader(GLenum type, const std::string & source);

		static bool linkProgram(GLuint programId);

		static bool validateProgram(GLuint programId);
        
	private:
		GLuint programId;
        
		GLuint vertexShaderId;
        
		GLuint fragmentShaderId;
        
		std::map<std::string, GLuint> uniforms;
	};
}

#endif
