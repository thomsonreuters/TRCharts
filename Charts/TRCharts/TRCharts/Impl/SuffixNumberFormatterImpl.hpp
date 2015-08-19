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

#ifndef TRCharts_Impl_SuffixNumberFormatterImpl_hpp
#define TRCharts_Impl_SuffixNumberFormatterImpl_hpp

#include <TRCharts/SuffixNumberFormatter.hpp>
#include <TRCharts/BasicNumberFormatter.hpp>
#include <TRCharts/Impl/BasicNumberFormatterImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class SuffixNumberFormatter : public GeneratedSuffixNumberFormatter
	{
	public:
		SuffixNumberFormatter(void);

		virtual ~SuffixNumberFormatter(void);

		virtual long getBase(void) const;

		virtual void setBase(long value);

		virtual const std::vector<std::string> & getSuffixes(void) const;

		virtual void setSuffixes(const std::vector<std::string> & value);

		virtual std::string formatNumber(double value) const;

    private:
        void recalculatePowers(void);
        
	private:
		long base;
		std::vector<std::string> suffixes;
        
        std::vector<double> powers;
	};
}

#endif