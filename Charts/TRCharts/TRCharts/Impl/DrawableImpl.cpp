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

#ifndef TRCharts_Impl_DrawableImpl_cpp
#define TRCharts_Impl_DrawableImpl_cpp

#include <TRCharts/Impl/DrawableImpl.hpp>


Charts::Drawable::Drawable(void)
:visible(true), opacity(255.0)
{
}


Charts::Drawable::~Drawable(void)
{
}

bool Charts::Drawable::isVisible(void) const
{
	return this->visible;
}


void Charts::Drawable::setVisible(bool value)
{
    if(this->visible != value) {
        newVersion();
        this->visible = value;
    }
}

double Charts::Drawable::getOpacity(void) const
{
	return this->opacity;
}


void Charts::Drawable::setOpacity(double value)
{
    if(this->opacity != value) {
        newVersion();
        this->opacity = value;
    }
}


#endif