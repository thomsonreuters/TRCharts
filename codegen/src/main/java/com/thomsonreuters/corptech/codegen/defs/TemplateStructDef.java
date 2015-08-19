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

import com.thomsonreuters.corptech.codegen.defs.types.TemplateStructTypeConfig;
import com.thomsonreuters.corptech.codegen.defs.types.TypeConfig;
import lombok.Getter;
import lombok.Setter;
import org.apache.commons.lang.StringUtils;

import javax.validation.Valid;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class TemplateStructDef extends StructDef
{
	@XmlElement(name = "templateParameter")
	@Valid
	private final List<TemplateParameterDef> templateParameters = new ArrayList<>();

	@Override
	public boolean isBound()
	{
		return false;
	}

	@Override
	public String getCppDeclarationName()
	{
		return super.getCppDeclarationName() + getCppTemplateParameters();
	}

	@Override
	public String getCppDeclarationType()
	{
		return getCppTemplateDeclaration() + " " + super.getCppDeclarationType();
	}

	public TypeConfig createTypeConfig(final String name, final TypeConfig ... templateArgs)
	{
		for(final TemplateParameterDef templateParameterDef : templateParameters) {
			if(name.equals(templateParameterDef.getName())) {
				return templateParameterDef.createTypeConfig(templateArgs);
			}
		}
		return super.createTypeConfig(name, templateArgs);
	}

	public TypeConfig createTypeConfig(final TypeConfig... templateArgs)
	{
		if(templateArgs.length != templateParameters.size()) {
			throw new IllegalStateException("Expected " + templateParameters.size() + " template argument(s)");
		}
		return new TemplateStructTypeConfig(this, templateArgs);
	}

	public String getCppTemplateDeclaration()
	{
		final List<String> args = new ArrayList<>();
		for(final TemplateParameterDef templateParameterDef : templateParameters) {
			args.add("typename " + templateParameterDef.getName());
		}
		return "template <" + StringUtils.join(args, ", ") + ">";
	}

	public String getCppTemplateParameters()
	{
		final List<String> args = new ArrayList<>();
		for(final TemplateParameterDef templateParameterDef : templateParameters) {
			args.add(templateParameterDef.getName());
		}
		return "<" + StringUtils.join(args, ", ") + ">";
	}

	@Override
	public String getObjcMarshallerIncludeFile()
	{
		return resolveVariable("objcFilePrefix") + "Support/" + getName() + "StructMarshaller.hh";
	}
}
