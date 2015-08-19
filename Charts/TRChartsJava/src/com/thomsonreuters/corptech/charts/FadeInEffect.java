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
 * Fade the targeted drawables into view (opacity from 0% to 100%)
 * </p>
 * <p>
 * <b>WARNING:</b> This is an automatically generated wrapper around a
 * native object; overriding methods will not work as expected.
 * </p>
 */

@SuppressWarnings("all")
public class FadeInEffect extends BaseObject implements AnimationEffect
{
	/**
	 * Default constructor
	 */

	public FadeInEffect()
	{
		this(true);
		setHandle(nativeCreate());
	}

	/**
	 * Get the drawableList.
	 * <p>
	 * Targeted drawables
	 * </p>
	 * @return The current drawableList.
	 */

	public List<Drawable> getDrawableList()
	{
		return (List<Drawable>)nativeGetDrawableList(getHandle());
	}

	/**
	 * Set the drawableList.
	 * <p>
	 * Targeted drawables
	 * </p>
	 * @param value The new drawableList.
	 */

	public void setDrawableList(final List<Drawable> value)
	{
		nativeSetDrawableList(getHandle(), value);
	}

	/**
	 * <p>
	 * Apply the next step of the animation.
	 * </p>
	 * @param position Position of the animation (in seconds)
	 * @param duration Duration of the animation (in seconds)
	 */

	public void apply(final double position, final double duration)
	{
		nativeApply(getHandle(), position, duration);
	}

	// need this to prevent default constructor in base classes
	/*package*/ FadeInEffect(boolean dummy)
	{
		super(dummy);
	}

	protected void onFinalize()
	{
		nativeDestroy(getHandle());
	}

	private final native long nativeCreate();
	private final native void nativeDestroy(long ptr);
	private final native Object nativeGetDrawableList(long ptr);
	private final native void nativeSetDrawableList(long ptr, Object value);
	private final native void nativeApply(long ptr, double position, double duration);
}