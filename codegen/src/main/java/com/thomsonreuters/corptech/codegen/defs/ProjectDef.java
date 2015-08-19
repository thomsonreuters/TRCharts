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

package com.thomsonreuters.corptech.codegen.defs;

import com.thomsonreuters.corptech.codegen.XMLUtils;
import com.thomsonreuters.corptech.codegen.defs.types.*;
import lombok.Getter;
import lombok.Setter;

import javax.annotation.Nonnull;
import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import javax.xml.bind.JAXBException;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.*;

@Getter
@Setter
@XmlRootElement(name = "project")
public class ProjectDef extends DefBase
{
	@XmlAttribute(name = "name")
	@NotNull
	private String name;

	@XmlElement(name = "dependency")
	@Valid
	private final List<DependencyDef> dependencies = new ArrayList<>();

	@XmlElement(name = "variable")
	@Valid
	private final List<VariableDef> variables = new ArrayList<>();

	@XmlElement(name = "output")
	@Valid
	private final List<OutputDef> outputs = new ArrayList<>();

	@XmlElement(name = "enum")
	@Valid
	private final List<EnumDef> enums = new ArrayList<>();

	@XmlElement(name = "struct")
	@Valid
	private final List<StructDef> structs = new ArrayList<>();

	@XmlElement(name = "interface")
	@Valid
	private final List<InterfaceDef> interfaces = new ArrayList<>();

	@XmlElement(name = "class")
	@Valid
	private final List<ClassDef> classes = new ArrayList<>();

	@XmlElement(name = "templateInterface")
	@Valid
	private final List<TemplateInterfaceDef> templateInterfaces = new ArrayList<>();

	@XmlElement(name = "templateClass")
	@Valid
	private final List<TemplateClassDef> templateClasses = new ArrayList<>();

	@XmlElement(name = "templateStruct")
	@Valid
	private final List<TemplateStructDef> templateStructs = new ArrayList<>();

	@XmlElement(name = "field")
	@Valid
	private final List<FieldDef> fields = new ArrayList<>();

	@XmlElement(name = "method")
	@Valid
	private final List<MethodDef> methods = new ArrayList<>();

	@Override
	@Nonnull
	public DefBase resolveNamespace(@Nonnull final String name)
	{
		for(final DependencyDef dependencyDef : dependencies) {
			if(name.equals(dependencyDef.getProject().getName())) {
				return dependencyDef.getProject();
			}
		}
		return super.resolveNamespace(name);
	}

	@Override
	public TypeConfig createTypeConfig(final String name, final TypeConfig ... templateArgs)
	{
		switch (name) {
			case "Void": return VOID_TYPE;
			case "Boolean": return BOOLEAN_TYPE;
			case "Integer": return INTEGER_TYPE;
			case "Number": return NUMBER_TYPE;
			case "String": return STRING_TYPE;
			case "List":
				assert(templateArgs.length == 1);
				return new ListTypeConfig(templateArgs[0]);
		}
		for(final EnumDef enumDef : enums) {
			if(name.equals(enumDef.getName())) {
				return enumDef.createTypeConfig(templateArgs);
			}
		}
		for(final ClassDef classDef : classes) {
			if(name.equals(classDef.getName())) {
				return classDef.createTypeConfig(templateArgs);
			}
		}
		for(final StructDef structDef : structs) {
			if(name.equals(structDef.getName())) {
				return structDef.createTypeConfig(templateArgs);
			}
		}
		for(final InterfaceDef interfaceDef : interfaces) {
			if(name.equals(interfaceDef.getName())) {
				return interfaceDef.createTypeConfig(templateArgs);
			}
		}
		for(final TemplateClassDef classDef : templateClasses) {
			if(name.equals(classDef.getName())) {
				return classDef.createTypeConfig(templateArgs);
			}
		}
		for(final TemplateInterfaceDef interfaceDef : templateInterfaces) {
			if(name.equals(interfaceDef.getName())) {
				return interfaceDef.createTypeConfig(templateArgs);
			}
		}
		for(final TemplateStructDef structDef : templateStructs) {
			if(name.equals(structDef.getName())) {
				return structDef.createTypeConfig(templateArgs);
			}
		}
		return super.createTypeConfig(name, templateArgs);
	}

