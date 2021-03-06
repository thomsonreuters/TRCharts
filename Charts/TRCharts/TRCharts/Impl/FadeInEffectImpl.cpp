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

#ifndef Charts_Impl_FadeInEffectImpl_cpp
#define Charts_Impl_FadeInEffectImpl_cpp

#include <TRCharts/Impl/FadeInEffectImpl.hpp>
#include <TRCharts/Drawable.hpp>


Charts::FadeInEffect::FadeInEffect(void)
	:GeneratedFadeInEffect(), drawableList()
{
}


Charts::FadeInEffect::~FadeInEffect(void)
{
}


const std::vector<std::shared_ptr<Charts::Drawable>> & Charts::FadeInEffect::getDrawableList(void) const
{
	return this->drawableList;
}


void Charts::FadeInEffect::setDrawableList(const std::vector<std::shared_ptr<Charts::Drawable>> & value)
{
	this->drawableList = value;
}

void Charts::FadeInEffect::apply(double position, double duration) const
{
    const double value = position / duration;
    const double opacity = value * 255.0;
    for(const auto & drawable : drawableList) {
        drawable->setOpacity(opacity);
    }
}

#endif