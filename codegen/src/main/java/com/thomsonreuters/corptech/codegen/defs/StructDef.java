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

package com.thomsonreuters.corptech.codegen.defs;

import com.thomsonreuters.corptech.codegen.defs.types.StructTypeConfig;
import com.thomsonreuters.corptech.codegen.defs.types.TypeConfig;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;

import javax.validation.Valid;
import javax.xml.bind.annotation.*;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class StructDef extends TopLevelDef
{
	@XmlAttribute(name = "extend")
	private String extendName;

	@XmlTransient
	@Setter(AccessLevel.PRIVATE)
	private TypeConfig extend;

	@XmlElement(name = "field")
	@Valid
	private final List<FieldDef> fields = new ArrayList<>();

	// @TODO validate that only static methods are on structs
	@XmlElement(name = "method")
	@Valid
	private final List<MethodDef> methods = new ArrayList<>();

	public boolean isBound()
	{
		return true;
	}

	@Override
	public void init()
	{
		initDefs(fields);
		initDefs(methods);
		extend = resolveType(extendName);
	}

	@Override
	public List<CommentDef> getComments()
	{
		final List<CommentDef> result = new ArrayList<>(super.getComments());
		final CommentDef autogenWarning = new CommentDef();
		autogenWarning.setType("note");
		autogenWarning.setBody("This is a value class, when passing it to other library methods it is always effectively copied.");
		result.add(autogenWarning);
		return result;
	}

	public Set<TypeConfig> getReferencedTypes()
	{
		final Set<TypeConfig> out = new LinkedHashSet<>();
		for(final FieldDef fieldDef : fields) {
			out.addAll(fieldDef.getReferencedTypes());
		}
		return out;
	}

	public List<FieldDef> getInheritedFields()
	{
		final List<FieldDef> result = new ArrayList<>();
		if(extend != null && extend instanceof StructTypeConfig) {
			result.addAll(((StructTypeConfig)extend).getStructDef().getFields());
		}
		return result;
	}

	public List<FieldDef> getAllFields()
	{
		final List<FieldDef> result = new ArrayList<>();
		result.addAll(getInheritedFields());
		result.addAll(fields);
		return result;
	}

	@Override
	public String getCppDeclarationType()
	{
		return "struct";
	}

	@Override
	public String getObjcDeclarationType()
	{
		return "@class";
	}

	public String getJniSignature()
	{
		return "L" + resolveVariable("javaPackage").replace(".", "/") + "/" + getJavaClassname() + ";";
	}

	@Override
	public Set<TopLevelDef> getDependencies()
	{
		final Set<TopLevelDef> out = new LinkedHashSet<>();
		if(extend != null) {
			out.addAll(extend.getDependencies());
		}
		for(final FieldDef fieldDef : fields) {
			out.addAll(fieldDef.getDependencies());
		}
		for(final MethodDef methodDef : methods) {
			out.addAll(methodDef.getDependencies());
		}
		return out;
	}

	@Override
	public Set<TopLevelDef> getForwardDependencies()
	{
		final Set<TopLevelDef> out = new LinkedHashSet<>();
		for(final FieldDef fieldDef : fields) {
			out.addAll(fieldDef.getForwardDependencies());
		}
		for(final MethodDef methodDef : methods) {
			out.addAll(methodDef.getForwardDependencies());
		}
		return out;
	}

	public TypeConfig createTypeConfig(final TypeConfig... templateArgs)
	{
		assert(templateArgs.length == 0);
		return new StructTypeConfig(this);
	}

	@Override
	public String getObjcMarshallerIncludeFile()
	{
		return resolveVariable("objcFilePrefix") + "Support/" + getName() + "StructMarshaller.hh";
	}
}
