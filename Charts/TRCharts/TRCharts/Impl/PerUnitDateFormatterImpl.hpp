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

#ifndef TRCharts_Impl_PerUnitDateFormatterImpl_hpp
#define TRCharts_Impl_PerUnitDateFormatterImpl_hpp

#include <TRCharts/PerUnitDateFormatter.hpp>
#include <TRCharts/DateUnit.hpp>
#include <TRCharts/Impl/Common.hpp>

#include <map>

namespace Charts
{

	
	class PerUnitDateFormatter : public GeneratedPerUnitDateFormatter
	{
	public:
		PerUnitDateFormatter(void);

		virtual ~PerUnitDateFormatter(void);

		virtual void setUnitFormat(Charts::DateUnit unit, const std::string & format);

		virtual std::string getUnitFormat(Charts::DateUnit unit) const;
        
		virtual void setZeroUnitFormat(Charts::DateUnit unit, const std::string & format);
        
		virtual std::string getZeroUnitFormat(Charts::DateUnit unit) const;
        
		virtual std::string formatDate(double seconds, Charts::DateUnit unit) const;

	private:
        std::map<DateUnit, std::string> unitFormats;
        
        std::map<DateUnit, std::string> zeroUnitFormats;
	};
}

#endif