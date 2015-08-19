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

#ifndef TRCharts_Impl_Utils_hpp
#define TRCharts_Impl_Utils_hpp

#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Color.hpp>
#include <TRCharts/Point.hpp>
#include <TRCharts/Coordinates.hpp>
#include <TRCharts/Size.hpp>
#include <TRCharts/Margin.hpp>
#include <TRCharts/Range.hpp>
#include <TRCharts/IndexRange.hpp>
#include <TRCharts/DateInterval.hpp>
#include <TR3DUtils/Common.hpp>

#include <sstream>

namespace Charts
{
	namespace Utils
	{
        // approximate/order-of-magnitude only
        extern const int SECONDS_MINUTE;
        extern const int SECONDS_HOUR;
        extern const int SECONDS_DAY;
        extern const int SECONDS_MONTH;
        extern const int SECONDS_YEAR;
        
		glm::vec2 pointToVec2(const Point & point);

		glm::vec2 pointToVec2Flipped(const Point & point, glm::float_t windowHeight);

		Point vec2ToPoint(const glm::vec2 & vec2);

		Point vec2ToPointFlipped(const glm::vec2 & vec2, glm::float_t windowHeight);

		glm::dvec2 pointToDVec2(const Point & point);
        
		glm::dvec2 pointToDVec2Flipped(const Point & point, double windowHeight);
        
		Point dvec2ToPoint(const glm::dvec2 & vec2);
        
		Point dvec2ToPointFlipped(const glm::dvec2 & vec2, double windowHeight);
        
		Coordinates dvec2ToCoordinates(const glm::dvec2 & vec2);
        
		glm::dvec2 coordinatesToDVec2(const Coordinates & coordinates);
        
		glm::vec2 sizeToVec2(const Size & size);
        
		glm::dvec2 sizeToDVec2(const Size & size);
        
		Size vec2ToSize(const glm::vec2 & vec2);
        
		glm::vec4 colorToVec4(const Color & color);

		Color vec4ToColor(const glm::vec4 & vec4);
        
		glm::float_t opacityToAlpha(double opacity);

		glm::vec4 marginToVec4(const Margin & margin);

		/*Margin addMargins(const Margin & a, const Margin & b);

		Range invalidRange(void);
        
		Range mergeRanges(const Range & a, const Range & b);
        
		double rangeLength(const Range & range);

		bool isRangeValid(const Range & range);

		bool isRangeZero(const Range & range);
        
		bool isIndexRangeValid(const IndexRange & range);
        
		bool isIndexRangeValid(const IndexRange & range, long end);
        
		long indexRangeLength(const IndexRange & range);
        
		bool indexRangesOverlap(const IndexRange & a, const IndexRange & b);
        
		Charts::IndexRange mergeIndexRanges(const IndexRange & a, const IndexRange & b);
        
		IndexRange clampIndexRange(const IndexRange & range, const IndexRange & clamp);*/

		double pow10Floor(double x);

		double pow5Floor(double x);

		double pow2Floor(double x);
        
		double powFloor(double x, double base);
        
		double pow10Ceil(double x);
        
		double powCeil(double x, double base);
        
		double pow10Round(double x);

		double logn(double x, double base);
        
        double roundUp(double x, double f);
        
        double roundDown(double x, double f);
        
        double round(double x, double f);
        
        bool getTime(tm & time, long seconds);
        
        void roundTime(tm & time, const DateInterval & interval);
        
        void incrementTime(tm & time, const DateInterval & interval);
        
        void decrementTime(tm & time, const DateInterval & interval);
        
        int dateUnitSeconds(DateUnit unit);
        
        int timeGet(const tm & time, DateUnit unit);
        
        DateInterval maxDateInterval(const DateInterval & a, const DateInterval & b);
        
        std::string formatDate(double seconds, const std::string & format);
        
        std::string formatDate(const tm & time, const std::string & format);
        
        std::string formatNumber(double value, size_t decimalPlaces);
        
		template<typename T>
		glm::float_t lengthSquared(const T & vec)
		{
			return glm::dot(vec, vec);
		}

		template<typename T>
		glm::float_t distanceSquared(const T & a, const T & b)
		{
			return lengthSquared(a - b);
		}
        
		template<typename T>
		glm::float_t distanceSquaredProj(const T & a, const T & b, const T & proj)
		{
			return lengthSquared((a - b) * proj);
		}
        
		template<typename T>
		bool approxEqual(T a, T b, T epsilon)
		{
			return glm::abs(a - b) < epsilon;
		}
	}
}

#endif
