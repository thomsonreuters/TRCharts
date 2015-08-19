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

#include <TR3DUtils/Log.hpp>

#include <cstdio>

using namespace TR3DUtils;

namespace
{
    Log::Level globalLogLevel = Log::LEVEL_TRACE;
    Log::LogHandler globalLogHandler = nullptr;
}

void Log::SetLevel(const Log::Level logLevel)
{
	globalLogLevel = logLevel;
}

Log::Level Log::GetLevel(void)
{
    return globalLogLevel;
}

void Log::Trace(const char * const fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Log::MessageVA(Log::LEVEL_TRACE, fmt, args);
	va_end(args);
}

void Log::Debug(const char * const fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Log::MessageVA(Log::LEVEL_DEBUG, fmt, args);
	va_end(args);
}

void Log::Info(const char * const fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Log::MessageVA(Log::LEVEL_INFO, fmt, args);
	va_end(args);
}

void Log::Warn(const char * const fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Log::MessageVA(Log::LEVEL_WARN, fmt, args);
	va_end(args);
}

void Log::Error(const char * const fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Log::MessageVA(Log::LEVEL_ERROR, fmt, args);
	va_end(args);
}

void Log::Message(const Level logLevel, const char * const fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Log::MessageVA(logLevel, fmt, args);
	va_end(args);
}


void Log::MessageVA(const Log::Level logLevel, const char * const fmt, va_list args)
{
    if(globalLogHandler) {
        globalLogHandler(logLevel, fmt, args);
    } else {
        MessagePlatformVA(logLevel, fmt, args);
    }
}

#ifdef __ANDROID__
#include <android/log.h>

namespace
{
	int getAndroidLogLevelPriority(const Log::Level logLevel)
	{
		switch (logLevel) {
			case Log::LEVEL_TRACE:
			return ANDROID_LOG_VERBOSE;
			case Log::LEVEL_DEBUG:
			return ANDROID_LOG_DEBUG;
			case Log::LEVEL_INFO:
			return ANDROID_LOG_INFO;
			case Log::LEVEL_WARN:
			return ANDROID_LOG_WARN;
			case Log::LEVEL_ERROR:
			return ANDROID_LOG_ERROR;
			default:
			return ANDROID_LOG_DEFAULT;
		}
	}
}

void Log::MessagePlatformVA(const Log::Level logLevel, const char * const fmt, va_list args)
{
	if(logLevel >= globalLogLevel) {
		__android_log_vprint(getAndroidLogLevelPriority(logLevel), "TR3DUtils", fmt, args);
	}
}

#else

namespace
{
	const char * getLogLevelName(const Log::Level logLevel)
	{
		switch (logLevel)
		{
		case Log::LEVEL_TRACE:
			return "TRACE";
		case Log::LEVEL_DEBUG:
			return "DEBUG";
		case Log::LEVEL_INFO:
			return "INFO";
		case Log::LEVEL_WARN:
			return "WARN";
		case Log::LEVEL_ERROR:
			return "ERROR";
		default:
			return "UNKNOWN";
		}
	}
}

void Log::MessagePlatformVA(const Log::Level logLevel, const char * const fmt, va_list args)
{
	if (logLevel >= globalLogLevel) {
		printf("%s: ", getLogLevelName(logLevel));
		vprintf(fmt, args);
		printf("\n");
	}
}

void Log::SetHandler(LogHandler handler)
{
    globalLogHandler = handler;
}

#endif
