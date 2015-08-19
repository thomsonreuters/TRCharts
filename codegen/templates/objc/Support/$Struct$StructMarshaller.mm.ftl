[#ftl]
[#include "/templates/objc/_macros.ftl"/]
${copyright}
${autogenNote}

#import <${objcFilePrefix}Support/${name}StructMarshaller.hh>
#import <${objcFilePrefix}Support/Marshallers.hh>

[#if templateParameters??]
${cppTemplateDeclaration!}
${objcSupportNamespace}::${name}StructMarshaller${cppTemplateParameters!}::${cppClassname}StructMarshaller([#list templateParameters as param]const Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.objcMarshallType}> & marshaller${param.name?cap_first}[#if param_has_next], [/#if][/#list])
:[#list templateParameters as param]marshaller${param.name?cap_first}(marshaller${param.name?cap_first})[#if param_has_next], [/#if][/#list]
{
}
[/#if]

${cppTemplateDeclaration!}
${cppDeclarationName} ${objcSupportNamespace}::${name}StructMarshaller${cppTemplateParameters!}::marshall(const ${objcCodegenSupportNamespace}::StrongAnyPtr & in) const
{
	${objcClassname} * const tmp = (${objcClassname}*)in;
	${cppDeclarationName} out;
	[#list allFields as field]
	out.${field.name} = [@objc_marshall field.type][tmp ${field.name}][/@objc_marshall];
	[/#list]
	return out;
}

${cppTemplateDeclaration!}
${objcCodegenSupportNamespace}::StrongAnyPtr ${objcSupportNamespace}::${name}StructMarshaller${cppTemplateParameters!}::unmarshall(const ${cppDeclarationName} & in) const
{
	${objcClassname} * out = [[${objcClassname} alloc] init];
	[#list allFields as field]
	[out set${field.name?cap_first}:[@objc_unmarshall field.type]in.${field.name}[/@objc_unmarshall]];
	[/#list]
	return out;
}

${cppTemplateDeclaration!}
${cppDeclarationName} ${objcSupportNamespace}::${name}StructMarshaller${cppTemplateParameters!}::marshallBoxed(const id & in) const
{
	return marshall(in);
}

${cppTemplateDeclaration!}
id ${objcSupportNamespace}::${name}StructMarshaller${cppTemplateParameters!}::unmarshallBoxed(const ${cppDeclarationName} & in) const
{
	return unmarshall(in);
}

// TODO: temporary hack until we fix static init + threads problems properly
${cppTemplateDeclaration!}
void ${objcSupportNamespace}::${name}StructMarshaller${cppTemplateParameters!}::init(void) const
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
const ${objcSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}> & ${objcSupportNamespace}::${name}StructMarshaller${cppTemplateParameters!}::get${type.name?cap_first}Marshaller(void) const
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