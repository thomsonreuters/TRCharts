[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_ListMarshaller_hpp
#define ${jniCppHeaderGuardPrefix}Support_ListMarshaller_hpp

#include <${jniCppFilePrefix}Support/BasicObjectMarshaller.hpp>
#include <${jniCppFilePrefix}Support/Utils.hpp>

namespace ${jniCppNamespace}
{
	template <typename T, typename U>
	class ListMarshaller : public BasicObjectMarshaller<std::vector<T>, jobject>
	{
	public:
		ListMarshaller(const Marshaller<T, U> & valueMarshaller);

		virtual std::vector<T> marshall(JNIEnv * env, const jobject & in) const;

		virtual jobject unmarshall(JNIEnv * env, const std::vector<T> & in) const;

	private:
		const Marshaller<T, U> & valueMarshaller;
	};

	template <typename T, typename U>
	ListMarshaller<T, U>::ListMarshaller(const Marshaller<T, U> & valueMarshaller)
		:valueMarshaller(valueMarshaller)
	{
	}

	template <typename T, typename U>
	std::vector<T> ListMarshaller<T, U>::marshall(JNIEnv * env, const jobject & in) const
	{
		std::vector<T> out;
		if(in) {
			const jint size = Utils::listGetSize(env, in);
			for(jint i = 0; i != size; ++i) {
				jobject tmp = Utils::listGetElement(env, in, i);
				out.push_back(valueMarshaller.marshallBoxed(env, tmp));
				env->DeleteLocalRef(tmp);
			}
		}
		return out;
	}

	template <typename T, typename U>
	jobject ListMarshaller<T, U>::unmarshall(JNIEnv * env, const std::vector<T> & in) const
	{
		const jobject out = Utils::listCreate(env, in.size());
		for(const T & element : in) {
			jobject tmp = valueMarshaller.unmarshallBoxed(env, element);
		 	Utils::listAdd(env, out, tmp);
			env->DeleteLocalRef(tmp);
		}
		return out;
	}
}

#endif