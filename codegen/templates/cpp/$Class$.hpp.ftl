[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#ifndef ${cppHeaderGuardPrefix}${name}_hpp
#define ${cppHeaderGuardPrefix}${name}_hpp

#include <${cppPublicFilePrefix}Common.hpp>
[#if !extend?exists]
#include <${cppCodegenSupportFilePrefix}BaseObject.hpp>
[/#if]
[#list dependencies as dependency]
#include <${dependency.cppIncludeFile}>
[/#list]

namespace ${cppNamespace}
{
	${cppTemplateDeclaration!}
	class ${cppClassname};
	[#list forwardDependencies as dependency]
	${dependency.cppDeclarationType} ${dependency.cppClassname};
	[/#list]

	[#if !bound]
	/* Non-generic interface for ${cppClassname} */
	class I${cppClassname}
	{
	public:
		virtual ~I${cppClassname}(void);

		[#list fields as field]
		[#if field.bound]
		${""}[@cpp_getter_declaration_signature field/] = 0;

		[#if !field.readonly]
		${""}[@cpp_setter_declaration_signature field/] = 0;

		[/#if]
		[/#if]
		[/#list]
		[#list methods as method]
		[#if method.bound]
		${""}[@cpp_method_declaration_signature method/] = 0;

		[/#if]
		[/#list]
	};

	inline I${cppClassname}::~I${cppClassname}(void)
	{
	}

	[/#if]
	${cppTemplateDeclaration!}
	class Generated${cppClassname} : public [#if extend?exists]${extend.cppRawType}[#else]${cppCodegenSupportNamespace}::BaseObject[/#if][#if !bound], public I${cppClassname}[/#if][#list implement as i], public ${i.cppRawType}[/#list]
	{
	public:
		virtual ~Generated${cppClassname}(void);

		std::shared_ptr<${cppClassname}${cppTemplateParameters!}> getSharedPtr(void);

		std::shared_ptr<const ${cppClassname}${cppTemplateParameters!}> getSharedPtr(void) const;

		[#list fields as field]
		${""}[@cpp_getter_declaration_signature field/] = 0;

		[#if !field.readonly]
		${""}[@cpp_setter_declaration_signature field/] = 0;

		[/#if]
		[/#list]
		[#list methods as method]
		${""}[@cpp_method_declaration_signature method/] = 0;

		[/#list]
	protected:
		Generated${cppClassname}(void);

	};
}

#include <${cppPublicFilePrefix}Impl/${cppClassname}Impl.hpp>

#endif