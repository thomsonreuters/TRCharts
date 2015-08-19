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

#ifndef CodegenSupport_BaseObject_hpp
#define CodegenSupport_BaseObject_hpp

#include <TRCodegenSupport/Common.hpp>
#include <TRCodegenSupport/NoCopy.hpp>

namespace CodegenSupport
{
	class BaseObject : public std::enable_shared_from_this<BaseObject>, public NoCopy
	{
	public:
		BaseObject(void);

		virtual ~BaseObject(void);

		std::shared_ptr<BaseObject> getSharedPtr(void);

		std::shared_ptr<const BaseObject> getSharedPtr(void) const;

		virtual void setHandle(void * handle);

		virtual void * getHandle(void) const;

	private:
		void * handle;
	};
}

#endif