	@Override
	public void init()
	{
		initDefs(dependencies);
		//initDefs(types);
		initDefs(enums);
		initDefs(classes);
		initDefs(structs);
		initDefs(interfaces);
		initDefs(templateClasses);
		initDefs(templateInterfaces);
		initDefs(templateStructs);
		initDefs(fields);
		initDefs(methods);
		for(final ClassDef classDef : classes) {
			classDef.postInit();
		}
	}

	public Set<TypeConfig> getReferencedTypes()
	{
		final Set<TypeConfig> out = new LinkedHashSet<>();
		for(final ClassDef classDef : classes) {
			out.addAll(classDef.getReferencedTypes());
		}
		for(final StructDef structDef : structs) {
			out.addAll(structDef.getReferencedTypes());
		}
		for(final InterfaceDef interfaceDef : interfaces) {
			out.addAll(interfaceDef.getReferencedTypes());
		}
		for(final TemplateClassDef classDef : templateClasses) {
			out.addAll(classDef.getReferencedTypes());
		}
		for(final TemplateInterfaceDef interfaceDef : templateInterfaces) {
			out.addAll(interfaceDef.getReferencedTypes());
		}
		for(final TemplateStructDef structDef : templateStructs) {
			out.addAll(structDef.getReferencedTypes());
		}
		for(final FieldDef fieldDef : fields) {
			out.addAll(fieldDef.getReferencedTypes());
		}
		for(final MethodDef methodDef : methods) {
			out.addAll(methodDef.getReferencedTypes());
		}
		return out;
	}

	public Set<TopLevelDef> getReferencedTypeDependencies()
	{
		final Set<TopLevelDef> result = new LinkedHashSet<>();
		for(final TypeConfig type : getReferencedTypes()) {
			result.addAll(type.getDependencies());
		}
		return result;
	}

	public Set<TopLevelDef> getReferencedTypeForwardDependencies()
	{
		final Set<TopLevelDef> result = new LinkedHashSet<>();
		for(final TypeConfig type : getReferencedTypes()) {
			result.addAll(type.getForwardDependencies());
		}
		return result;
	}

	@Override
	public String resolveVariable(final String name)
	{
		for(final VariableDef variableDef : variables) {
			if (name.equals(variableDef.getName())) {
				return variableDef.getValue();
			}
		}
		return super.resolveVariable(name);
	}

	@Override
	public Map<String, String> resolveVariables()
	{
		final Map<String, String> result = new HashMap<>();
		for(final VariableDef variableDef : variables) {
			result.put(variableDef.getName(), variableDef.getValue());
		}
		return result;
	}

	public static final VoidTypeConfig VOID_TYPE = new VoidTypeConfig();
	public static final BooleanTypeConfig BOOLEAN_TYPE = new BooleanTypeConfig();
	public static final IntegerTypeConfig INTEGER_TYPE = new IntegerTypeConfig();
	public static final NumberTypeConfig NUMBER_TYPE = new NumberTypeConfig();
	public static final StringTypeConfig STRING_TYPE = new StringTypeConfig();

	@Nonnull
	public static ProjectDef load(final String path) throws IOException, JAXBException
	{
		final FileInputStream inputStream = new FileInputStream(path);
		final ProjectDef project = load(inputStream);
		inputStream.close();
		return project;
	}

	@Nonnull
	public static ProjectDef load(final InputStream inputStream) throws JAXBException
	{
		final ProjectDef project = XMLUtils.unmarshall(ProjectDef.class, inputStream);
		XMLUtils.validate(project);
		project.init();
		return project;
	}
}
