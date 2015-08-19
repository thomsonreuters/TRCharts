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

#ifndef TRCharts_Impl_ContinuousAxisImpl_cpp
#define TRCharts_Impl_ContinuousAxisImpl_cpp

#include <TRCharts/Impl/ContinuousAxisImpl.hpp>
#include <TRCharts/RangeCalculator.hpp>
#include <TRCharts/AxisLayout.hpp>
#include <TRCharts/Impl/Utils.hpp>
#include <TR3DUtils/Utils.hpp>
#include <TR3DUtils/Log.hpp>


Charts::ContinuousAxis::ContinuousAxis(void)
:rawDataRange(), dataRange(), screenDataRange(), valueTransform(0.0, 1.0), relayoutRequired(true)
{
}


Charts::ContinuousAxis::~ContinuousAxis(void)
{
}


const Charts::DataTransform & Charts::ContinuousAxis::getValueTransform(void) const
{
    return this->valueTransform;
}

void Charts::ContinuousAxis::setValueTransform(const Charts::DataTransform & value)
{
    if(this->valueTransform != value) {
        newVersion();
        this->valueTransform = value;
    }
}

const std::shared_ptr<Charts::AxisLayout> & Charts::ContinuousAxis::getLayout(void) const
{
	return this->layout;
}


void Charts::ContinuousAxis::setLayout(const std::shared_ptr<Charts::AxisLayout> & value)
{
    newVersion();
	this->layout = value;
}

const std::shared_ptr<Charts::RangeCalculator> & Charts::ContinuousAxis::getRangeCalculator(void) const
{
	return this->rangeCalculator;
}


void Charts::ContinuousAxis::setRangeCalculator(const std::shared_ptr<Charts::RangeCalculator> & value)
{
    newVersion();
	this->rangeCalculator = value;
}

Charts::DataTransform Charts::ContinuousAxis::getRenderValueTransform(void) const
{
    return DataTransform::concatenate(getRenderTransform(), this->valueTransform);
}

double Charts::ContinuousAxis::screenToData(double screen) const
{
    return screenStart + DataTransform::unapply(getRenderValueTransform(), screen);
}

double Charts::ContinuousAxis::dataToScreen(double data) const
{
    return screenStart + DataTransform::apply(getRenderValueTransform(), data);
}

double Charts::ContinuousAxis::dataToLayout(double data) const
{
    return screenStart + DataTransform::apply(getValueTransform(), data);
}

void Charts::ContinuousAxis::resetDataRange(void)
{
    this->rawDataRange = Range::identity();
}

void Charts::ContinuousAxis::calculateDataRange(void)
{
    Range newDataRange = this->rawDataRange;
    if(this->rangeCalculator) {
        newDataRange = this->rangeCalculator->calculateRange(newDataRange);
    }
    if(!Range::positive(newDataRange)) {
#warning hack
        newDataRange.min -= 1.0;
        newDataRange.max += 1.0;
    }
    if(newDataRange != this->dataRange) {
        this->dataRange = newDataRange;
        this->relayoutRequired = true;
    }
}

void Charts::ContinuousAxis::writeDataRange(const Range & range)
{
    if(Range::valid(range)) {
        this->rawDataRange = Range::merge(range, this->rawDataRange);
    } else {
        //TR3DUtils::Log::Warn("Invalid data range");
    }
}

const Charts::Range & Charts::ContinuousAxis::getDataRange(void) const
{
    return this->dataRange;
}

void Charts::ContinuousAxis::relayout(void)
{
    this->relayoutRequired = true;
}

bool Charts::ContinuousAxis::update(const RenderArgs & args)
{
	bool changed = Axis::update(args);
    changed = changed || this->relayoutRequired;
    if(this->relayoutRequired) {
        if(this->layout) {
            valueTransform = this->layout->calculateTransform(getSharedPtr(), dataRange, screenLength, getRenderTransform());
        }
        this->relayoutRequired = false;
    }
    
    const Range newScreenDataRange = DataTransform::unapplyRange(getRenderValueTransform(), Range(0, screenLength));
    
    if(TR_VERIFY(Range::valid(newScreenDataRange))) {
        if(screenDataRange != newScreenDataRange) {
            screenDataRange = newScreenDataRange;
            changed = true;
        }
    }
    return changed;
}

bool Charts::ContinuousAxis::inScreenRange(const double screen) const
{
    const glm::float_t axisStart = getScreenStart();
    const glm::float_t axisLength = getScreenLength();
    return (screen >= axisStart) && (screen <= (axisStart + axisLength));
}

const Charts::Range & Charts::ContinuousAxis::getScreenDataRange(void) const
{
    return screenDataRange;
}

Charts::Range Charts::ContinuousAxis::getLayoutRange(void) const
{
    return DataTransform::applyRange(getValueTransform(), dataRange);
}

Charts::Axis::Tick Charts::ContinuousAxis::createTick(double value, const std::string & label) const
{
    const DataTransform transform = getRenderValueTransform();
    const double position = DataTransform::apply(transform, value);
    return Tick{position, label};
}

#endif
