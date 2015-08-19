[#ftl]
[#include "/templates/jni/_macros.ftl"/]
[#include "/templates/cpp/_macros.ftl"/]
${copyright}
${autogenNote}

#ifndef ${jniCppHeaderGuardPrefix}Support_${name}InterfaceMarshaller_cpp
#define ${jniCppHeaderGuardPrefix}Support_${name}InterfaceMarshaller_cpp

#include <${jniCppFilePrefix}Support/${name}InterfaceMarshaller.hpp>
#include <${jniCppFilePrefix}Support/Marshallers.hpp>
#include <${jniCppFilePrefix}Support/Handle.hpp>

#include <cassert>

${cppTemplateDeclaration!}
bool ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::inited = false;

${cppTemplateDeclaration!}
jclass ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::cls = nullptr;

[#list methods as method]
${cppTemplateDeclaration!}
jmethodID ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::mid${method.name?cap_first} = nullptr;

[/#list]
${cppTemplateDeclaration!}
class ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy : public ${cppDeclarationName}
{
public:
	Proxy(JNIEnv * env, const ${name}InterfaceMarshaller${cppTemplateParameters!} & marshaller, jobject hostObject);

	virtual ~Proxy(void);

	jobject getHostObject(JNIEnv * env) const;

	[#list methods as method]
	${""}[@cpp_method_declaration_signature method/];
	[/#list]

private:
	const ${name}InterfaceMarshaller${cppTemplateParameters!} & marshaller;
	const jweak weakHostObject;
};

[#if templateParameters??]
${cppTemplateDeclaration!}
${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::${cppClassname}InterfaceMarshaller([#list templateParameters as param]const Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.cppJniType}> & marshaller${param.name?cap_first}[#if param_has_next], [/#if][/#list])
:[#list templateParameters as param]marshaller${param.name?cap_first}(marshaller${param.name?cap_first})[#if param_has_next], [/#if][/#list]
{
}
[/#if]

${cppTemplateDeclaration!}
void ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::checkInited(JNIEnv * const env)
{
	if(!inited) {
		inited = true;
		cls = (jclass)env->NewGlobalRef(env->FindClass("${jniClassnamePrefix}${javaClassname}"));
		[#list methods as method]
		mid${method.name?cap_first} = env->GetMethodID(cls, "${method.name}", "${method.jniSignature}");
		[/#list]
	}
}

${cppTemplateDeclaration!}
std::shared_ptr<${cppDeclarationName}> ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::marshall(JNIEnv * const env, const jobject & in) const
{
	checkInited(env);
	if(in) {
		if(Utils::isBaseObjectInstance(env, in)) {
			Handle * const handle = reinterpret_cast<Handle *>(Utils::getBaseObjectHandle(env, in));
			return handle->getNativeObject<${cppDeclarationName}>(env);
		} else {
			Proxy * const impl = new Proxy(env, *this, in);
			const jobject strongRef = env->NewGlobalRef(in);
			return std::shared_ptr<${cppDeclarationName}>(impl, [=](${cppDeclarationName} * const ptr) -> void {
				delete ptr;
				env->DeleteGlobalRef(strongRef);
			});
		}
	}
	return std::shared_ptr<${cppDeclarationName}>();
}

${cppTemplateDeclaration!}
jobject ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::unmarshall(JNIEnv * const env, const std::shared_ptr<${cppDeclarationName}> & in) const
{
	checkInited(env);
	if(in) {
		${cppCodegenSupportNamespace}::BaseObject * const baseObject = dynamic_cast<${cppCodegenSupportNamespace}::BaseObject *>(in.get());
		if(baseObject) {
			Handle * const handle = reinterpret_cast<Handle *>(baseObject->getHandle());
			return handle->getHostObject(env);
		} else {
			Proxy * proxy = dynamic_cast<Proxy *>(in.get());
			if(proxy) {
				return proxy->getHostObject(env);
			} else {
				throw new std::logic_error("Cannot unmarshall");
			}
		}
	}
	return nullptr;
}

[#list referencedTypes as type]
[#if type.returnable && !type.bound]
${cppTemplateDeclaration!}
const ${jniCppNamespace}::Marshaller<${type.cppValueType}, ${type.cppJniType}> & ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::get${type.name?cap_first}Marshaller(void) const
{
	[#if type.templateParameter]
	return marshaller${type.name};
	[#else]
	if(!cached${type.name}Marshaller) {
		cached${type.name}Marshaller.reset(new ${type.jniMarshaller});
	}
	return *cached${type.name}Marshaller;
	[/#if]
}

[/#if]
[/#list]

${cppTemplateDeclaration!}
${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy::Proxy(JNIEnv * const env, const ${name}InterfaceMarshaller${cppTemplateParameters!} & marshaller, const jobject hostObject)
	:marshaller(marshaller), weakHostObject(env->NewWeakGlobalRef(hostObject))
{
}

${cppTemplateDeclaration!}
${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy::~Proxy(void)
{
	JNIEnv * const env = Utils::getThreadEnv();
	assert(env);
	env->DeleteWeakGlobalRef(weakHostObject);
}

${cppTemplateDeclaration!}
jobject ${jniCppNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy::getHostObject(JNIEnv * const env) const
{
	return env->NewLocalRef(weakHostObject);
}

[#list methods as method]
${cppTemplateDeclaration!}
${""}[@cpp_method_implementation_signature jniCppNamespace + "::" + name + "InterfaceMarshaller" + (cppTemplateParameters!) + "::Proxy", method/]
{
	JNIEnv * const env = Utils::getThreadEnv();
	assert(env);
	checkInited(env);
	jvalue args[] = {
		[#list method.parameters as param]
		[@jni_marshaller param.type/].unmarshallToValue(env, ${param.name})[#if param_has_next],[/#if]
		[/#list]
	};
	const jobject hostObject = getHostObject(env);
	[#if method.returnType.returnable]
	const ${method.returnType.cppValueType} result = [@jni_marshaller method.returnType/].callMethod(env, hostObject, mid${method.name?cap_first}, args);
	env->DeleteLocalRef(hostObject);
	return result;
	[#else]
	env->CallVoidMethodA(hostObject, mid${method.name?cap_first}, args);
	env->DeleteLocalRef(hostObject);
	[/#if]
}

[/#list]
#endif