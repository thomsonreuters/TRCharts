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

#ifndef TRCharts_Impl_Utils_cpp
#define TRCharts_Impl_Utils_cpp

#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>

#include <cmath>
#include <ctime>
#include <iomanip>

const int Charts::Utils::SECONDS_MINUTE = 60;
const int Charts::Utils::SECONDS_HOUR = SECONDS_MINUTE * 60;
const int Charts::Utils::SECONDS_DAY = SECONDS_HOUR * 24;
const int Charts::Utils::SECONDS_MONTH = SECONDS_DAY * 30;
const int Charts::Utils::SECONDS_YEAR = SECONDS_DAY * 365;

glm::vec2 Charts::Utils::pointToVec2(const Point & point)
{
	return glm::vec2(point.x, point.y);
}

glm::vec2 Charts::Utils::pointToVec2Flipped(const Point & point, glm::float_t windowHeight)
{
	return glm::vec2(point.x, windowHeight - point.y);
}

Charts::Point Charts::Utils::vec2ToPoint(const glm::vec2 & vec2)
{
	return Point(vec2.x, vec2.y);
}

Charts::Point Charts::Utils::vec2ToPointFlipped(const glm::vec2 & vec2, glm::float_t windowHeight)
{
	return Point(vec2.x, windowHeight - vec2.y);
}

Charts::Point Charts::Utils::dvec2ToPoint(const glm::dvec2 & vec2)
{
	return Point(vec2.x, vec2.y);
}

glm::dvec2 Charts::Utils::pointToDVec2(const Point & point)
{
	return glm::dvec2(point.x, point.y);
}

glm::dvec2 Charts::Utils::pointToDVec2Flipped(const Point & point, double windowHeight)
{
	return glm::dvec2(point.x, windowHeight - point.y);
}

Charts::Coordinates Charts::Utils::dvec2ToCoordinates(const glm::dvec2 & vec2)
{
	return Coordinates(vec2.x, vec2.y);
}

Charts::Point Charts::Utils::dvec2ToPointFlipped(const glm::dvec2 & vec2, double windowHeight)
{
	return Point(vec2.x, windowHeight - vec2.y);
}

glm::dvec2 Charts::Utils::coordinatesToDVec2(const Charts::Coordinates & coordinates)
{
	return glm::dvec2(coordinates.abscissa, coordinates.ordinate);
}

glm::vec2 Charts::Utils::sizeToVec2(const Size & size)
{
	return glm::vec2(size.width, size.height);
}

glm::dvec2 Charts::Utils::sizeToDVec2(const Size & size)
{
	return glm::dvec2(size.width, size.height);
}

Charts::Size Charts::Utils::vec2ToSize(const glm::vec2 & vec2)
{
    return Charts::Size(vec2.x, vec2.y);
}

glm::vec4 Charts::Utils::colorToVec4(const Color & color)
{
	return glm::vec4(color.red / 255.f, color.green / 255.f, color.blue / 255.f, color.alpha / 255.f);
}

Charts::Color Charts::Utils::vec4ToColor(const glm::vec4 & vec4)
{
	return Color(vec4.x * 255.f, vec4.y * 255.f, vec4.z * 255.f, vec4.w * 255.f);
}

glm::float_t Charts::Utils::opacityToAlpha(double opacity)
{
    return glm::float_t(opacity / 255.f);
}

glm::vec4 Charts::Utils::marginToVec4(const Margin & margin)
{
	return glm::vec4(margin.left, margin.right, margin.top, margin.bottom);
}

