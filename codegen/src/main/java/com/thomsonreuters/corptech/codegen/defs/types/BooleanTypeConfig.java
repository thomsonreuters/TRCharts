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

public class BooleanTypeConfig extends TypeConfig
{
	@Override
	public String getBasicType()
	{
		return "Boolean";
	}

	@Override
	public String getName()
	{
		return "Boolean";
	}

	@Override
	public String getJavaType()
	{
		return "boolean";
	}

	@Override
	public String getJavaContainerType()
	{
		return "Boolean";
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
		return "jboolean";
	}

	@Override
	public String getCppJniArrayType()
	{
		return "jbooleanArray";
	}

	@Override
	public String getCppRawType()
	{
		return "bool";
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
		return "false";
	}

	@Override
	public String getObjcValueType()
	{
		return getObjcRawType();
	}

	@Override
	public String getObjcRawType()
	{
		return "BOOL";
	}

	@Override
	public String getObjcValue(final String spec)
	{
		if(spec != null) {
			if(Boolean.parseBoolean(spec)) {
				return "YES";
			} else {
				return "NO";
			}
		} else {
			return "NO";
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
		return "d";
	}

	@Override
	public String getJniMarshaller()
	{
		return "BooleanMarshaller()";
	}

	@Override
	public String getJavaMarshaller()
	{
		return "BooleanMarshaller()";
	}

	@Override
	public String getObjcMarshaller()
	{
		return "CodegenSupportObjc::BooleanMarshaller()";
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
		return "Z";
	}

	@Override
	public String getGetterPrefix()
	{
		return "is";
	}
}
