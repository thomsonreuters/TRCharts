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
import java.util.Set;

public class IntegerTypeConfig extends TypeConfig
{
	@Override
	public String getBasicType()
	{
		return "Integer";
	}

	@Override
	public String getName()
	{
		return "Integer";
	}

	@Override
	public String getJavaType()
	{
		return "long";
	}

	@Override
	public String getJavaContainerType()
	{
		return "Long";
	}

	@Override
	public String getJavaJniType()
	{
		return getJavaType();
	}

	@Override
	public String getJavaJniContainerType()
	{
		return getJavaContainerType();
	}

	@Override
	public boolean isJavaPrimitive() { return true; }

	@Override
	public String getCppJniType()
	{
		return "jlong";
	}

	@Override
	public String getCppRawType()
	{
		return "long";
	}

	@Override
	public String getCppJniArrayType()
	{
		return "jlongArray";
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
		return "0L";
	}

	@Override
	public String getObjcValueType()
	{
		return getObjcRawType();
	}

	@Override
	public String getObjcRawType()
	{
		return "long";
	}

	@Override
	public String getObjcValue(final String spec)
	{
		if(spec != null) {
			final long value = Long.parseLong(spec);
			return value + "L";
		} else {
			return "0L";
		}
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
		return "ld";
	}

	@Override
	public String getJniMarshaller()
	{
		return "IntegerMarshaller()";
	}

	@Override
	public String getJavaMarshaller()
	{
		return "IntegerMarshaller()";
	}

	@Override
	public String getObjcMarshaller()
	{
		return "CodegenSupportObjc::IntegerMarshaller()";
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
		return "J";
	}
}
