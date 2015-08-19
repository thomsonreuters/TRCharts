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
/* NOTE: This file is autogenerated, do not edit this file directly.*/

package com.thomsonreuters.corptech.charts;

import java.util.List;

/**
 * <p>
 * Base class for axes that display numbers
 * </p>
 * <p>
 * <b>WARNING:</b> This is an automatically generated wrapper around a
 * native object; overriding methods will not work as expected.
 * </p>
 */

@SuppressWarnings("all")
public abstract class AbstractNumberAxis extends ContinuousAxis
{
	/**
	 * Default constructor
	 */

	private AbstractNumberAxis()
	{
		this(true);
	}

	/**
	 * Get the tick formatter.
	 * @return The current tick formatter.
	 */

	public NumberFormatter getTickFormatter()
	{
		return (NumberFormatter)nativeGetTickFormatter(getHandle());
	}

	/**
	 * Set the tick formatter.
	 * @param value The new tick formatter.
	 */

	public void setTickFormatter(final NumberFormatter value)
	{
		nativeSetTickFormatter(getHandle(), value);
	}

	// need this to prevent default constructor in base classes
	/*package*/ AbstractNumberAxis(boolean dummy)
	{
		super(dummy);
	}

	private final native Object nativeGetTickFormatter(long ptr);
	private final native void nativeSetTickFormatter(long ptr, Object value);
}