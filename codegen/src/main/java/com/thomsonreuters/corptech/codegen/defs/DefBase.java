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
import lombok.Getter;
import lombok.Setter;

import javax.validation.Valid;
import javax.xml.bind.Unmarshaller;
import javax.xml.bind.annotation.*;
import java.text.CharacterIterator;
import java.text.StringCharacterIterator;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;

@Getter
@Setter
@XmlAccessorType(XmlAccessType.FIELD)
public class DefBase
{
	@XmlTransient
	private DefBase parent;

	@XmlID
	@XmlAttribute(name = "id")
	private String id;

	@XmlElement(name = "comment")
	@Valid
	private List<CommentDef> comments = new ArrayList<>();

	public void afterUnmarshal(final Unmarshaller unmarshaller, final Object parent)
	{
		this.parent = (DefBase)parent;
	}

	public void init()
	{
	}

	protected static void initDefs(final List<? extends DefBase> defs)
	{
		for(final DefBase def : defs) {
			def.init();
		}
	}

	public DefBase resolveNamespace(final String name)
	{
		if(parent != null) {
			return parent.resolveNamespace(name);
		} else {
			throw new IllegalStateException("Namespace '" + name + "' not found");
		}
	}

	public TypeConfig createTypeConfig(final String name, final TypeConfig ... templateArgs)
	{
		if(parent != null) {
			return parent.createTypeConfig(name, templateArgs);
		} else {
			throw new IllegalStateException("Type '" + name + "' not found");
		}
	}

	public Map<String, String> resolveVariables()
	{
		if(parent != null) {
			return parent.resolveVariables();
		} else {
			return Collections.emptyMap();
		}
	}

	public String resolveVariable(final String name)
	{
		if(parent != null) {
			return parent.resolveVariable(name);
		} else {
			throw new IllegalStateException("Variable " + name + " not found");
		}
	}

	public TypeConfig resolveType(final String description)
	{
		if(description == null) {
			return null;
		}
		final CharacterIterator iterator = new StringCharacterIterator(description);
		final TypeConfig result = resolveType(iterator);
		eatWs(iterator);
		expect(iterator, CharacterIterator.DONE);
		return result;
	}

	public List<TypeConfig> resolveTypes(final String description)
	{
		if(description == null) {
			return Collections.emptyList();
		}
		final CharacterIterator iterator = new StringCharacterIterator(description);
		final List<TypeConfig> results = new ArrayList<>();
		while(true) {
			results.add(resolveType(iterator));
			eatWs(iterator);
			if(iterator.current() == ',') {
				iterator.next();
			} else {
				break;
			}
		}
		eatWs(iterator);
		expect(iterator, CharacterIterator.DONE);
		return results;
	}

	private void eatWs(final CharacterIterator iterator)
	{
		while(Character.isWhitespace(iterator.current())) {
			iterator.next();
		}
	}

	private String characterName(final char c)
	{
		return c == CharacterIterator.DONE ? "end-of-sequence" : Character.toString(c);
	}

	private void expect(final CharacterIterator iterator, final char c)
	{
		if(iterator.current() != c) {
			throw new IllegalStateException("Expected " + characterName(c) + " (got '" + characterName(iterator.current()) + "')");
		}
	}

	private TypeConfig resolveType(final CharacterIterator iterator)
	{
		DefBase namespace = this;
		StringBuilder baseName = new StringBuilder();
		final List<TypeConfig> templateArgs = new ArrayList<>();
		eatWs(iterator);
		char c = iterator.current();
		while (c != CharacterIterator.DONE) {
			if(c == '[') {
				do {
					iterator.next();
					templateArgs.add(resolveType(iterator));
					eatWs(iterator);
					c = iterator.current();
				} while(c == ',');
				eatWs(iterator);
				expect(iterator, ']');
			} else if (c == '.') {
				namespace = namespace.resolveNamespace(baseName.toString());
				baseName = new StringBuilder();
			} else if (Character.isJavaIdentifierPart(c)) {
				baseName.append(c);
			} else {
				break;
			}
			c = iterator.next();
		}
		return namespace.createTypeConfig(baseName.toString().trim(), templateArgs.toArray(new TypeConfig[templateArgs.size()]));
	}

	private List<CommentDef> getComments(final String scope)
	{
		final List<CommentDef> result = new ArrayList<>();
		for(final CommentDef commentDef : getComments()) {
			if(commentDef.getScope() == null || commentDef.getScope().isEmpty() || commentDef.getScope().equals(scope)) {
				result.add(commentDef);
			}
		}
		return result;
	}

	public List<CommentDef> getCppComments()
	{
		return getComments("cpp");
	}

	public List<CommentDef> getJniComments()
	{
		return getComments("jni");
	}

	public List<CommentDef> getJavaComments()
	{
		return getComments("java");
	}

	public List<CommentDef> getObjcComments()
	{
		return getComments("objc");
	}
}
