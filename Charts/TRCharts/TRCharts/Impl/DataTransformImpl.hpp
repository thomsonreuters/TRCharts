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

#ifndef Charts_Impl_DataTransformImpl_hpp
#define Charts_Impl_DataTransformImpl_hpp

#include <TRCharts/DataTransform.hpp>

namespace Charts
{
	struct Range;
    
	struct DataTransform : public GeneratedDataTransform
	{
		DataTransform(void);

		DataTransform(double offset, double scale);

		static Charts::DataTransform concatenate(const Charts::DataTransform & dataTransform, const Charts::DataTransform & otherDataTransform);
        
		static Charts::DataTransform invert(const Charts::DataTransform & dataTransform);
        
		static double apply(const Charts::DataTransform & dataTransform, double value);
        
		static Charts::Range applyRange(const Charts::DataTransform & dataTransform, const Range & range);
        
		static double unapply(const Charts::DataTransform & dataTransform, double value);
        
		static Charts::Range unapplyRange(const Charts::DataTransform & dataTransform, const Range & range);

	};
}

#endif