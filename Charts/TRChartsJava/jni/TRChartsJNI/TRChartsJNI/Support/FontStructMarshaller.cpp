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
/* NOTE: This file is autogenerated, do not edit this file directly.*/

#include <TRChartsJNI/Support/FontStructMarshaller.hpp>
#include <TRChartsJNI/Support/Marshallers.hpp>

using namespace TRChartsJNI;
using namespace Charts;

namespace
{
	bool inited = false;
	jclass cls;
	jmethodID ctor;
	jfieldID fidName;
	jfieldID fidSize;
	jfieldID fidHint;

	void checkInited(JNIEnv * const env)
	{
		if(!::inited) {
			::inited = true;
			::cls = (jclass)env->NewGlobalRef(env->FindClass("com/thomsonreuters/corptech/charts/Font"));
			::ctor = env->GetMethodID(::cls, "<init>", "()V");
			::fidName = env->GetFieldID(cls, "name", "Ljava/lang/String;");
			::fidSize = env->GetFieldID(cls, "size", "J");
			::fidHint = env->GetFieldID(cls, "hint", "Lcom/thomsonreuters/corptech/charts/FontHint;");
		}
	}
}

Font FontStructMarshaller::marshall(JNIEnv * const env, const jobject & in) const
{
	::checkInited(env);
	Font out;
	out.name = TRChartsJNI::getStringMarshaller().getFieldValue(env, in, ::fidName);
	out.size = TRChartsJNI::getIntegerMarshaller().getFieldValue(env, in, ::fidSize);
	out.hint = TRChartsJNI::getFontHintMarshaller().getFieldValue(env, in, ::fidHint);
	return out;
}

jobject FontStructMarshaller::unmarshall(JNIEnv * const env, const Font & in) const
{
	::checkInited(env);
	jobject out = env->NewObject(::cls, ::ctor);
	TRChartsJNI::getStringMarshaller().setFieldValue(env, out, ::fidName, in.name);
	TRChartsJNI::getIntegerMarshaller().setFieldValue(env, out, ::fidSize, in.size);
	TRChartsJNI::getFontHintMarshaller().setFieldValue(env, out, ::fidHint, in.hint);
	return out;
}

Font FontStructMarshaller::getFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID) const
{
	return marshall(env, env->GetObjectField(obj, fieldID));
}

void FontStructMarshaller::setFieldValue(JNIEnv * const env, const jobject obj, const jfieldID fieldID, const Font & value) const
{
	env->SetObjectField(obj, fieldID, unmarshall(env, value));
}

Font FontStructMarshaller::callMethod(JNIEnv * const env, const jobject obj, const jmethodID methodID, jvalue * const args) const
{
	return marshall(env, env->CallObjectMethodA(obj, methodID, args));
}