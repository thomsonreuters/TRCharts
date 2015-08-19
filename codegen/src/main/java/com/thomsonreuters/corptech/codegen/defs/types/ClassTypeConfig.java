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

import com.thomsonreuters.corptech.codegen.defs.ClassDef;
import com.thomsonreuters.corptech.codegen.defs.TopLevelDef;
import lombok.Getter;

import javax.annotation.Nonnull;
import java.util.Collections;
import java.util.Set;

public class ClassTypeConfig extends TypeConfig
{
	@Getter
	@Nonnull
	private final ClassDef classDef;

	public ClassTypeConfig(@Nonnull final ClassDef classDef)
	{
		this.classDef = classDef;
	}

	@Override
	public String getBasicType()
	{
		return "Class";
	}

	@Override
	public String getName()
	{
		return classDef.getName();
	}

	@Override
	public String getJavaType()
	{
		return classDef.getJavaClassname();
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
		return "Object";
	}

	@Override
	public String getJavaJniContainerType()
	{
		return getJavaJniType();
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
		return classDef.getCppNamespacedClassname();
	}

	@Override
	public String getCppValueType()
	{
		return "std::shared_ptr<" + getCppRawType() + ">";
	}

	@Override
	public String getCppConstReferenceType()
	{
		return "const " + getCppValueType() + " &";
	}

	@Override
	public String getCppDefaultValue()
	{
		return "nullptr";
	}

	@Override
	public String getObjcValueType()
	{
		return getObjcRawType() + " *";
	}

	@Override
	public String getObjcRawType()
	{
		return classDef.getObjcClassname();
	}

	@Override
	public String getObjcValue(final String spec)
	{
		return "nil";
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
		return "ObjectMarshaller<" + getCppRawType() + ">()";
	}

	@Override
	public String getJavaMarshaller()
	{
		return "ObjectMarshaller<" + getJavaType() + ">(" + getJavaType() + ".class)";
	}

	@Override
	public String getObjcMarshaller()
	{
		return "CodegenSupportObjc::ObjectMarshaller<" + getCppRawType() + ">()";
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
		return getForwardDependencies();
	}

	@Override
	public Set<TopLevelDef> getDependencies()
	{
		return Collections.emptySet();
	}

	@Override
	public Set<TopLevelDef> getForwardDependencies()
	{
		return Collections.<TopLevelDef>singleton(classDef);
	}

	@Override
	public String getJniSignature()
	{
		return classDef.getJniSignature();
	}
}
