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

import com.thomsonreuters.corptech.codegen.defs.types.TypeConfig;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;

import javax.validation.Valid;
import javax.validation.constraints.AssertTrue;
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.*;
import java.util.*;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class MethodDef extends DefBase
{
	@XmlAttribute(name = "name")
	@NotNull
	private String name;

	@XmlAttribute(name = "instance")
	private boolean instance = true;

	@XmlAttribute(name = "concrete")
	private boolean concrete = true;

	@XmlAttribute(name = "returnType")
	@NotNull
	private String returnTypeName;

	@XmlTransient
	@Setter(AccessLevel.PRIVATE)
	private TypeConfig returnType;

	@XmlAttribute(name = "returnReference")
	private boolean returnReference = false;

	@XmlAttribute(name = "mutating")
	private boolean mutating;

	@XmlElement(name = "parameter")
	@Valid
	private final List<ParameterDef> parameters = new ArrayList<>();

	@Override
	public void init()
	{
		returnType = resolveType(returnTypeName);
		initDefs(parameters);
	}

	public MethodDef bind(final Map<String, TypeConfig> args)
	{
		final MethodDef result = new MethodDef();
		result.name = name;
		result.concrete = concrete;
		result.returnType = returnType.bind(args);
		result.mutating = mutating;
		for(final ParameterDef parameterDef : parameters) {
			result.parameters.add(parameterDef.bind(args));
		}
		result.getComments().addAll(getComments());
		return result;
	}

	public boolean isBound()
	{
		boolean result = returnType.isBound();
		for(final ParameterDef parameterDef : parameters) {
			result = result && parameterDef.isBound();
		}
		return result;
	}

	public Set<TypeConfig> getReferencedTypes()
	{
		final Set<TypeConfig> out = new LinkedHashSet<>();
		out.addAll(returnType.getReferencedTypes());
		for(final ParameterDef parameterDef : parameters) {
			out.addAll(parameterDef.getReferencedTypes());
		}
		return out;
	}

	public Set<TopLevelDef> getDependencies()
	{
		final Set<TopLevelDef> result = new LinkedHashSet<>();
		result.addAll(returnType.getDependencies());
		for(final ParameterDef parameterDef : parameters) {
			result.addAll(parameterDef.getDependencies());
		}
		return result;
	}

	public Set<TopLevelDef> getForwardDependencies()
	{
		final Set<TopLevelDef> result = new LinkedHashSet<>();
		result.addAll(returnType.getForwardDependencies());
		for(final ParameterDef parameterDef : parameters) {
			result.addAll(parameterDef.getForwardDependencies());
		}
		return result;
	}

	public String getJniSignature()
	{
		final StringBuilder parameterSignatures = new StringBuilder();
		for(final ParameterDef parameterDef : parameters) {
			parameterSignatures.append(parameterDef.getType().getJniSignature());
		}
		return "(" + parameterSignatures + ")" + returnType.getJniSignature();
	}

	@AssertTrue(message = "Unbound method must not be concrete")
	public boolean validateBoundState()
	{
		return !isConcrete() || isBound();
	}
}
