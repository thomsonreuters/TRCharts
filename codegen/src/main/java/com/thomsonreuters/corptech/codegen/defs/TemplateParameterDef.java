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

import com.thomsonreuters.corptech.codegen.defs.types.TemplateParameterTypeConfig;
import com.thomsonreuters.corptech.codegen.defs.types.TypeConfig;
import lombok.Getter;
import lombok.Setter;

import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class TemplateParameterDef extends DefBase
{
	@XmlAttribute(name = "name")
	@NotNull
	private String name;

	@XmlAttribute(name = "object")
	private boolean object;

	public TypeConfig getTypeConfig()
	{
		return new TemplateParameterTypeConfig(this);
	}

	public TypeConfig createTypeConfig(final TypeConfig... templateArgs)
	{
		assert(templateArgs.length == 0);
		return getTypeConfig();
	}
}
