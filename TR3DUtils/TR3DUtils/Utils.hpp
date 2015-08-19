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

#ifndef TR3DUtils_Utils_hpp
#define TR3DUtils_Utils_hpp

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <tuple>
#include <string>
#include <sstream>

namespace TR3DUtils
{
	namespace Utils
	{
		typedef glm::vec4 Plane;

		template <typename T>
		T roundToPixels(const T & v, glm::float_t scale);

		template <typename T>
		void assertImpl(const T & v, const char * expression, const char * function, const char * file, int line)
		{
			if (!v) {
				std::stringstream strbuf;
				strbuf << "Assertation failed: (" << expression << "), function " << function << ", file " << file << ", line " << line << ".";
				throw std::logic_error(strbuf.str());
			}
		}

		template <typename T>
		T & verifyImpl(T & v, const char * expression, const char * function, const char * file, int line)
		{
			assertImpl(v, expression, function, file, line);
			return v;
		}

		template <typename T>
		const T & verifyImpl(const T & v, const char * expression, const char * function, const char * file, int line)
		{
			assertImpl(v, expression, function, file, line);
			return v;
		}
        
        template <typename T>
        std::string toString(const T & v)
        {
            std::stringstream buf;
            buf << v;
            return buf.str();
        }
        
        inline bool approxEqual(glm::float_t a, glm::float_t b, glm::float_t epsilon)
        {
            return std::fabs(a - b) < epsilon;
        }
        
        inline double approxEqual(double a, double b, double epsilon)
        {
            return std::fabs(a - b) < epsilon;
        }
        
        template <typename T>
        inline bool approxEqual(const T & a, const T & b, const T & epsilon)
        {
            return glm::all(glm::lessThan(glm::abs(a - b), epsilon));
        }

	}

	template<typename T>
	inline T Utils::roundToPixels(const T & v, const glm::float_t scale)
	{
		return (glm::floor(v * scale) / scale); // + T(0.375);
	}
}

#ifndef NDEBUG
#define TR_ASSERT_NOT_REACHED() TR3DUtils::Utils::assertImpl(false, "Expected unreachable", __FUNCTION__, __FILE__, __LINE__)
#define TR_ASSERT(v) TR3DUtils::Utils::assertImpl(v, #v, __FUNCTION__, __FILE__, __LINE__)
#define TR_VERIFY(v) TR3DUtils::Utils::verifyImpl(v, #v, __FUNCTION__, __FILE__, __LINE__)
#else
#define TR_ASSERT_NOT_REACHED()
#define TR_ASSERT(v)
#define TR_VERIFY(v) v
#endif

#endif
