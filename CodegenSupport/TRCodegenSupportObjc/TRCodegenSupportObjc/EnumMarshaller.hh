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

namespace CodegenSupportObjc
{
	template <typename T, typename U>
	class EnumMarshaller : public Marshaller<T, U>
	{
	public:
		virtual T marshall(const U & in) const;

		virtual U unmarshall(const T & in) const;

		virtual T marshallBoxed(const id & in) const;

		virtual id unmarshallBoxed(const T & in) const;
	};

	template <typename T, typename U>
	T EnumMarshaller<T, U>::marshall(const U & in) const
	{
		return static_cast<T>(in);
	}

	template <typename T, typename U>
	U EnumMarshaller<T, U>::unmarshall(const T & in) const
	{
		return static_cast<U>(in);
	}

	template <typename T, typename U>
	T EnumMarshaller<T, U>::marshallBoxed(const id & in) const
	{
		return marshall(static_cast<U>([(NSNumber*)in intValue]));
	}

	template <typename T, typename U>
	id EnumMarshaller<T, U>::unmarshallBoxed(const T & in) const
	{
		return [NSNumber numberWithInteger:static_cast<int>(unmarshall(in))];
	}
}