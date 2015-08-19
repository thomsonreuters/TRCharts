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

#ifndef Charts_Impl_AbstractDateFormatterImpl_hpp
#define Charts_Impl_AbstractDateFormatterImpl_hpp

#include <TRCharts/AbstractDateFormatter.hpp>
#include <TRCharts/DateFormatter.hpp>
#include <TRCharts/FormatSyntax.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class AbstractDateFormatter : public GeneratedAbstractDateFormatter
	{
	public:
		AbstractDateFormatter(void);

		virtual ~AbstractDateFormatter(void);

		virtual Charts::FormatSyntax getSyntax(void) const;

		virtual void setSyntax(Charts::FormatSyntax value);
        
    protected:
		virtual std::string formatDateImpl(double seconds, const std::string & format) const;
        
		virtual std::string formatDateImpl(tm * time, const std::string & format) const;
        
	private:
		Charts::FormatSyntax syntax;
	};
}

#endif