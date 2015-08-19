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

import com.thomsonreuters.corptech.codegen.defs.types.EnumTypeConfig;
import com.thomsonreuters.corptech.codegen.defs.types.TypeConfig;
import lombok.Getter;
import lombok.Setter;

import javax.validation.Valid;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Set;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class EnumDef extends TopLevelDef
{
	@XmlElement(name = "value")
	@Valid
    private List<EnumValueDef> values = new ArrayList<>();

    @Override
    public String getCppDeclarationType()
    {
        return "enum class";
    }

    @Override
    public String getObjcDeclarationType()
    {
        return "typedef int ";
    }

	public String getJniSignature()
	{
		return "L" + resolveVariable("javaPackage").replace(".", "/") + "/" + getJavaClassname() + ";";
	}

    @Override
    public Set<TopLevelDef> getDependencies()
    {
        return Collections.emptySet();
    }

    @Override
    public Set<TopLevelDef> getForwardDependencies()
    {
        return Collections.emptySet();
    }

	public TypeConfig createTypeConfig(final TypeConfig... templateArgs)
	{
		assert(templateArgs.length == 0);
		return new EnumTypeConfig(this);
	}
}
