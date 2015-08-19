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
public class ParameterDef extends DefBase
{
	@XmlAttribute(name = "name")
	@NotNull
	private String name;

	@XmlAttribute(name = "type")
	@NotNull
	private String typeName;

	@XmlTransient
	@Setter(AccessLevel.PRIVATE)
	private TypeConfig type;

	@Override
	public void init()
	{
		type = resolveType(typeName);
	}

	public ParameterDef bind(final Map<String, TypeConfig> args)
	{
		final ParameterDef result = new ParameterDef();
		result.name = name;
		result.type = type.bind(args);
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

	public Set<TopLevelDef> getDependencies()
	{
		return type.getDependencies();
	}

	public Set<TopLevelDef> getForwardDependencies()
	{
		return type.getForwardDependencies();
	}
}
