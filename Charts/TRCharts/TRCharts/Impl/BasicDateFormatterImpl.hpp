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

#ifndef Charts_Impl_BasicDateFormatterImpl_hpp
#define Charts_Impl_BasicDateFormatterImpl_hpp

#include <TRCharts/BasicDateFormatter.hpp>
#include <TRCharts/AbstractDateFormatter.hpp>
#include <TRCharts/DateUnit.hpp>
#include <TRCharts/Impl/AbstractDateFormatterImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class BasicDateFormatter : public GeneratedBasicDateFormatter
	{
	public:
		BasicDateFormatter(void);

		virtual ~BasicDateFormatter(void);

		virtual const std::string & getFormat(void) const;

		virtual void setFormat(const std::string & value);

		virtual std::string formatDate(double seconds, Charts::DateUnit unit) const;

	private:
		std::string format;
	};
}

#endif