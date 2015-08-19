[#ftl]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_Utils_hpp
#define ${jniCppHeaderGuardPrefix}Support_Utils_hpp

#include <${jniCppFilePrefix}Support/Common.hpp>
#include <functional>

namespace ${jniCppNamespace}
{
	namespace Utils
	{
		class EndScopeAction
		{
		public:
			EndScopeAction(const std::function<void(void)> & f)
				:f(f)
			{
			}

			~EndScopeAction(void)
			{
				f();
			}

		private:
			const std::function<void(void)> f;
		};

		JNIEnv * getThreadEnv(void);

		void threadEnter(JNIEnv * env);

		void threadExit(void);

		long getBaseObjectHandle(JNIEnv * env, jobject hostObject);

		bool isBaseObjectInstance(JNIEnv * env, jobject hostObject);

		jint listGetSize(JNIEnv * env, jobject list);

		jobject listGetElement(JNIEnv * env, jobject list, jint i);

		void listGetElements(JNIEnv * env, jobject hostObject, std::vector<jobject> & out);

		jobject listCreate(JNIEnv * env, jint capacity);

		jint enumOrdinal(JNIEnv * env, jobject in);

		void listAdd(JNIEnv * env, jobject list, jobject value);

		void throwJavaException(JNIEnv * env, const char * msg);

		jobject boxBoolean(JNIEnv * env, jboolean value);

		jboolean unboxBoolean(JNIEnv * env, jobject value);

		jobject boxLong(JNIEnv * env, jlong value);

		jlong unboxLong(JNIEnv * env, jobject value);

		jobject boxDouble(JNIEnv * env, jdouble value);

		jdouble unboxDouble(JNIEnv * env, jobject value);
	}
}

#endif

