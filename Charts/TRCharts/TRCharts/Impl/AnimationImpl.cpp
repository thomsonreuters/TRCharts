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

#ifndef Charts_Impl_AnimationImpl_cpp
#define Charts_Impl_AnimationImpl_cpp

#include <TRCharts/Impl/AnimationImpl.hpp>
#include <TRCharts/AnimationEffect.hpp>
#include <TRCharts/AnimationDelegate.hpp>

#include <TR3DUtils/Utils.hpp>

Charts::Animation::Animation(void)
:GeneratedAnimation(), duration(1.0), position(), effectList(), delegate(), state(UNSTARTED)
{
}


Charts::Animation::~Animation(void)
{
}

void Charts::Animation::attach(void)
{
    GeneratedAnimation::attach();
    // reset on attach
    this->restart();
}

double Charts::Animation::getDuration(void) const
{
	return this->duration;
}


void Charts::Animation::setDuration(double value)
{
	this->duration = value;
}


double Charts::Animation::getPosition(void) const
{
	return this->position;
}


void Charts::Animation::setPosition(double value)
{
    value = glm::clamp(value, 0.0, 1.0);
	this->position = value;
}


const std::vector<std::shared_ptr<Charts::AnimationEffect>> & Charts::Animation::getEffectList(void) const
{
	return this->effectList;
}


void Charts::Animation::setEffectList(const std::vector<std::shared_ptr<Charts::AnimationEffect>> & value)
{
	this->effectList = value;
}


const std::shared_ptr<Charts::AnimationDelegate> & Charts::Animation::getDelegate(void) const
{
	return this->delegate;
}


void Charts::Animation::setDelegate(const std::shared_ptr<Charts::AnimationDelegate> & value)
{
	this->delegate = value;
}

void Charts::Animation::restart(void)
{
    position = 0.0;
    state = UNSTARTED;
}

void Charts::Animation::complete(void)
{
	this->position = this->duration;
}

void Charts::Animation::cancel(void)
{
    if(this->state == UNSTARTED || this->state == STARTED) {
        this->state = CANCEL;
    }
}

void Charts::Animation::update(double elapsedSeconds)
{
    if(this->isEnabled()) {
        if(this->state == CANCEL) {
            this->state = CANCELLED;
        }
        if(this->state == UNSTARTED || this->state == STARTED) {
            this->position = glm::clamp(this->position + (elapsedSeconds / duration), 0.0, this->duration);
            for(const auto & effect : effectList) {
                if(TR_VERIFY(effect)) {
                    effect->apply(position, duration);
                }
            }
            if(this->position >= this->duration) {
                this->state = COMPLETED;
            } else {
                this->state = STARTED;
            }
        }
    }
}

void Charts::Animation::postUpdate(void)
{
    if(this->isEnabled()) {
        if(this->state == CANCELLED) {
            this->state = REMOVE;
            if(this->delegate) {
                this->delegate->animationCancelled(getSharedPtr());
            }
        } else if(this->state == COMPLETED) {
            this->state = REMOVE;
            if(this->delegate) {
                this->delegate->animationCompleted(getSharedPtr());
            }
        }
    }
}

bool Charts::Animation::doRemove(void) const
{
    return this->state == REMOVE;
}

#endif