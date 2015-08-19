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
 * Draws a line at a fixed data position on a given axis
 * </p>
 * <p>
 * <b>WARNING:</b> This is an automatically generated wrapper around a
 * native object; overriding methods will not work as expected.
 * </p>
 */

@SuppressWarnings("all")
public class LineDecoration extends Decoration
{
	/**
	 * Default constructor
	 */

	public LineDecoration()
	{
		this(true);
		setHandle(nativeCreate());
	}

	/**
	 * Get the axis.
	 * <p>
	 * Axis to associate the decoration with. The decoration will intersect the
	 * axis at the specified value
	 * </p>
	 * @return The current axis.
	 */

	public ContinuousAxis getAxis()
	{
		return (ContinuousAxis)nativeGetAxis(getHandle());
	}

	/**
	 * Set the axis.
	 * <p>
	 * Axis to associate the decoration with. The decoration will intersect the
	 * axis at the specified value
	 * </p>
	 * @param value The new axis.
	 */

	public void setAxis(final ContinuousAxis value)
	{
		nativeSetAxis(getHandle(), value);
	}

	/**
	 * Get the value.
	 * <p>
	 * Position in data co-ordinates (relative to the axis)
	 * </p>
	 * @return The current value.
	 */

	public double getValue()
	{
		return nativeGetValue(getHandle());
	}

	/**
	 * Set the value.
	 * <p>
	 * Position in data co-ordinates (relative to the axis)
	 * </p>
	 * @param value The new value.
	 */

	public void setValue(final double value)
	{
		nativeSetValue(getHandle(), value);
	}

	/**
	 * Get the lineStyle.
	 * <p>
	 * Drawing style for the line
	 * </p>
	 * @return The current lineStyle.
	 */

	public LineStyle getLineStyle()
	{
		return (LineStyle)nativeGetLineStyle(getHandle());
	}

	/**
	 * Set the lineStyle.
	 * <p>
	 * Drawing style for the line
	 * </p>
	 * @param value The new lineStyle.
	 */

	public void setLineStyle(final LineStyle value)
	{
		nativeSetLineStyle(getHandle(), value);
	}

	// need this to prevent default constructor in base classes
	/*package*/ LineDecoration(boolean dummy)
	{
		super(dummy);
	}

	protected void onFinalize()
	{
		nativeDestroy(getHandle());
	}

	private final native long nativeCreate();
	private final native void nativeDestroy(long ptr);
	private final native Object nativeGetAxis(long ptr);
	private final native void nativeSetAxis(long ptr, Object value);
	private final native double nativeGetValue(long ptr);
	private final native void nativeSetValue(long ptr, double value);
	private final native Object nativeGetLineStyle(long ptr);
	private final native void nativeSetLineStyle(long ptr, Object value);
}