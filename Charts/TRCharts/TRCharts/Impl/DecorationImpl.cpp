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

#ifndef TRCharts_Impl_DecorationImpl_cpp
#define TRCharts_Impl_DecorationImpl_cpp

#include <TRCharts/Impl/DecorationImpl.hpp>


Charts::Decoration::Decoration(void)
	:color()
{
}


Charts::Decoration::~Decoration(void)
{
}


const Charts::Color & Charts::Decoration::getColor(void) const
{
	return this->color;
}


void Charts::Decoration::setColor(const Charts::Color & value)
{
    if(this->color != value) {
        newVersion();
        this->color = value;
    }
}

bool Charts::Decoration::update(const RenderArgs & args)
{
    bool changed = versionChanged();
    markVersion();
    return changed;
}

void Charts::Decoration::beforeRender(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(args.areaStart.x * args.contentScaleFactor, args.areaStart.y * args.contentScaleFactor, args.areaSize.x * args.contentScaleFactor, args.areaSize.y * args.contentScaleFactor);
}

void Charts::Decoration::afterRender(TR3DUtils::RenderContext & context, const RenderArgs & args) const
{
    glDisable(GL_SCISSOR_TEST);
}

#endif