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
import lombok.Getter;

import javax.annotation.Nonnull;
import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.Set;

public class ListTypeConfig extends TypeConfig
{
	@Getter
	@Nonnull
	private final TypeConfig valueType;

	public ListTypeConfig(@Nonnull final TypeConfig valueType)
	{
		this.valueType = valueType;
	}

	@Override
	public String getBasicType()
	{
		return "List";
	}

	@Override
	public String getName()
	{
		return "List" + valueType.getName();
	}

	@Override
	public String getJavaType()
	{
		return "List<" + valueType.getJavaContainerType() + ">";
	}

	@Override
	public String getJavaContainerType()
	{
		return getJavaType();
	}

	@Override
	public boolean isJavaPrimitive() { return false; }

	@Override
	public String getJavaJniType()
	{
		return "Object";//valueType.getConfig().getJavaJniType() + "[]";
	}

	@Override
	public String getJavaJniContainerType()
	{
		return "Object";
	}

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
		return "std::vector<" + valueType.getCppValueType() + ">";
	}

	@Override
	public String getCppValueType()
	{
		return getCppRawType();
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
		return getObjcRawType() + " *";
	}

	@Override
	public String getObjcRawType()
	{
		return "NSArray";
	}

	@Override
	public String getObjcValue(final String spec)
	{
		if(spec != null) {
			final StringBuilder result = new StringBuilder();
			result.append("@[");
			// TODO: will not work well with strings
			final String [] specs = spec.split(",");
			for(int i = 0; i != specs.length; ++i) {
				if(i != 0) {
					result.append(", ");
				}
				result.append(valueType.getObjcValue(specs[i]));
			}
			result.append("]");
			return result.toString();
		} else {
			return "@[]";
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
		return valueType;
	}

	@Override
	public String getJniMarshaller()
	{
		return "ListMarshaller<" + valueType.getCppValueType() + ", " + valueType.getCppJniType() + ">(get" + valueType.getName() + "Marshaller())";
	}

	@Override
	public String getJavaMarshaller()
	{
		return "ListMarshaller<" + valueType.getJavaContainerType() + ">()";
	}

	@Override
	public String getObjcMarshaller()
	{
		return "CodegenSupportObjc::ListMarshaller<" + valueType.getCppValueType() + ", " + valueType.getObjcMarshallType() + ">(get" + valueType.getName() + "Marshaller())";
	}

	@Override
	public boolean isReturnable()
	{
		return true;
	}

	@Override
	public boolean isBound()
	{
		return valueType.isBound();
	}

	@Override
	public Set<TopLevelDef> getSuperDependencies()
	{
		return Collections.emptySet();
	}

	@Override
	public Set<TopLevelDef> getDependencies()
	{
		return valueType.getDependencies();
	}

	@Override
	public Set<TopLevelDef> getForwardDependencies()
	{
		return valueType.getForwardDependencies();
	}

	@Override
	public Set<TypeConfig> getReferencedTypes()
	{
		final Set<TypeConfig> result = new LinkedHashSet<>();
		result.addAll(super.getReferencedTypes());
		result.add(valueType);
		return result;
	}

	@Override
	public String getJniSignature()
	{
		return "Ljava/util/List;";
	}
}