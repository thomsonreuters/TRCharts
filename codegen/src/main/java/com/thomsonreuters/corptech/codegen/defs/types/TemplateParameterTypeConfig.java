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

package com.thomsonreuters.corptech.codegen.defs.types;

import com.thomsonreuters.corptech.codegen.defs.TemplateParameterDef;
import com.thomsonreuters.corptech.codegen.defs.TopLevelDef;
import lombok.Getter;

import javax.annotation.Nonnull;
import java.util.Collections;
import java.util.Map;
import java.util.Set;

public class TemplateParameterTypeConfig extends TypeConfig
{
	@Getter
	@Nonnull
	private TemplateParameterDef templateParameterDef;

	public TemplateParameterTypeConfig(@Nonnull final TemplateParameterDef templateParameterDef)
	{
		this.templateParameterDef = templateParameterDef;
	}

	@Override
	public String getBasicType()
	{
		return "TemplateParameter";
	}

	@Override
	public String getName()
	{
		return templateParameterDef.getName();
	}

	@Override
	public String getJavaType()
	{
		return templateParameterDef.getName();
	}

	@Override
	public String getJavaContainerType()
	{
		return getJavaType();
	}

	@Override
	public String getJavaJniType()
	{
		return "Object";
	}

	@Override
	public String getJavaJniContainerType()
	{
		return "Object";
	}

	@Override
	public boolean isJavaPrimitive() { return false; }

	@Override
	public String getCppJniType()
	{
		return "jobject";
	}

	@Override
	public String getCppJniArrayType()
	{
		return "jobjectArray";
	}

	@Override
	public String getCppRawType()
	{
		return templateParameterDef.getName();
	}

	@Override
	public String getCppValueType()
	{
		return templateParameterDef.isObject() ? "std::shared_ptr<" + getCppRawType() + ">" : getCppRawType();
	}

	@Override
	public String getCppConstReferenceType()
	{
		return "const " + getCppValueType() + " &";
	}

	@Override
	public String getCppDefaultValue()
	{
		return getCppValueType() + "()";
	}

	@Override
	public String getObjcValueType()
	{
		return getObjcRawType();
	}

	@Override
	public String getObjcRawType()
	{
		return "id";
	}

	@Override
	public String getObjcValue(final String spec)
	{
		return "nil";
	}

	@Override
	public String getObjcMarshallType()
	{
		return getObjcValueType();
	}

	@Override
	public boolean isObjcPrimitive()
	{
		return false;
	}

	@Override
	public String getObjcFormatPlaceholder()
	{
		return "@";
	}

	@Override
	public String getJniMarshaller()
	{
		throw new IllegalArgumentException();
	}

	@Override
	public String getJavaMarshaller()
	{
		throw new IllegalArgumentException();
	}

	@Override
	public String getObjcMarshaller()
	{
		throw new IllegalArgumentException();
	}

	@Override
	public TypeConfig getHintType()
	{
		return this;
	}

	@Override
	public boolean isReturnable()
	{
		return true;
	}

	@Override
	public boolean isBound()
	{
		return false;
	}

	@Override
	public boolean isTemplateParameter()
	{
		return true;
	}

	public TypeConfig bind(final Map<String, TypeConfig> args)
	{
		final TypeConfig tmp = args.get(templateParameterDef.getName());
		return tmp != null ? tmp : this;
	}

	@Override
	public Set<TopLevelDef> getSuperDependencies()
	{
		return Collections.emptySet();
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

	@Override
	public String getJniSignature()
	{
		return "Ljava/lang/Object;";
	}
}
