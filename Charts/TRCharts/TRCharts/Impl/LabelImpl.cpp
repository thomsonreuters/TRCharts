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

#ifndef TRCharts_Impl_LabelImpl_cpp
#define TRCharts_Impl_LabelImpl_cpp

#include <TRCharts/Impl/LabelImpl.hpp>


Charts::Label::Label(void)
	:text(), color(), font(), margin(), size()
{
}


Charts::Label::~Label(void)
{
}


const std::string & Charts::Label::getText(void) const
{
	return this->text;
}


void Charts::Label::setText(const std::string & value)
{
    if(this->text != value) {
        newVersion();
        this->text = value;
    }
}


const Charts::Color & Charts::Label::getColor(void) const
{
	return this->color;
}


void Charts::Label::setColor(const Charts::Color & value)
{
    if(this->color != value) {
        newVersion();
        this->color = value;
    }
}


const Charts::Font & Charts::Label::getFont(void) const
{
	return this->font;
}


void Charts::Label::setFont(const Charts::Font & value)
{
    if(this->font != value) {
        newVersion();
        this->font = value;
    }
}


const Charts::Margin & Charts::Label::getMargin(void) const
{
	return this->margin;
}


void Charts::Label::setMargin(const Charts::Margin & value)
{
    if(this->margin != value) {
        newVersion();
        this->margin = value;
    }
}


const Charts::Size & Charts::Label::getSize(void) const
{
	return this->size;
}


void Charts::Label::setSize(const Charts::Size & value)
{
    if(this->size != value) {
        newVersion();
        this->size = value;
    }
}

double Charts::Label::getFullHeight(void) const
{
    return margin.top + size.height + margin.bottom;
}


double Charts::Label::getFullWidth(void) const
{
    return margin.top + size.width + margin.right;
}

#endif