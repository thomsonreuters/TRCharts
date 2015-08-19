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

#import <TRChartsObjc/Attachable.h>
@protocol TRAnimationEffect;
@protocol TRAnimationDelegate;

/**
 * An animation describes a series of effects that are applied over a duration.
 *
 * To animate elements, create effects targetting those elements and associate
 * them with an animation, then add the animation to a chart.
 *
 * The animation will run until completion, then the (optional) animation
 * delegate will be called, and the animation will be removed from the chart in
 * the next update cycle.
 *
 * @warning This is an automatically generated wrapper around a native object;
 * overriding methods will not work as expected.
 *
 */
@interface TRAnimation : TRAttachable

/** @name Fields */

/**
 * Animation duration (in seconds)
 *
 * @return The current duration.
 * @see setDuration:
 */
-(double)duration;

/**
 * Animation duration (in seconds)
 *
 * @param value The new duration.
 * @see duration
 */
-(void)setDuration:(double)value;

/**
 * Current position of the animation (in seconds)
 *
 * @return The current position.
 * @see setPosition:
 */
-(double)position;

/**
 * Current position of the animation (in seconds)
 *
 * @param value The new position.
 * @see position
 */
-(void)setPosition:(double)value;

/**
 * Effects applied by this animation
 *
 * @return The current effect list.
 * @see setEffectList:
 */
-(NSArray *)effectList;

/**
 * Effects applied by this animation
 *
 * @param value The new effect list.
 * @see effectList
 */
-(void)setEffectList:(NSArray *)value;

/**
 * The delegate will be called back when the animation is completed (or
 * cancelled)
 *
 * @return The current delegate.
 * @see setDelegate:
 */
-(id<TRAnimationDelegate>)delegate;

/**
 * The delegate will be called back when the animation is completed (or
 * cancelled)
 *
 * @param value The new delegate.
 * @see delegate
 */
-(void)setDelegate:(id<TRAnimationDelegate>)value;

/** @name Methods */

/**
 * Set animation position to beginning and continue running.
 *
 */
-(void)restart;

/**
 * Set animation position to the end and stop running, flag the animation for
 * removal.
 *
 */
-(void)complete;

/**
 * Stop running, flag the animation for removal.
 *
 */
-(void)cancel;

@end