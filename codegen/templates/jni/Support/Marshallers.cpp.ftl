[#ftl]
${copyright}
${autogenNote}

#include <${jniCppFilePrefix}Support/Marshallers.hpp>

#include <${jniCppFilePrefix}Support/BooleanMarshaller.hpp>
#include <${jniCppFilePrefix}Support/IntegerMarshaller.hpp>
#include <${jniCppFilePrefix}Support/ListMarshaller.hpp>
#include <${jniCppFilePrefix}Support/NumberMarshaller.hpp>
#include <${jniCppFilePrefix}Support/ObjectMarshaller.hpp>
#include <${jniCppFilePrefix}Support/StringMarshaller.hpp>

[#list interfaces as interface]
#include <${jniCppFilePrefix}Support/${interface.name}InterfaceMarshaller.hpp>
[/#list]
[#list templateInterfaces as interface]
#include <${jniCppFilePrefix}Support/${interface.name}InterfaceMarshaller.hpp>
[/#list]
[#list structs as struct]
#include <${jniCppFilePrefix}Support/${struct.name}StructMarshaller.hpp>
[/#list]
[#list enums as enum]
#include <${jniCppFilePrefix}Support/${enum.name}EnumMarshaller.hpp>
[/#list]

[#list referencedTypeForwardDependencies as dependency]
#include <${cppPublicFilePrefix}${dependency.name}.hpp>
[/#list]

using namespace ${jniCppNamespace};

namespace
{
	[#list referencedTypes as type]
	[#if type.returnable && type.bound]
	std::shared_ptr<Marshaller<${type.cppValueType}, ${type.cppJniType}>> cached${type.name}Marshaller;
	[/#if]
	[/#list]
}

[#list referencedTypes as type]
[#if type.returnable && type.bound]
const Marshaller<${type.cppValueType}, ${type.cppJniType}> & ${jniCppNamespace}::get${type.name?cap_first}Marshaller(void)
{
	if(!::cached${type.name}Marshaller) {
		::cached${type.name}Marshaller.reset(new ${type.jniMarshaller});
	}
	return *::cached${type.name}Marshaller;
}

[/#if]
[/#list]