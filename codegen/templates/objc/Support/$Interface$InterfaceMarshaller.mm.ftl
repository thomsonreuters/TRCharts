[#ftl]
[#include "/templates/objc/_macros.ftl"/]
[#include "/templates/cpp/_macros.ftl"/]
${copyright}
${autogenNote}

#include <${objcFilePrefix}Support/${name}InterfaceMarshaller.hh>
#include <${objcFilePrefix}Support/Marshallers.hh>
#include <${objcCodegenSupportFilePrefix}Handle.hh>
#include <${objcCodegenSupportFilePrefix}BaseObject.h>

${cppTemplateDeclaration!}
class ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy : public ${cppDeclarationName}
{
public:
	Proxy(const ${name}InterfaceMarshaller${cppTemplateParameters!} & marshaller, ${objcCodegenSupportNamespace}::StrongAnyPtr hostObject);

	virtual ~Proxy(void);

	${objcCodegenSupportNamespace}::StrongAnyPtr getHostObject(void) const;

	[#list referencedTypes as type]
	[#if type.returnable && !type.bound]
	const ${objcCodegenSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}> & get${type.name}Marshaller(void) const;

	[/#if]
	[/#list]
	[#list methods as method]
	${""}[@cpp_method_declaration_signature method/];

	[/#list]
private:
	const ${name}InterfaceMarshaller${cppTemplateParameters!} & marshaller;
	mutable id __strong strongHostObject;
};

[#if templateParameters??]
${cppTemplateDeclaration!}
${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::${cppClassname}InterfaceMarshaller([#list templateParameters as param]const ${objcCodegenSupportNamespace}::Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.objcMarshallType}> & marshaller${param.name?cap_first}[#if param_has_next], [/#if][/#list])
:[#list templateParameters as param]marshaller${param.name?cap_first}(marshaller${param.name?cap_first})[#if param_has_next], [/#if][/#list]
{
}
[/#if]

${cppTemplateDeclaration!}
std::shared_ptr<${cppDeclarationName}> ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::marshall(const ${objcCodegenSupportNamespace}::StrongAnyPtr & in) const
{
	if(in) {
		if([in isKindOfClass:[${objcBase} class]]) {
			${objcCodegenSupportNamespace}::Handle * const handle = static_cast<${objcCodegenSupportNamespace}::Handle *>([in handle]);
			return handle->getNativeObject<${cppDeclarationName}>();
		} else {
			return std::make_shared<Proxy>(*this, in);
		}
	}
	return std::shared_ptr<${cppDeclarationName}>();
}

${cppTemplateDeclaration!}
${objcCodegenSupportNamespace}::StrongAnyPtr ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::unmarshall(const std::shared_ptr<${cppDeclarationName}> & in) const
{
	if(in) {
		${cppCodegenSupportNamespace}::BaseObject * const baseObject = dynamic_cast<${cppCodegenSupportNamespace}::BaseObject *>(in.get());
		if(baseObject) {
			${objcCodegenSupportNamespace}::Handle * const handle = static_cast<${objcCodegenSupportNamespace}::Handle *>(baseObject->getHandle());
			return handle->getHostObject();
		} else {
			Proxy * proxy = dynamic_cast<Proxy *>(in.get());
			if(proxy) {
				return proxy->getHostObject();
			} else {
				throw std::logic_error("Cannot unmarshall");
			}
		}
	}
	return nullptr;
}

${cppTemplateDeclaration!}
std::shared_ptr<${cppDeclarationName}> ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::marshallBoxed(const id & in) const
{
	return marshall(in);
}

${cppTemplateDeclaration!}
id ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::unmarshallBoxed(const std::shared_ptr<${cppDeclarationName}> & in) const
{
	return unmarshall(in);
}

// TODO: temporary hack until we fix static init + threads problems properly
${cppTemplateDeclaration!}
void ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::init(void) const
{
[#list referencedTypes as type]
[#if type.returnable && !type.bound]
	get${type.name?cap_first}Marshaller();
[/#if]
[/#list]
}

[#list referencedTypes as type]
[#if type.returnable && !type.bound]
${cppTemplateDeclaration!}
const ${objcCodegenSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}> & ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::get${type.name?cap_first}Marshaller(void) const
{
	[#if type.templateParameter]
	return marshaller${type.name};
	[#else]
	if(!cached${type.name}Marshaller) {
		cached${type.name}Marshaller.reset(new ${type.objcMarshaller});
	}
	return *cached${type.name}Marshaller;
	[/#if]
}

[/#if]
[/#list]

${cppTemplateDeclaration!}
${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy::Proxy(const ${name}InterfaceMarshaller${cppTemplateParameters!} & marshaller, const ${objcCodegenSupportNamespace}::StrongAnyPtr hostObject)
	:marshaller(marshaller), strongHostObject(hostObject)
{
}

${cppTemplateDeclaration!}
${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy::~Proxy(void)
{
	// anything to verify here?
}

${cppTemplateDeclaration!}
${objcCodegenSupportNamespace}::StrongAnyPtr ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy::getHostObject(void) const
{
	return strongHostObject;
}

[#list referencedTypes as type]
[#if type.returnable && !type.bound]
${cppTemplateDeclaration!}
const ${objcCodegenSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}> & ${objcSupportNamespace}::${name}InterfaceMarshaller${cppTemplateParameters!}::Proxy::get${type.name?cap_first}Marshaller(void) const
{
	return marshaller.get${type.name?cap_first}Marshaller();
}

[/#if]
[/#list]
[#list methods as method]
${cppTemplateDeclaration!}
${""}[@cpp_method_implementation_signature objcSupportNamespace + "::" + name + "InterfaceMarshaller" + (cppTemplateParameters!) + "::Proxy", method/]
{
	${""}[@objc_enter_method/]
	id<${objcClassname}> target = getHostObject();
	[#if method.returnType.returnable]return [@objc_marshall method.returnType][target [@objc_call method/]][/@objc_marshall];[#rt]
 	[#else][target [@objc_call method/]];[/#if]
}

[/#list]