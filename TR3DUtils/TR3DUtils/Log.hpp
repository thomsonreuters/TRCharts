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

#ifndef TR3DUtils_Logger_hpp
#define TR3DUtils_Logger_hpp

#include <cstdlib>
#include <cstdarg>

#include <string>

#ifndef __printflike
#define __printflike(x,y)
#endif

namespace TR3DUtils
{
	namespace Log
	{
		enum Level
		{
			LEVEL_TRACE,
			LEVEL_DEBUG,
			LEVEL_INFO,
			LEVEL_WARN,
			LEVEL_ERROR
		};
        
        typedef void (*LogHandler)(Level level, const char * fmt, va_list args);
        
		__printflike(1, 2)void Trace(const char * const fmt, ...);

		__printflike(1, 2)void Debug(const char * const fmt, ...);

		__printflike(1, 2)void Info(const char * const fmt, ...);

		__printflike(1, 2)void Warn(const char * const fmt, ...);

		__printflike(1, 2)void Error(const char * const fmt, ...);

		__printflike(2, 3)void Message(const Level logLevel, const char * const fmt, ...);

		void MessageVA(const Level logLevel, const char * const fmt, va_list args);
        
		void MessagePlatformVA(const Level logLevel, const char * const fmt, va_list args);

		void SetLevel(const Level logLevel);
        
		Level GetLevel(void);
        
        void SetHandler(LogHandler handler);
	}
}

#endif
