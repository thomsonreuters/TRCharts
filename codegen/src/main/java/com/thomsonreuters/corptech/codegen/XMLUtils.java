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

package com.thomsonreuters.corptech.codegen;

import org.apache.log4j.Logger;

import javax.validation.ConstraintViolation;
import javax.validation.ConstraintViolationException;
import javax.validation.Validation;
import javax.validation.Validator;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import java.io.InputStream;
import java.util.LinkedHashSet;
import java.util.Set;

public class XMLUtils
{
	private static final Logger log = Logger.getLogger(XMLUtils.class);

	public static <T> T unmarshall(final Class<T> docClass, final InputStream inputStream) throws JAXBException
	{
		final JAXBContext jc = JAXBContext.newInstance(docClass);
		final Unmarshaller u = jc.createUnmarshaller();
		return (T)u.unmarshal(inputStream);
	}

	public static <T> void validate(final T value)
	{
		Validator validator = Validation.buildDefaultValidatorFactory().getValidator();
		final Set<ConstraintViolation<T>> violations = validator.validate(value);
		if(!violations.isEmpty()) {
			final Set<ConstraintViolation<?>> tmp = new LinkedHashSet<>();
			for(final ConstraintViolation<?> violation : violations) {
				log.error(violation.getPropertyPath() + ": " + violation.getMessage());
				tmp.add(violation);
			}
			throw new ConstraintViolationException(tmp);
		}
	}

}
