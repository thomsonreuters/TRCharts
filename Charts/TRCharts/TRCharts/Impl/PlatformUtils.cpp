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

#ifndef TRCharts_Impl_PlatformUtils_cpp
#define TRCharts_Impl_PlatformUtils_cpp

#include <TRCharts/Impl/PlatformUtils.hpp>
#include <TRCharts/Impl/Utils.hpp>

#ifdef __APPLE__

#define TRCHARTS_HAS_PLATFORM_FORMAT_DATE
#define TRCHARTS_HAS_PLATFORM_FORMAT_NUMBER

#include <TR3DUtils/Utils.hpp>

#include <CoreFoundation/CoreFoundation.h>

namespace
{
    std::string stringFromCFStringRef(CFStringRef stringRef, const std::string & def)
    {
        std::string result = def;
        if(const char * const ptr = CFStringGetCStringPtr(stringRef, kCFStringEncodingUTF8)) {
            result = ptr;
        } else {
            const size_t length = CFStringGetMaximumSizeForEncoding(CFStringGetLength(stringRef) + 1, kCFStringEncodingUTF8);
            char * const buffer = new char[length];
            if(TR_VERIFY(CFStringGetCString(stringRef, buffer, length, kCFStringEncodingUTF8))) {
                result = buffer;
            }
            delete [] buffer;
        }
        return result;
    }
}

std::string Charts::PlatformUtils::formatDate(double seconds, const std::string & format)
{
    const double MACH_TIMESTAMP_OFFSET = 978307200;
    std::string result = "?";
    if(const CFLocaleRef localeRef = CFLocaleCopyCurrent()) {
        if(const CFDateFormatterRef dateFormatterRef = CFDateFormatterCreate (NULL, localeRef, kCFDateFormatterNoStyle, kCFDateFormatterNoStyle)) {
            if(const CFTimeZoneRef timezoneRef = CFTimeZoneCreateWithTimeIntervalFromGMT(NULL, 0)) {
                CFDateFormatterSetProperty(dateFormatterRef, kCFDateFormatterTimeZone, timezoneRef);
                if(const CFStringRef formatRef = CFStringCreateWithCString(NULL, format.c_str(), kCFStringEncodingUTF8)) {
                    CFDateFormatterSetFormat(dateFormatterRef, formatRef);
                    const CFAbsoluteTime absoluteTime = seconds - MACH_TIMESTAMP_OFFSET;
                    if(const CFStringRef stringRef = CFDateFormatterCreateStringWithAbsoluteTime(NULL, dateFormatterRef, absoluteTime)) {
                        result = ::stringFromCFStringRef(stringRef, result);
                        CFRelease(stringRef);
                    }
                    CFRelease(formatRef);
                }
                CFRelease(timezoneRef);
            }
            CFRelease(dateFormatterRef);
        }
        CFRelease(localeRef);
    }
    return result;
    
}

std::string Charts::PlatformUtils::formatNumber(const double value, size_t decimalPlaces)
{
	std::string result = "?";
    const void * valuePtr = &value;
	if(const CFNumberRef numberRef = CFNumberCreate(NULL, kCFNumberDoubleType, valuePtr)) {
		if(const CFLocaleRef localeRef = CFLocaleCopyCurrent()) {
			if(const CFNumberFormatterRef formatterRef = CFNumberFormatterCreate(NULL, localeRef, kCFNumberFormatterDecimalStyle)) {
                if(const CFNumberRef decimalPlacesRef = CFNumberCreate(NULL, kCFNumberLongType, &decimalPlaces)) {
                    CFNumberFormatterSetProperty(formatterRef, kCFNumberFormatterMaxFractionDigits, decimalPlacesRef);
                    CFRelease(decimalPlacesRef);
                }
				if(const CFStringRef stringRef = CFNumberFormatterCreateStringWithNumber(NULL, formatterRef, numberRef)) {
                    result = ::stringFromCFStringRef(stringRef, result);
					CFRelease(stringRef);
				}
				CFRelease(formatterRef);
			}
			CFRelease(localeRef);
		}
		CFRelease(numberRef);
	}
	return result;
}

#endif


#ifndef TRCHARTS_HAS_PLATFORM_FORMAT_DATE

std::string Charts::PlatformUtils::formatDate(double seconds, const std::string & format)
{
	return Utils::formatDate(seconds, format);
}

#endif

#ifndef TRCHARTS_HAS_PLATFORM_FORMAT_NUMBER

std::string Charts::PlatformUtils::formatNumber(const double value, size_t decimalPlaces)
{
	return Utils::formatNumber(value, decimalPlaces);
}

#endif

#endif
