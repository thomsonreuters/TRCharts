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

public class VoidTypeConfig extends TypeConfig
{
	@Override
	public String getBasicType()
	{
		return "Void";
	}

	@Override
	public String getName()
	{
		return "Void";
	}

	@Override
	public String getJavaType()
	{
		return "void";
	}

	@Override
	public String getJavaContainerType()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getJavaJniType()
	{
		return "void";
	}

	@Override
	public String getJavaJniContainerType()
	{
		throw new IllegalStateException();
	}

	@Override
	public boolean isJavaPrimitive() { throw new IllegalStateException(); }

	@Override
	public String getCppJniType()
	{
		return "void";
	}

	@Override
	public String getCppJniArrayType()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getCppRawType()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getCppValueType()
	{
		return "void";
	}

	@Override
	public String getCppConstReferenceType()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getCppDefaultValue()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getObjcValueType()
	{
		return getObjcRawType();
	}

	@Override
	public String getObjcRawType()
	{
		return "void";
	}

	@Override
	public String getObjcValue(final String spec)
	{
		throw new IllegalStateException();
	}

	@Override
	public String getObjcMarshallType()
	{
		throw new IllegalStateException();
	}

	@Override
	public boolean isObjcPrimitive()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getObjcFormatPlaceholder()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getJniMarshaller()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getJavaMarshaller()
	{
		throw new IllegalStateException();
	}

	@Override
	public String getObjcMarshaller()
	{
		throw new IllegalStateException();
	}

	@Override
	public TypeConfig getHintType()
	{
		return this;
	}

	@Override
	public boolean isReturnable()
	{
		return false;
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
		return "V";
	}
}
