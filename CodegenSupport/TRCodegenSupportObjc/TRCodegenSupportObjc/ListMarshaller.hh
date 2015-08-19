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

#import <vector>

namespace CodegenSupportObjc
{
	template <typename T, typename U>
	class ListMarshaller : public Marshaller<std::vector<T>, StrongArrayPtr>
	{
	public:
		ListMarshaller(const Marshaller<T, U> & valueMarshaller);

		virtual std::vector<T> marshall(const StrongArrayPtr & in) const;

		virtual StrongArrayPtr unmarshall(const std::vector<T> & in) const;

		virtual std::vector<T> marshallBoxed(const id & in) const;

		virtual id unmarshallBoxed(const std::vector<T> & in) const;

	private:
		const Marshaller<T, U> & valueMarshaller;
	};

	template <typename T, typename U>
	inline ListMarshaller<T, U>::ListMarshaller(const Marshaller<T, U> & valueMarshaller)
		:valueMarshaller(valueMarshaller)
	{
	}

	template <typename T, typename U>
	inline std::vector<T> ListMarshaller<T, U>::marshall(const StrongArrayPtr & in) const
	{
		std::vector<T> out;
		for(id elemIn in in) {
			out.push_back(valueMarshaller.marshallBoxed(elemIn));
		}
		return out;
	}

	template <typename T, typename U>
	inline StrongArrayPtr ListMarshaller<T, U>::unmarshall(const std::vector<T> & in) const
	{
		NSMutableArray * const out = [[NSMutableArray alloc]init];
		for(const T elemIn : in) {
			[out addObject:valueMarshaller.unmarshallBoxed(elemIn)];
		}
		return out;
	}

	template <typename T, typename U>
	inline std::vector<T> ListMarshaller<T, U>::marshallBoxed(const id & in) const
	{
		return marshall(in);
	}

	template <typename T, typename U>
	inline id ListMarshaller<T, U>::unmarshallBoxed(const std::vector<T> & in) const
	{
		return unmarshall(in);
	}
}