[#ftl]
${copyright}
${autogenNote}

#include <${jniCppFilePrefix}Support/Utils.hpp>
#include <stdexcept>
#ifndef TR_CODEGEN_JNI_DISABLE_THREAD_SAFETY
#include <mutex>
#endif

using namespace ${jniCppNamespace};

namespace
{
	bool inited = false;
	jclass clsBaseObject;
	jmethodID midBaseObjectGetHandle;
	jclass clsList;
	jmethodID midListSize;
	jmethodID midListGet;
	jmethodID midListAdd;
	jclass clsArrayList;
	jmethodID ctorArrayList;
	jclass clsEnum;
	jmethodID midEnumOrdinal;
	jclass clsBoolean;
	jmethodID midBooleanValueOf;
	jmethodID midBooleanBooleanValue;
	jclass clsLong;
	jmethodID midLongValueOf;
	jmethodID midLongLongValue;
	jclass clsDouble;
	jmethodID midDoubleValueOf;
	jmethodID midDoubleDoubleValue;

	void checkInited(JNIEnv * const env)
	{
		if(!::inited) {
			::inited = true;
			::clsBaseObject = (jclass)env->NewGlobalRef(env->FindClass("${jniClassnamePrefix}${javaBaseObject}"));
			::midBaseObjectGetHandle = env->GetMethodID(::clsBaseObject, "getHandle", "()J");
			::clsList = (jclass)env->NewGlobalRef(env->FindClass("java/util/List"));
			::midListSize = env->GetMethodID(::clsList, "size", "()I");
			::midListGet = env->GetMethodID(::clsList, "get", "(I)Ljava/lang/Object;");
			::midListAdd = env->GetMethodID(::clsList, "add", "(Ljava/lang/Object;)Z");
			::clsArrayList = (jclass)env->NewGlobalRef(env->FindClass("java/util/ArrayList"));
			::ctorArrayList = env->GetMethodID(::clsArrayList, "<init>", "(I)V");
			::clsEnum = (jclass)env->NewGlobalRef(env->FindClass("java/lang/Enum"));
			::midEnumOrdinal = env->GetMethodID(::clsEnum, "ordinal", "()I");
			::clsBoolean = (jclass)env->NewGlobalRef(env->FindClass("java/lang/Boolean"));
			::midBooleanValueOf = env->GetStaticMethodID(::clsBoolean, "valueOf", "(Z)Ljava/lang/Boolean;");
			::midBooleanBooleanValue = env->GetMethodID(::clsBoolean, "booleanValue", "()Z");
			::clsLong = (jclass)env->NewGlobalRef(env->FindClass("java/lang/Long"));
			::midLongValueOf = env->GetStaticMethodID(::clsLong, "valueOf", "(J)Ljava/lang/Long;");
			::midLongLongValue = env->GetMethodID(::clsLong, "longValue", "()J");
			::clsDouble = (jclass)env->NewGlobalRef(env->FindClass("java/lang/Double"));
			::midDoubleValueOf = env->GetStaticMethodID(::clsDouble, "valueOf", "(D)Ljava/lang/Double;");
			::midDoubleDoubleValue = env->GetMethodID(::clsDouble, "doubleValue", "()D");
		}
	}

	thread_local JNIEnv * threadEnv = nullptr;

#ifndef TR_CODEGEN_JNI_DISABLE_THREAD_SAFETY
	std::recursive_mutex globalMutex;
#endif
}

JNIEnv * Utils::getThreadEnv(void)
{
	return ::threadEnv;
}

void Utils::threadEnter(JNIEnv * const env)
{
	::threadEnv = env;
#ifndef TR_CODEGEN_JNI_DISABLE_THREAD_SAFETY
	globalMutex.lock();
#endif
}

void Utils::threadExit(void)
{
	::threadEnv = nullptr;
#ifndef TR_CODEGEN_JNI_DISABLE_THREAD_SAFETY
	globalMutex.unlock();
#endif
}

long Utils::getBaseObjectHandle(JNIEnv * const env, const jobject hostObject)
{
	::checkInited(env);
	const long handle = env->CallLongMethod(hostObject, ::midBaseObjectGetHandle);
	return handle;
}

bool Utils::isBaseObjectInstance(JNIEnv * const env, const jobject hostObject)
{
	::checkInited(env);
	return env->IsInstanceOf(hostObject, ::clsBaseObject);
}

jint Utils::listGetSize(JNIEnv * const env, const jobject list)
{
	::checkInited(env);
	return env->CallIntMethod(list, ::midListSize);
}

jobject Utils::listGetElement(JNIEnv * const env, const jobject list, const jint i)
{
	::checkInited(env);
	return env->CallObjectMethod(list, ::midListGet, i);
}

jobject Utils::listCreate(JNIEnv * const env, const jint capacity)
{
	::checkInited(env);
	return env->NewObject(::clsArrayList, ::ctorArrayList, capacity);
}

void Utils::listAdd(JNIEnv * const env, const jobject list, const jobject value)
{
	::checkInited(env);
	env->CallBooleanMethod(list, ::midListAdd, value);
}

jint Utils::enumOrdinal(JNIEnv * env, jobject in)
{
	::checkInited(env);
	return env->CallIntMethod(in, ::midEnumOrdinal);
}

void Utils::throwJavaException(JNIEnv * const env, const char * const msg)
{
	jclass c = env->FindClass("java/lang/RuntimeException");
	env->ThrowNew(c, msg ? msg : "Unknown error");
}

jobject Utils::boxBoolean(JNIEnv * const env, const jboolean value)
{
	return env->CallStaticObjectMethod(clsBoolean, ::midBooleanValueOf, value);
}

jboolean Utils::unboxBoolean(JNIEnv * const env, const jobject value)
{
	return env->CallBooleanMethod(value, ::midBooleanBooleanValue);
}

jobject Utils::boxLong(JNIEnv * const env, const jlong value)
{
	return env->CallStaticObjectMethod(clsLong, ::midLongValueOf, value);
}

jlong Utils::unboxLong(JNIEnv * const env, const jobject value)
{
	return env->CallLongMethod(value, ::midLongLongValue);
}

jobject Utils::boxDouble(JNIEnv * const env, const jdouble value)
{
	return env->CallStaticObjectMethod(clsDouble, ::midDoubleValueOf, value);
}

jdouble Utils::unboxDouble(JNIEnv * const env, const jobject value)
{
	return env->CallDoubleMethod(value, ::midDoubleDoubleValue);
}
