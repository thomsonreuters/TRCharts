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

import com.thomsonreuters.corptech.codegen.defs.types.InterfaceTypeConfig;
import com.thomsonreuters.corptech.codegen.defs.types.TypeConfig;
import lombok.Getter;
import lombok.Setter;

import javax.validation.Valid;
import javax.xml.bind.annotation.*;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class InterfaceDef extends TopLevelDef
{
	@XmlAttribute(name = "extend")
	private String extendNames;

	@XmlTransient
	private final List<TypeConfig> extend = new ArrayList<>();

	@XmlElement(name = "method")
	@Valid
	private final List<MethodDef> methods = new ArrayList<>();

	@Override
	public void init()
	{
		extend.addAll(resolveTypes(extendNames));
		initDefs(methods);
	}

	public Set<TypeConfig> getReferencedTypes()
	{
		final Set<TypeConfig> out = new LinkedHashSet<>();
		for(final MethodDef methodDef : methods) {
			out.addAll(methodDef.getReferencedTypes());
		}
		return out;
	}

	public String getJniSignature()
	{
		return "L" + resolveVariable("javaPackage").replace(".", "/") + "/" + getJavaClassname() + ";";
	}

	@Override
	public String getCppDeclarationType()
	{
		return "class";
	}

	@Override
	public String getObjcDeclarationType()
	{
		return "@protocol";
	}

	@Override
	public Set<TopLevelDef> getDependencies()
	{
		final Set<TopLevelDef> out = new LinkedHashSet<>();
		for(final TypeConfig extendEntry : extend) {
			out.addAll(extendEntry.getSuperDependencies());
		}
		for(final MethodDef methodDef : methods) {
			out.addAll(methodDef.getDependencies());
		}
		return out;
	}

	@Override
	public Set<TopLevelDef> getForwardDependencies()
	{
		final Set<TopLevelDef> out = new LinkedHashSet<>();
		for(final MethodDef methodDef : methods) {
			out.addAll(methodDef.getForwardDependencies());
		}
		return out;
	}

	public TypeConfig createTypeConfig(final TypeConfig... templateArgs)
	{
		assert(templateArgs.length == 0);
		return new InterfaceTypeConfig(this);
	}

	@Override
	public String getObjcMarshallerIncludeFile()
	{
		return resolveVariable("objcFilePrefix") + "Support/" + getName() + "InterfaceMarshaller.hh";
	}
}
