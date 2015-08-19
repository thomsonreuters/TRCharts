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
import org.apache.commons.lang.StringEscapeUtils;

import java.util.Collections;
import java.util.Set;

public class StringTypeConfig extends TypeConfig
{
	@Override
	public String getBasicType()
	{
		return "String";
	}

	@Override
	public String getName()
	{
		return "String";
	}

	@Override
	public String getJavaType()
	{
		return "String";
	}

	@Override
	public String getJavaContainerType()
	{
		return getJavaType();
	}

	@Override
	public String getJavaJniType()
	{
		return getJavaType();
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
		return "jstring";
	}

	@Override
	public String getCppJniArrayType()
	{
		return "jstringArray";
	}

	@Override
	public String getCppRawType()
	{
		return "std::string";
	}

	@Override
	public String getCppValueType()
	{
		return getCppRawType();
	}

	@Override
	public String getCppConstReferenceType()
	{
		return "const " + getCppRawType() + " &";
	}

	@Override
	public String getCppDefaultValue()
	{
		return "\"\"";
	}

	@Override
	public String getObjcValueType()
	{
		return getObjcRawType() + " *";
	}

	@Override
	public String getObjcRawType()
	{
		return "NSString";
	}

	@Override
	public String getJniMarshaller()
	{
		return "StringMarshaller()";
	}

	@Override
	public String getJavaMarshaller()
	{
		return "StringMarshaller()";
	}

	@Override
	public String getObjcValue(final String spec)
	{
		if(spec != null) {
			return "@\"" + StringEscapeUtils.escapeJava(spec) + "\"";
		} else {
			return "@\"\"";
		}
	}

	@Override
	public String getObjcMarshaller()
	{
		return "CodegenSupportObjc::StringMarshaller()";
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
		return "Ljava/lang/String;";
	}
}
