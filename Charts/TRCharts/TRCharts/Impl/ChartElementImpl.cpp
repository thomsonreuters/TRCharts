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

#ifndef TRCharts_Impl_ChartElementImpl_cpp
#define TRCharts_Impl_ChartElementImpl_cpp

#include <TRCharts/Impl/ChartElementImpl.hpp>
#include <stdexcept>


Charts::ChartElement::ChartElement(void)
:drawOrder(0)
{
}


Charts::ChartElement::~ChartElement(void)
{
}

void Charts::ChartElement::attach(void)
{
    GeneratedChartElement::attach();
    newVersion();
}

long Charts::ChartElement::getDrawOrder(void) const
{
    return this->drawOrder;
}

void Charts::ChartElement::setDrawOrder(long value)
{
    if(this->drawOrder != value) {
        newVersion();
        this->drawOrder = value;
    }
}
#endif
