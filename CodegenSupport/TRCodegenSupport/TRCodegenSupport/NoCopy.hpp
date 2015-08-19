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

#ifndef CodegenSupport_NoCopy_hpp
#define CodegenSupport_NoCopy_hpp

#include <TRCodegenSupport/Common.hpp>

namespace CodegenSupport
{
	class NoCopy
	{
	public:
		NoCopy(void)
		{
		}
        
		virtual ~NoCopy(void)
		{
		}
        
	private:
		NoCopy(const NoCopy & copy);
        
		NoCopy & operator=(const NoCopy & copy) const;
	};
}

#endif