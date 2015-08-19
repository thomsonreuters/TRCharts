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

import lombok.Getter;
import lombok.Setter;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public abstract class TopLevelDef extends DefBase
{
	@XmlAttribute(name = "name")
	@NotNull
	private String name;

	@XmlElement(name = "type")
	@Valid
	private final List<TypeDef> types = new ArrayList<>();

	public String getCppClassname()
	{
		return name;
	}

	public String getCppNamespacedClassname()
	{
		return resolveVariable("cppNamespace") + "::" + getCppClassname();
	}

	public String getCppDeclarationName()
	{
		return getCppNamespacedClassname();
	}

	public String getJavaClassname()
	{
		return name;
	}

	public String getObjcClassname()
	{
		return resolveVariable("objcClassPrefix") + name;
	}

	public abstract String getCppDeclarationType();

	public abstract String getObjcDeclarationType();

	public abstract Set<TopLevelDef> getDependencies();

	public abstract Set<TopLevelDef> getForwardDependencies();

	public String getCppIncludeFile()
	{
		return resolveVariable("cppPublicFilePrefix") + name + ".hpp";
	}

	public String getObjcIncludeFile()
	{
		return resolveVariable("objcFilePrefix") + name + ".h";
	}

	public String getObjcMarshallerIncludeFile()
	{
		return null;
	}
}
