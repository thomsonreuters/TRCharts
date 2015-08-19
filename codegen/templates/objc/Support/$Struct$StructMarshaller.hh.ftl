[#ftl]
${copyright}
${autogenNote}

#import <${objcCodegenSupportFilePrefix}Marshaller.hh>
#import <${objcFilePrefix}${name}.h>
#import <${cppPublicFilePrefix}${name}.hpp>

namespace ${objcSupportNamespace}
{
	${cppTemplateDeclaration!}
	class ${name}StructMarshaller : public ${objcCodegenSupportNamespace}::Marshaller<${cppDeclarationName}, id>
	{
	public:
		[#if templateParameters??]
		${name}StructMarshaller([#list templateParameters! as param]const Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.objcMarshallType}> & marshaller${param.name?cap_first}[#if param_has_next], [/#if][/#list]);

		[/#if]
		virtual ${cppDeclarationName} marshall(const ${objcCodegenSupportNamespace}::StrongAnyPtr & in) const;

		virtual ${objcCodegenSupportNamespace}::StrongAnyPtr unmarshall(const ${cppDeclarationName} & in) const;

		virtual ${cppDeclarationName} marshallBoxed(const id & in) const;

		virtual id unmarshallBoxed(const ${cppDeclarationName} & in) const;

		virtual void init(void) const;
		[#list referencedTypes as type]
		[#if type.returnable && !type.bound]
		const Marshaller<${type.cppValueType}, ${type.objcMarshallType}> & get${type.name}Marshaller(void) const;

		[/#if]
		[/#list]
	private:
		[#list templateParameters! as param]
		const Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.objcMarshallType}> & marshaller${param.name?cap_first};
		[/#list]
		[#list referencedTypes as type]
		[#if type.returnable && !type.bound && !type.templateParameter]
		mutable std::shared_ptr<Marshaller<${type.cppValueType}, ${type.objcMarshallType}>> cached${type.name}Marshaller;
		[/#if]
		[/#list]
	};
}
