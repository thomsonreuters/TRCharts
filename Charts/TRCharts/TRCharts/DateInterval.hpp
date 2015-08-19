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
/* NOTE: This file is autogenerated, do not edit this file directly.*/

#ifndef Charts_DateInterval_hpp
#define Charts_DateInterval_hpp

#include <TRCharts/Common.hpp>
#include <TRCharts/DateUnit.hpp>

#include <ostream>

namespace Charts
{
	
	struct DateInterval;

	
	struct GeneratedDateInterval
	{
		Charts::DateUnit unit;
		double magnitude;

		GeneratedDateInterval(void);

		GeneratedDateInterval(Charts::DateUnit unit, double magnitude);

		bool operator==(const GeneratedDateInterval & other) const;

		bool operator!=(const GeneratedDateInterval & other) const;
	};

	
	std::ostream & operator<<(std::ostream & to, const GeneratedDateInterval & from);
}

#include <TRCharts/Impl/DateIntervalImpl.hpp>

#endif