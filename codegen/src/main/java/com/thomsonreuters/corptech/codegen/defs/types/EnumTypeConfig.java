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

import com.thomsonreuters.corptech.codegen.defs.EnumDef;
import com.thomsonreuters.corptech.codegen.defs.EnumValueDef;
import com.thomsonreuters.corptech.codegen.defs.TopLevelDef;
import lombok.Getter;

import javax.annotation.Nonnull;
import java.util.Collections;
import java.util.Set;

public class EnumTypeConfig extends TypeConfig
{
	@Getter
	@Nonnull
	private final EnumDef enumDef;

	public EnumTypeConfig(@Nonnull final EnumDef enumDef)
	{
		this.enumDef = enumDef;
	}

	@Override
	public String getBasicType()
	{
		return "Enum";
	}

	@Override
	public String getName()
	{
		return enumDef.getName();
	}

	@Override
	public String getJavaType()
	{
		return enumDef.getJavaClassname();
	}

	@Override
	public String getJavaContainerType()
	{
		return getJavaType();
	}

	@Override
	public String getJavaJniType()
	{
		return "Object"; //"int";
	}

	@Override
	public String getJavaJniContainerType()
	{
		return getJavaJniType();
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
		return enumDef.getCppNamespacedClassname();
	}

	@Override
	public String getCppValueType()
	{
		return getCppRawType();
	}

	@Override
	public String getCppConstReferenceType()
	{
		return getCppValueType();
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
		return enumDef.getObjcClassname();
	}

	@Override
	public String getObjcValue(final String spec)
	{
		if(spec != null) {
			final String value = spec.trim();
			for(final EnumValueDef valueDef : enumDef.getValues()) {
				if(valueDef.getName().equals(value)) {
					return valueDef.getObjcRepresentation();
				}
			}
		} else if(!enumDef.getValues().isEmpty()){
			return enumDef.getValues().get(0).getObjcRepresentation();
		}
		throw new IllegalStateException();
	}

	@Override
	public String getObjcMarshallType()
	{
		return getObjcValueType();
	}

	@Override
	public boolean isObjcPrimitive()
	{
		return true;
	}

	@Override
	public String getObjcFormatPlaceholder()
	{
		return "zd";
	}

	@Override
	public String getJniMarshaller()
	{
		return enumDef.getName() + "EnumMarshaller()";
	}

	@Override
	public String getJavaMarshaller()
	{
		return "EnumMarshaller<" + getJavaType() + ">(" + getJavaType() + ".class)";
	}

	@Override
	public String getObjcMarshaller()
	{
		return "CodegenSupportObjc::EnumMarshaller<" + getCppRawType() + ", " + getObjcValueType() + ">()";
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
		return true;
	}

	@Override
	public Set<TopLevelDef> getSuperDependencies()
	{
		return Collections.emptySet();
	}

	@Override
	public Set<TopLevelDef> getDependencies()
	{
		return Collections.<TopLevelDef>singleton(enumDef);
	}

	@Override
	public Set<TopLevelDef> getForwardDependencies()
	{
		return Collections.emptySet();
	}

	@Override
	public String getJniSignature()
	{
		return enumDef.getJniSignature();
	}
}
