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

#import <TRCodegenSupportObjc/Common.hh>
#import <TRCodegenSupport/BaseObject.hpp>

namespace CodegenSupportObjc
{
	class Handle
	{
	public:
		Handle(CodegenSupport::BaseObject * nativeObject, id hostObject);

		~Handle(void);

		template <typename T>
		std::shared_ptr<T> getNativeObject(void) const;

		id getHostObject(void) const;

		void * getInternalData(void) const;

		void setInternalData(void * data);

	private:
		CodegenSupport::BaseObject * const nativeObject;
		const __weak id weakHostObject;
		mutable std::weak_ptr<CodegenSupport::BaseObject> weakNativeObject;
		mutable __strong id strongHostObject;
		void * internalData;
	};

	template <typename T>
	std::shared_ptr<T> Handle::getNativeObject(void) const
	{
		std::shared_ptr<CodegenSupport::BaseObject> sharedNativeObject = weakNativeObject.lock();
		if(!sharedNativeObject) {
			strongHostObject = weakHostObject;
			sharedNativeObject.reset(nativeObject, [this](CodegenSupport::BaseObject * const ptr) -> void {
				strongHostObject = nil;
			});
			weakNativeObject = sharedNativeObject;
		}
		return std::dynamic_pointer_cast<T>(sharedNativeObject);
	}

}