/*
Charts::Margin Charts::Utils::addMargins(const Margin & a, const Margin & b)
{
	return Charts::Margin(a.left + b.left, a.right + b.right, a.bottom + b.bottom, a.top + b.top);
}

Charts::Range Charts::Utils::invalidRange(void)
{
	return Charts::Range(std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());
}

Charts::Range Charts::Utils::mergeRanges(const Range & a, const Range & b)
{
	return Range(std::min(a.min, b.min), std::max(a.max, b.max));
}

double Charts::Utils::rangeLength(const Charts::Range & range)
{
    return range.max - range.min;
}

bool Charts::Utils::isRangeValid(const Charts::Range & range)
{
	return range.min <= range.max;
}

bool Charts::Utils::isRangeZero(const Charts::Range & range)
{
	return approxEqual(range.min, range.max, 0.000001);
}

bool Charts::Utils::isIndexRangeValid(const Charts::IndexRange & range)
{
	return (range.begin >= 0) && (range.begin <= range.end);
}

bool Charts::Utils::isIndexRangeValid(const Charts::IndexRange & range, long end)
{
	return isIndexRangeValid(range) && range.end <= end;
}

long Charts::Utils::indexRangeLength(const IndexRange & range)
{
	return range.end - range.begin;
}

bool Charts::Utils::indexRangesOverlap(const IndexRange & a, const IndexRange & b)
{
	return std::max(a.begin, b.begin) <= std::min(a.end, b.end);
}

Charts::IndexRange Charts::Utils::mergeIndexRanges(const IndexRange & a, const IndexRange & b)
{
	return IndexRange(std::min(a.begin, b.begin), std::max(a.end, b.end));
}

Charts::IndexRange Charts::Utils::clampIndexRange(const Charts::IndexRange & range, const Charts::IndexRange & clamp)
{
	return IndexRange(std::max(clamp.begin, range.begin), std::min(clamp.end, range.end));
}*/

double Charts::Utils::pow10Floor(double x)
{
	return std::pow(10, std::floor(std::log10(x)));
}

double Charts::Utils::pow5Floor(double x)
{
	return std::pow(5, std::floor(logn(x, 5)));
}

double Charts::Utils::pow2Floor(double x)
{
	return std::pow(2, std::floor(logn(x, 2)));
}

double Charts::Utils::powFloor(double x, double base)
{
	return std::pow(base, std::floor(logn(x, base)));
}

double Charts::Utils::pow10Ceil(double x)
{
	return std::pow(10, std::ceil(std::log10(x)));
}

double Charts::Utils::powCeil(double x, double base)
{
	return std::pow(base, std::ceil(logn(x, base)));
}

double Charts::Utils::logn(double x, double base)
{
	return std::log(x) / std::log(base);
}

double Charts::Utils::pow10Round(double x)
{
	return std::pow(10, std::floor(std::log10(2 * x)));
}

double Charts::Utils::roundUp(double value, double factor)
{
	return factor * std::ceil(value / factor);
}

double Charts::Utils::roundDown(double value, double factor)
{
	return factor * std::floor(value / factor);
}

double Charts::Utils::round(double value, double factor)
{
	return factor * glm::round(value / factor);
}

bool Charts::Utils::getTime(tm & time, long seconds)
{
	const time_t tmp = time_t(seconds);
#ifdef __APPLE__
	tm buffer;
	const tm * const result = gmtime_r(&tmp, &buffer);
#else
#warning No threadsafe gmtime available
	const tm * const result = std::gmtime(&tmp);
#endif
	if (result) {
		time = *result;
		return true;
	} else {
		return false;
	}
}

void Charts::Utils::roundTime(tm & time, const DateInterval & interval)
{
	switch (interval.unit)
	{
	case DateUnit::Year:
		time.tm_year = Utils::roundDown(time.tm_year, interval.magnitude);
		time.tm_mon = 0;
	case DateUnit::Month:
		time.tm_mon = Utils::roundDown(time.tm_mon, interval.magnitude);
		time.tm_mday = 0;
	case DateUnit::Day:
		time.tm_mday = Utils::roundDown(time.tm_mday, interval.magnitude);
		time.tm_hour = 0;
	case DateUnit::Hour:
		time.tm_hour = Utils::roundDown(time.tm_hour, interval.magnitude);
		time.tm_min = 0;
	case DateUnit::Minute:
		time.tm_min = Utils::roundDown(time.tm_min, interval.magnitude);
		time.tm_sec = 0;
	case DateUnit::Second:
		time.tm_sec = Utils::roundDown(time.tm_sec, interval.magnitude);
	default:
		break;
	}
}

