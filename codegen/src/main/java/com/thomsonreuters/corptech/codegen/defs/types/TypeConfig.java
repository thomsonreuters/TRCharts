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

import com.thomsonreuters.corptech.codegen.defs.TopLevelDef;

import java.util.Collections;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

public abstract class TypeConfig
{
	public abstract String getBasicType();

	public abstract String getName();

	public abstract String getJavaType();

	public abstract String getJavaContainerType();

	public abstract String getJavaJniType();

	public abstract String getJavaJniContainerType();

	public abstract boolean isJavaPrimitive();

	public abstract String getCppJniType();

	public abstract String getCppJniArrayType();

	public abstract String getCppRawType();

	public abstract String getCppValueType();

	public abstract String getCppConstReferenceType();

	public abstract String getCppDefaultValue();

	public abstract String getObjcValueType();

	public abstract String getObjcRawType();

	public abstract String getObjcValue(final String spec);

	public abstract String getObjcMarshallType();

	public abstract boolean isObjcPrimitive();

	public abstract String getObjcFormatPlaceholder();

	public abstract String getJniMarshaller();

	public abstract String getJavaMarshaller();

	public abstract String getObjcMarshaller();

	public abstract TypeConfig getHintType();

	public abstract boolean isReturnable();

	public abstract boolean isBound();

	public boolean isTemplateParameter()
	{
		return false;
	}

	public abstract Set<TopLevelDef> getSuperDependencies();

	public abstract Set<TopLevelDef> getDependencies();

	public abstract Set<TopLevelDef> getForwardDependencies();

	public TypeConfig bind(final Map<String, TypeConfig> args)
	{
		return this;
	}

	public Set<TypeConfig> getReferencedTypes()
	{
		return Collections.singleton(this);
	}

	public abstract String getJniSignature();

	@Override
	public boolean equals(final Object other)
	{
		if(other instanceof TypeConfig) {
			return Objects.equals(getName(), ((TypeConfig) other).getName());
		} else {
			return false;
		}
	}

	public String getGetterPrefix()
	{
		return "get";
	}

	@Override
	public int hashCode()
	{
		return Objects.hashCode(getName());
	}
}
