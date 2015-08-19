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

import com.thomsonreuters.corptech.codegen.defs.types.ClassTypeConfig;
import com.thomsonreuters.corptech.codegen.defs.types.TemplateClassTypeConfig;
import com.thomsonreuters.corptech.codegen.defs.types.TypeConfig;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.Setter;

import javax.validation.Valid;
import javax.xml.bind.annotation.*;
import java.util.*;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class ClassDef extends TopLevelDef
{
	@XmlAttribute(name = "extend")
	private String extendName;

	@XmlTransient
	@Setter(AccessLevel.PRIVATE)
	private TypeConfig extend;

	@XmlAttribute(name = "implement")
	private String implementNames;

	@XmlTransient
	private final List<TypeConfig> implement = new ArrayList<>();

	@XmlAttribute(name = "instance")
	private boolean instance = true;

	@XmlAttribute(name = "concrete")
	private boolean concrete = true;

	@XmlElement(name = "field")
	@Valid
	private final List<FieldDef> fields = new ArrayList<>();

	@XmlElement(name = "method")
	@Valid
	private final List<MethodDef> methods = new ArrayList<>();

	private final List<FieldDef> newlyBoundFields = new ArrayList<>();

	private final List<MethodDef> newlyBoundMethods = new ArrayList<>();

	@Override
	public List<CommentDef> getComments()
	{
		final List<CommentDef> result = new ArrayList<>(super.getComments());
		final CommentDef autogenWarning = new CommentDef();
		autogenWarning.setType("warning");
		autogenWarning.setBody("This is an automatically generated wrapper around a native object; overriding methods will not work as expected.");
		result.add(autogenWarning);
		return result;
	}

	@Override
	public void init()
	{
		extend = resolveType(extendName);
		implement.addAll(resolveTypes(implementNames));
		initDefs(fields);
		initDefs(methods);
	}

	public void postInit()
	{
		TypeConfig parent = extend;
		while(parent instanceof TemplateClassTypeConfig) {
			final TemplateClassTypeConfig parentInstantiation = ((TemplateClassTypeConfig)parent);
			final TemplateClassDef parentClass = parentInstantiation.getClassDef();
			final Map<String, TypeConfig> args = new HashMap<>();
			final List<TemplateParameterDef> templateParameterDefs = parentClass.getTemplateParameters();
			final List<TypeConfig> templateTypes = parentInstantiation.getTemplateArgs();
			for(int i = 0; i != templateParameterDefs.size(); ++i) {
				args.put(templateParameterDefs.get(i).getName(), templateTypes.get(i));
			}
			for(final FieldDef fieldDef : parentClass.getFields()) {
				if(!fieldDef.isBound()) {
					final FieldDef bound = fieldDef.bind(args);
					if(bound.isBound()) {
						newlyBoundFields.add(bound);
					}
				}
			}
			for(final MethodDef methodDef : parentClass.getMethods()) {
				if(!methodDef.isBound()) {
					final MethodDef bound = methodDef.bind(args);
					if(bound.isBound()) {
						newlyBoundMethods.add(bound);
					}
				}
			}
			parent = parentClass.getExtend();
		}
	}

	public boolean isBound()
	{
		return true;
	}

	public Set<TypeConfig> getReferencedTypes()
	{
		final Set<TypeConfig> out = new LinkedHashSet<>();
		for(final FieldDef fieldDef : fields) {
			out.addAll(fieldDef.getReferencedTypes());
		}
		for(final MethodDef methodDef : methods) {
			out.addAll(methodDef.getReferencedTypes());
		}
		for(final FieldDef fieldDef : newlyBoundFields) {
			out.addAll(fieldDef.getReferencedTypes());
		}
		for(final MethodDef methodDef : newlyBoundMethods) {
			out.addAll(methodDef.getReferencedTypes());
		}
		return out;
	}

	public String getCppImplClassname()
	{
		return getName() + "Impl";
	}

	public String getCppNamespacedImplClassname()
	{
		return resolveVariable("cppNamespace") + "::" + getCppImplClassname();
	}

	public String getJniSignature()
	{
		return "L" + resolveVariable("javaPackage").replace(".", "/") + "/" + getJavaClassname() + ";";
	}

	@Override
	public String getCppDeclarationType()
	{
		return "class";
	}

	@Override
	public String getObjcDeclarationType()
	{
		return "@class";
	}

	@Override
	public Set<TopLevelDef> getDependencies()
	{
		final Set<TopLevelDef> out = new LinkedHashSet<>();
		if(extend != null) {
			out.addAll(extend.getForwardDependencies());
		} else {
			//out.add(BASE_CLASS);
		}
		for(final TypeConfig implementEntry : implement) {
			out.addAll(implementEntry.getSuperDependencies());
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
		return new ClassTypeConfig(this);
	}
}