void Charts::Utils::incrementTime(tm & time, const DateInterval & interval)
{
	switch (interval.unit) {
	case DateUnit::Year:
		time.tm_year += interval.magnitude;
		break;
	case DateUnit::Month:
		time.tm_mon += interval.magnitude;
		break;
	case DateUnit::Day:
		time.tm_mday += interval.magnitude;
		break;
	case DateUnit::Hour:
		time.tm_hour += interval.magnitude;
		break;
	case DateUnit::Minute:
		time.tm_min += interval.magnitude;
		break;
	case DateUnit::Second:
		time.tm_sec += interval.magnitude;
		break;
	}
}

void Charts::Utils::decrementTime(tm & time, const DateInterval & interval)
{
	switch (interval.unit) {
    case DateUnit::Year:
        time.tm_year -= interval.magnitude;
        break;
    case DateUnit::Month:
        time.tm_mon -= interval.magnitude;
        break;
    case DateUnit::Day:
        time.tm_mday -= interval.magnitude;
        break;
    case DateUnit::Hour:
        time.tm_hour -= interval.magnitude;
        break;
    case DateUnit::Minute:
        time.tm_min -= interval.magnitude;
        break;
    case DateUnit::Second:
        time.tm_sec -= interval.magnitude;
        break;
	}
}

int Charts::Utils::dateUnitSeconds(DateUnit unit)
{
	switch (unit) {
	case DateUnit::Year:
		return SECONDS_YEAR;
	case DateUnit::Month:
		return SECONDS_MONTH;
	case DateUnit::Day:
		return SECONDS_DAY;
	case DateUnit::Hour:
		return SECONDS_HOUR;
	case DateUnit::Minute:
		return SECONDS_MINUTE;
	case DateUnit::Second:
		return 1;
	default:
		return 0;
	}
}

int Charts::Utils::timeGet(const tm & time, DateUnit unit)
{
	switch (unit)
	{
	case DateUnit::Year:
		return time.tm_year;
	case DateUnit::Month:
		return time.tm_mon;
	case DateUnit::Day:
		return time.tm_mday;
	case DateUnit::Hour:
		return time.tm_hour;
	case DateUnit::Minute:
		return time.tm_min;
	case DateUnit::Second:
		return time.tm_min;
	default:
		return 0;
	}
}

Charts::DateInterval Charts::Utils::maxDateInterval(const Charts::DateInterval & a, const Charts::DateInterval & b)
{
	const int unitOrdinalA = int(a.unit);
	const int unitOrdinalB = int(b.unit);
	if (unitOrdinalA > unitOrdinalB) {
		return a;
	} else if (unitOrdinalB > unitOrdinalA) {
		return b;
	} else if (a.magnitude > b.magnitude) {
		return a;
	} else {
		return b;
	}
}

std::string Charts::Utils::formatDate(double seconds, const std::string & format)
{
	tm time = tm();
	if (TR_VERIFY(getTime(time, seconds))) {
		return formatDate(time, format);
	} else {
		return "?";
	}
}

std::string Charts::Utils::formatDate(const tm & time, const std::string & format)
{
#ifdef __APPLE__
	std::stringstream buffer;
	buffer << std::put_time(&time, format.c_str());
	return buffer.str();
#else
	const size_t BUFFER_SIZE = 64;
	char buffer[BUFFER_SIZE];
	if(strftime(buffer, BUFFER_SIZE, format.c_str(), &time)) {
		return std::string(buffer);
	} else {
		return "?";
	}
#endif
}

std::string Charts::Utils::formatNumber(double value, size_t decimalPlaces)
{
    std::ostringstream stream;
    stream.precision(decimalPlaces);
    stream << std::fixed;
    stream << value;
    return stream.str();
}

#endif
