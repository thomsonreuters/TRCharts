[#ftl]
[#include "/templates/cpp/_macros.ftl"]
${copyright}
${autogenNote}

#include <${cppPublicFilePrefix}${name}.hpp>
#include <${cppPublicFilePrefix}${name}.hpp>

[#if fields?has_content]
${cppTemplateDeclaration!}
${cppNamespace}::Generated${cppClassname}::Generated${cppClassname}(void)
	:[#if extend??]${extend.cppRawType}(), [/#if][#list fields as field]${field.name}(${field.cppDefaultValue})[#if field_has_next], [/#if][/#list]
{
}

${cppTemplateDeclaration!}
${cppNamespace}::Generated${cppClassname}::Generated${cppClassname}([#list allFields as field]${field.type.cppConstReferenceType} ${field.name}[#if field_has_next], [/#if][/#list])
	:[#if inheritedFields?has_content]${extend.cppRawType}([#list inheritedFields as field]${field.name}[#if field_has_next], [/#if][/#list]), [/#if][#list fields as field]${field.name}(${field.name})[#if field_has_next], [/#if][/#list]
{
}

[/#if]
${cppTemplateDeclaration!}
bool ${cppNamespace}::Generated${cppClassname}::operator==(const Generated${cppClassname} & other) const
{
	bool result = true;
	[#list fields as field]
	result = result && (this->${field.name} == other.${field.name});
	[/#list]
	return result;
}

${cppTemplateDeclaration!}
bool ${cppNamespace}::Generated${cppClassname}::operator!=(const Generated${cppClassname} & other) const
{
	return !(*this == other);
}

${cppTemplateDeclaration!}
std::ostream & ${cppNamespace}::operator<<(std::ostream & to, const Generated${cppClassname} & from)
{
	to << "${cppClassname}[";
	[#if extend??]
	const ${extend.cppRawType} & super = from;
	to << super << ", ";
	[/#if]
	[#list fields as field]
	to << "${field.name}: " << from.${field.name}[#if field_has_next] << ", "[/#if];
	[/#list]
	to << "]";
	return to;
}