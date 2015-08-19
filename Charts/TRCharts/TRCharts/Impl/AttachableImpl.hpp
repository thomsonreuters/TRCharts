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

#ifndef TRCharts_Impl_AttachableImpl_hpp
#define TRCharts_Impl_AttachableImpl_hpp

#include <TRCharts/Attachable.hpp>
#include <TRCharts/Impl/Versionable.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class Attachable : public GeneratedAttachable, public Versionable
	{
	public:
		Attachable(void);

		virtual ~Attachable(void);
        
		virtual bool isAttached(void) const;
        
		virtual bool isEnabled(void) const;

		virtual void setEnabled(bool value);
        
		virtual void attach(void);
        
		virtual void detach(void);
        
        virtual bool versionChanged(void) const;
        
        virtual void markVersion(void);
        
	private:
		bool attached;
		bool enabled;
        
        Version lastCleanVersion;
	};
}

#endif