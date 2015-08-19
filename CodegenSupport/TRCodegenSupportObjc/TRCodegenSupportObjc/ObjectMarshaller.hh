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

#import <TRCodegenSupportObjc/Marshaller.hh>
#import <TRCodegenSupportObjc/Handle.hh>
#import <TRCodegenSupportObjc/BaseObject.h>

namespace CodegenSupportObjc
{
	template <typename T>
	class ObjectMarshaller : public Marshaller<std::shared_ptr<T>, StrongAnyPtr>
	{
	public:
		virtual std::shared_ptr<T> marshall(const StrongAnyPtr & in) const;

		virtual StrongAnyPtr unmarshall(const std::shared_ptr<T> & in) const;

		virtual std::shared_ptr<T> marshallBoxed(const id & in) const;

		virtual id unmarshallBoxed(const std::shared_ptr<T> & in) const;
	};

	template <typename T>
	std::shared_ptr<T> ObjectMarshaller<T>::marshall(const StrongAnyPtr & in) const
	{
		if(in) {
            TRBaseObject * baseObject = in;
			Handle * const handle = reinterpret_cast<Handle*>([baseObject handle]);
			return handle->getNativeObject<T>();
		} else {
			return nullptr;
		}
	}

	template <typename T>
	StrongAnyPtr ObjectMarshaller<T>::unmarshall(const std::shared_ptr<T> & in) const
	{
		T * const obj = in.get();
		if(obj) {
			Handle * const handle = reinterpret_cast<Handle*>(obj->getHandle());
			return handle->getHostObject();
		} else {
			return nil;
		}
	}

	template <typename T>
	std::shared_ptr<T> ObjectMarshaller<T>::marshallBoxed(const id & in) const
	{
		return marshall(in);
	}

	template <typename T>
	id ObjectMarshaller<T>::unmarshallBoxed(const std::shared_ptr<T> & in) const
	{
		return unmarshall(in);
	}
}