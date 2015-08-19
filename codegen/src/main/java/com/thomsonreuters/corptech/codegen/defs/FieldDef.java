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

import com.thomsonreuters.corptech.codegen.defs.types.TypeConfig;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;

import javax.validation.constraints.AssertTrue;
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlTransient;
import java.util.Map;
import java.util.Set;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class FieldDef extends DefBase
{
	@XmlAttribute(name = "name")
	@NotNull
	private String name;

	@XmlAttribute(name = "description")
	private String description;

	@XmlAttribute(name = "instance")
	private boolean instance = true;

	@XmlAttribute(name = "concrete")
	private boolean concrete = true;

	@XmlAttribute(name = "readonly")
	private boolean readonly;

	@XmlAttribute(name = "type")
	@NotNull
	private String typeName;

	@XmlTransient
	@Setter(AccessLevel.PRIVATE)
	private TypeConfig type;

	@XmlAttribute(name = "returnReference")
	private boolean returnReference = true;

	@XmlAttribute(name = "defaultValue")
	private String defaultValue;

	@Override
	public void init()
	{
		type = resolveType(typeName);
	}

	public FieldDef bind(final Map<String, TypeConfig> args)
	{
		final FieldDef result = new FieldDef();
		result.name = name;
		result.concrete = concrete;
		result.readonly = readonly;
		result.type = type.bind(args);
		result.description = description;
		result.getComments().addAll(getComments());
		return result;
	}

	public boolean isBound()
	{
		return type.isBound();
	}

	public Set<TypeConfig> getReferencedTypes()
	{
		return type.getReferencedTypes();
	}

	public String getCppDefaultValue()
	{
		if(defaultValue != null) {
			return defaultValue;
		} else {
			return type.getCppDefaultValue();
		}
	}

	public String getObjcDefaultValue()
	{
		return type.getObjcValue(defaultValue);
	}

	public String getObjcPropertyFlags()
	{
		return readonly ? "readonly" : "";
	}

	public Set<TopLevelDef> getDependencies()
	{
		return type.getDependencies();
	}

	public Set<TopLevelDef> getForwardDependencies()
	{
		return type.getForwardDependencies();
	}

	@AssertTrue(message = "Unbound method must not be concrete")
	public boolean validateBoundState()
	{
		return !isConcrete() || isBound();
	}
}
