[#ftl]
${copyright}
${autogenNote}

#import <${objcCodegenSupportFilePrefix}Marshaller.hh>
#import <${objcFilePrefix}${name}.h>
#import <${cppPublicFilePrefix}${name}.hpp>

namespace ${objcSupportNamespace}
{
	${cppTemplateDeclaration!}
	class ${name}InterfaceMarshaller : public ${objcCodegenSupportNamespace}::Marshaller<std::shared_ptr<${cppDeclarationName}>, id>
	{
	public:
		[#if templateParameters??]
		${name}InterfaceMarshaller([#list templateParameters! as param]const ${objcCodegenSupportNamespace}::Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.objcMarshallType}> & marshaller${param.name?cap_first}[#if param_has_next], [/#if][/#list]);

		[/#if]
		virtual std::shared_ptr<${cppDeclarationName}> marshall(const ${objcCodegenSupportNamespace}::StrongAnyPtr & in) const;

		virtual ${objcCodegenSupportNamespace}::StrongAnyPtr unmarshall(const std::shared_ptr<${cppDeclarationName}> & in) const;

		virtual std::shared_ptr<${cppDeclarationName}> marshallBoxed(const id & in) const;

		virtual id unmarshallBoxed(const std::shared_ptr<${cppDeclarationName}> & in) const;

		virtual void init(void) const;

		[#list referencedTypes as type]
		[#if type.returnable && !type.bound]
		const ${objcCodegenSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}> & get${type.name}Marshaller(void) const;

		[/#if]
		[/#list]
	private:
		[#list templateParameters! as param]
		const ${objcCodegenSupportNamespace}::Marshaller<${param.typeConfig.cppValueType}, ${param.typeConfig.objcMarshallType}> & marshaller${param.name?cap_first};
		[/#list]
		[#list referencedTypes as type]
		[#if type.returnable && !type.bound && !type.templateParameter]
		mutable std::shared_ptr<${objcCodegenSupportNamespace}::Marshaller<${type.cppValueType}, ${type.objcMarshallType}>> cached${type.name}Marshaller;
		[/#if]
		[/#list]

		class Proxy;
	};
}
