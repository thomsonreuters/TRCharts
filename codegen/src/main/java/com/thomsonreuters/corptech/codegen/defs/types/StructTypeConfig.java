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

import com.thomsonreuters.corptech.codegen.defs.FieldDef;
import com.thomsonreuters.corptech.codegen.defs.StructDef;
import com.thomsonreuters.corptech.codegen.defs.TopLevelDef;
import lombok.Getter;

import javax.annotation.Nonnull;
import java.util.Collections;
import java.util.List;
import java.util.Set;

public class StructTypeConfig extends TypeConfig
{
	@Getter
	@Nonnull
	private final StructDef structDef;

	public StructTypeConfig(@Nonnull final StructDef structDef)
	{
		this.structDef = structDef;
	}

	@Override
	public String getBasicType()
	{
		return "Struct";
	}

	@Override
	public String getName()
	{
		return structDef.getName();
	}

	@Override
	public String getJavaType()
	{
		return structDef.getJavaClassname();
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
		return structDef.getCppNamespacedClassname();
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
		return structDef.getObjcClassname();
	}

	@Override
	public String getObjcValue(final String spec)
	{
		final String [] specs;
		if(spec != null) {
			// TODO: will not work well with strings
			specs = spec.split(",");
		} else {
			specs = null;
		}
		final List<FieldDef> fields = structDef.getAllFields();
		if(!fields.isEmpty()) {
			final StringBuilder result = new StringBuilder();
			result.append("[");
			result.append(structDef.getObjcClassname());
			for(int i = 0; i != fields.size(); ++i) {
				final FieldDef fieldDef = fields.get(i);
				result.append(" ");
				result.append(fieldDef.getName());
				result.append(":");
				if(specs == null) {
					result.append(fieldDef.getObjcDefaultValue());
				} else {
					result.append(fieldDef.getType().getObjcValue(specs[i]));
				}
			}
			result.append("]");
			return result.toString();
		} else {
			return "[[" + structDef.getObjcClassname() + " alloc] init]";
		}
	}

	@Override
	public String getObjcMarshallType()
	{
		return "id";
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
		return structDef.getName() + "StructMarshaller()";
	}

	@Override
	public String getJavaMarshaller()
	{
		return "??()";
	}

	@Override
	public String getObjcMarshaller()
	{
		return structDef.resolveVariable("objcSupportNamespace") + "::" + structDef.getName() + "StructMarshaller()";
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
		return Collections.<TopLevelDef>singleton(structDef);
	}

	@Override
	public Set<TopLevelDef> getForwardDependencies()
	{
		return Collections.emptySet();
	}

	@Override
	public String getJniSignature()
	{
		return structDef.getJniSignature();
	}
}
