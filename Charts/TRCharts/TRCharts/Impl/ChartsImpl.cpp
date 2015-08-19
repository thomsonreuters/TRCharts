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

#ifndef TRCharts_Impl_ChartsImpl_cpp
#define TRCharts_Impl_ChartsImpl_cpp

#include <TRCharts/Impl/ChartsImpl.hpp>
#include <TR3DUtils/Debug.hpp>

Charts::LogLevel Charts::Impl::getLogLevel(void)
{
	return LogLevel(TR3DUtils::Log::GetLevel());
}

void Charts::Impl::setLogLevel(Charts::LogLevel value)
{
	return TR3DUtils::Log::SetLevel(TR3DUtils::Log::Level(value));
}

namespace
{
    std::shared_ptr<Charts::LogHandler> logHandler;
    
#warning untested
    std::string strVSPrintF(const char * fmt, va_list args)
    {
        const size_t INITIAL_BUFFER_SIZE = 255;
        char initialBuffer[INITIAL_BUFFER_SIZE];
        const int size = vsnprintf(initialBuffer, INITIAL_BUFFER_SIZE, fmt, args);
        if(TR_VERIFY(size >= 0)) {
            if(size_t(size) < INITIAL_BUFFER_SIZE) {
                return std::string(initialBuffer, size);
            } else {
                char * buffer = new char[size + 1];
                vprintf(buffer, args);
                const std::string result(buffer, size);
                delete [] buffer;
                return result;
            }
        } else {
            return "";
        }
    }
    
    void logHandlerAdaptor(TR3DUtils::Log::Level level, const char * fmt, va_list args)
    {
        if(logHandler) {
            logHandler->logMessage(Charts::LogLevel(level), strVSPrintF(fmt, args));
        }
    }
}

const std::shared_ptr<Charts::LogHandler> & Charts::Impl::getLogHandler(void)
{
    return logHandler;
}

void Charts::Impl::setLogHandler(const std::shared_ptr<Charts::LogHandler> & value)
{
    logHandler = value;
    if(logHandler) {
        TR3DUtils::Log::SetHandler(nullptr);
    } else {
        TR3DUtils::Log::SetHandler(logHandlerAdaptor);
    }
}

bool Charts::Impl::isDebugGLValidationEnabled(void)
{
	return TR3DUtils::Debug::isGLValidationEnabled();
}

void Charts::Impl::setDebugGLValidationEnabled(bool value)
{
	TR3DUtils::Debug::setGLValidationEnabled(value);
}

#endif