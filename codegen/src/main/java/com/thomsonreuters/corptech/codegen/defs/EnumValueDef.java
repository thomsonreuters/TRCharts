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

import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class EnumValueDef extends DefBase
{
	@XmlAttribute(name = "name")
	@NotNull
	private String name;

	@Override
	public void init()
	{
	}

	public String getCppRepresentation()
	{
		final EnumDef enumDef = (EnumDef)getParent();
		return Character.toUpperCase(name.charAt(0)) + name.substring(1);
	}

	public String getObjcRepresentation()
	{
		final EnumDef enumDef = (EnumDef)getParent();
		return (enumDef.resolveVariable("objcClassPrefix") + "_" + enumDef.getName() + "_" + name).toUpperCase();
	}

	public String getJavaRepresentation()
	{
		final EnumDef enumDef = (EnumDef)getParent();
		return name.toUpperCase();
	}
}
