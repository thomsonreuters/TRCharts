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

#ifndef TRCharts_Impl_ContinuousSeriesImpl_cpp
#define TRCharts_Impl_ContinuousSeriesImpl_cpp

#include <TRCharts/Impl/ContinuousSeriesImpl.hpp>
#include <TRCharts/ContinuousDataSource.hpp>
#include <TRCharts/ColorSource.hpp>
#include <TRCharts/ContinuousAxis.hpp>
#include <TRCharts/Impl/ContinuousAxisImpl.hpp>
#include <TRCharts/Impl/Utils.hpp>

#include <TR3DUtils/Log.hpp>
#include <TR3DUtils/Utils.hpp>

#include <limits>
#include <algorithm>

template <typename T>
Charts::ContinuousSeries<T>::ContinuousSeries(void)
:wasDirty(true), needPrerender(true), abscissaStorageTransform(0.0, 1.0), ordinateStorageTransform(0.0, 1.0), useDatumColors(false), selectedIndex(Series::NO_SELECTION), validateDataOnLoad(true), dataSourceIndexRange(0, 0), abscissaRange(), ordinateRange()
{
}
 
template <typename T>
Charts::ContinuousSeries<T>::~ContinuousSeries(void)
{
}

template <typename T>
void Charts::ContinuousSeries<T>::dispose(void)
{
    this->needPrerender = true;
}

template <typename T>
const std::shared_ptr<Charts::ContinuousAxis> & Charts::ContinuousSeries<T>::getAbscissaAxis(void) const
{
	return this->abscissaAxis;
}

template <typename T>
void Charts::ContinuousSeries<T>::setAbscissaAxis(const std::shared_ptr<Charts::ContinuousAxis> & value)
{
	this->abscissaAxis = value;
	this->markDirty();
}

template <typename T>
const std::shared_ptr<Charts::ContinuousDataSource<T>> & Charts::ContinuousSeries<T>::getDataSource(void) const
{
	return this->dataSource;
}

template <typename T>
void Charts::ContinuousSeries<T>::setDataSource(const std::shared_ptr<Charts::ContinuousDataSource<T>> & value)
{
	this->dataSource = value;
	this->markDirty();
}

template <typename T>
const std::shared_ptr<Charts::ColorSource> & Charts::ContinuousSeries<T>::getColorSource(void) const
{
	return this->colorSource;
}

template <typename T>
void Charts::ContinuousSeries<T>::setColorSource(const std::shared_ptr<Charts::ColorSource> & value)
{
	this->colorSource = value;
	this->markDirty();
}

template <typename T>
void Charts::ContinuousSeries<T>::setColor(const Charts::Color & color)
{
    Series::setColor(color);
    if(this->colorSource) {
        this->markDirty();
    }
}

template <typename T>
Charts::DataTransform Charts::ContinuousSeries<T>::calculateStorageTransform(const Charts::Range & dataRange) const
{
    const double offset = -dataRange.min;
    const double scale = 1.0;//glm::max(1.0, Range::length(dataRange)) * 100.0;
    return DataTransform(offset, scale);
}

template <typename T>
void Charts::ContinuousSeries<T>::loadData(void)
{
	if(!this->dirtyRanges.empty()) {
        // TODO should merge dirty ranges that overlap
		if(this->dataSource) {
			dataSourceIndexRange = this->dataSource->getDatumRange(this->getSharedPtr());
            if(!IndexRange::valid(dataSourceIndexRange)) {
                throw std::logic_error("Invalid datum index range");
            }
            for(const IndexRange & rawRange : this->dirtyRanges) {
                const IndexRange indexRange = IndexRange::clamp(rawRange, dataSourceIndexRange);
                if(size_t(indexRange.end) != data.size()) {
                    data.resize(std::max(indexRange.end, dataSourceIndexRange.end));
                }
                const size_t numDatums = indexRange.end - indexRange.begin;
                TR3DUtils::Log::Debug("Loading %zu datums", numDatums);
                const std::vector<T> rawData = this->dataSource->getDatums(this->getSharedPtr(), indexRange);
                const size_t copyDatumCount = std::min(numDatums, rawData.size());
                // explicitly allowed to return more/less data than requested.
                std::copy(rawData.begin(), rawData.begin() + copyDatumCount, data.begin() + indexRange.begin);
                if(validateDataOnLoad) {
                    // TODO: test that index range merge works, else this wont.
                    IndexRange validateIndexRange(indexRange.begin, indexRange.begin + numDatums);
                    if(validateIndexRange.begin > 0) {
                        --validateIndexRange.begin;
                    }
                    if(size_t(validateIndexRange.end) < data.size()) {
                        ++validateIndexRange.end;
                    }
                    validateData(validateIndexRange);
                }
            }
            const Range abscissaRange = getAbscissaRange();
            const Range ordinateRange = getOrdinateRange();
			TR3DUtils::Log::Debug("- Abscissa range: %f %f", abscissaRange.min, abscissaRange.max);
			TR3DUtils::Log::Debug("- Ordinate range: %f %f", ordinateRange.min, ordinateRange.max);
            abscissaStorageTransform = calculateStorageTransform(abscissaRange);
            ordinateStorageTransform = calculateStorageTransform(ordinateRange);
            if(this->colorSource) {
                for(const IndexRange & rawRange : this->dirtyRanges) {
                    const IndexRange indexRange = IndexRange::clamp(rawRange, dataSourceIndexRange);
                    if(size_t(indexRange.end) != datumColors.size()) {
                        datumColors.resize(std::max(indexRange.end, dataSourceIndexRange.end));
                    }
                    const size_t numDatums = indexRange.end - indexRange.begin;
                    TR3DUtils::Log::Debug("Loading %zu datum colors", numDatums);
                    const std::vector<Color> rawDatumColors = this->colorSource->getColors(this->getSharedPtr(), indexRange, this->getColor());
                    const size_t copyDatumCount = std::min(numDatums, rawDatumColors.size());
                    // explicitly allowed to return more/less data than requested.
                    for(size_t i = 0; i != copyDatumCount; ++i) {
                        datumColors[i + indexRange.begin] = Utils::colorToVec4(rawDatumColors[i]);
                    }
                }
                useDatumColors = true;
            } else {
                datumColors.clear();
                useDatumColors = false;
            }
		} else {
            dataSourceIndexRange = IndexRange(0,0);
            data.clear();
            datumColors.clear();
        }
        loadAdditionalData();
        this->wasDirty = true;
        this->abscissaRange = getAbscissaRange();
        this->ordinateRange = getOrdinateRange();
	}
	this->dirtyRanges.clear();
}

template <typename T>
void Charts::ContinuousSeries<T>::validateData(const IndexRange & indexRange)
{
    const auto beginIter = data.begin() + indexRange.begin;
    const auto endIter = data.begin() + indexRange.end;
    double lastAbscissa = -std::numeric_limits<double>::max();
    for(auto iter = beginIter; iter != endIter; ++iter) {
        const double abscissa = iter->abscissa;
        if(abscissa < lastAbscissa) {
            throw std::logic_error("Abscissa values must be monotonically increasing");
        }
        lastAbscissa = abscissa;
    }
}

template <typename T>
void Charts::ContinuousSeries<T>::loadAdditionalData(void)
{
    
}

template <typename T>
void Charts::ContinuousSeries<T>::writeDataRangeToAxes(void) const
{
    if(abscissaAxis) {
        abscissaAxis->writeDataRange(abscissaRange);
    }
    if(const std::shared_ptr<ContinuousAxis> & ordinateAxis = this->getOrdinateAxis()) {
        ordinateAxis->writeDataRange(ordinateRange);
    }
}

template <typename T>
bool Charts::ContinuousSeries<T>::update(const RenderArgs & args)
{
    bool changed = this->wasDirty || this->versionChanged();
    screenHeight = args.screenSize.y;
	if(abscissaAxis) {
		abscissaScreenStart = abscissaAxis->getScreenStart();
		//abscissaScreenLength = abscissaAxis->getScreenLength();
		abscissaAxisDirection = abscissaAxis->getAxisDirection();
	} else {
        TR3DUtils::Log::Error("No abscissa axis specified");
    }
	if(const std::shared_ptr<ContinuousAxis> & ordinateAxis = this->getOrdinateAxis()) {
		ordinateScreenStart = ordinateAxis->getScreenStart();
		//ordinateScreenLength = ordinateAxis->getScreenLength();
		ordinateAxisDirection = ordinateAxis->getAxisDirection();
	} else {
        TR3DUtils::Log::Error("No ordinate axis specified");
    }
    this->markVersion();
    return changed;
}

template <typename T>
void Charts::ContinuousSeries<T>::preRender(TR3DUtils::RenderContext & context, const RenderArgs & args)
{
    //TR_ASSERT(this->isEnabled());
    if(this->wasDirty || needPrerender) {
        this->preRenderImpl(context, args);
    }
    this->wasDirty = false;
    this->needPrerender = false;
}

template <typename T>
glm::vec2 Charts::ContinuousSeries<T>::createVertex(double abscissa, double ordinate) const
{
    return glm::vec2(DataTransform::apply(abscissaStorageTransform, abscissa), DataTransform::apply(ordinateStorageTransform, ordinate));
}

template <typename T>
Charts::DataTransform Charts::ContinuousSeries<T>::getAbscissaRenderTransform(void) const
{
    const auto & abscissaAxis = this->getAbscissaAxis();
    if(TR_VERIFY(abscissaAxis)) {
        return DataTransform::concatenate(abscissaAxis->getRenderValueTransform(), DataTransform::invert(abscissaStorageTransform));
    } else {
        return DataTransform();
    }
}

template <typename T>
Charts::DataTransform Charts::ContinuousSeries<T>::getOrdinateRenderTransform(void) const
{
    const auto & ordinateAxis = this->getOrdinateAxis();
    if(TR_VERIFY(ordinateAxis)) {
        return DataTransform::concatenate(ordinateAxis->getRenderValueTransform(), DataTransform::invert(ordinateStorageTransform));
    } else {
        return DataTransform();
    }
}

template <typename T>
glm::vec2 Charts::ContinuousSeries<T>::getRenderValueScale(void) const
{
    const Charts::DataTransform abscissaTransform = getAbscissaRenderTransform();
    const Charts::DataTransform ordinateTransform = getOrdinateRenderTransform();
    return glm::vec2(abscissaTransform.scale, ordinateTransform.scale);
}

template <typename T>
glm::vec2 Charts::ContinuousSeries<T>::getRenderValueOffset(void) const
{
    const Charts::DataTransform abscissaTransform = getAbscissaRenderTransform();
    const Charts::DataTransform ordinateTransform = getOrdinateRenderTransform();
    return glm::vec2(abscissaTransform.offset, ordinateTransform.offset);
}

template <typename T>
glm::vec2 Charts::ContinuousSeries<T>::getRenderOffset(void) const
{
    const glm::vec2 abscissaScreenOffset = abscissaAxisDirection * abscissaScreenStart;
    const glm::vec2 ordinateScreenOffset = ordinateAxisDirection * ordinateScreenStart;
    return abscissaScreenOffset + ordinateScreenOffset;
}

template <typename T>
const Charts::DataTransform & Charts::ContinuousSeries<T>::getAbscissaStorageTransform(void) const
{
    return abscissaStorageTransform;
}

template <typename T>
const Charts::DataTransform & Charts::ContinuousSeries<T>::getOrdinateStorageTransform(void) const
{
    return ordinateStorageTransform;
}

template <typename T>
Charts::Coordinates Charts::ContinuousSeries<T>::screenPositionToValue(const Charts::Point & screenPosition) const
{
    return Utils::dvec2ToCoordinates(screenToDataRaw(Utils::pointToVec2Flipped(screenPosition, screenHeight)));
}

template <typename T>
Charts::Point Charts::ContinuousSeries<T>::valueToScreenPosition(const Charts::Coordinates & value) const
{
    return Utils::vec2ToPointFlipped(dataToScreenRaw(Utils::coordinatesToDVec2(value)), screenHeight);
}

template <typename T>
T Charts::ContinuousSeries<T>::getDatum(long index) const
{
    if(TR_VERIFY(index >= 0) && (size_t(index) < data.size())) {
        return data[index];
    } else {
        throw std::logic_error("Index out of range");
    }
}

template <typename T>
T Charts::ContinuousSeries<T>::interpolateDatum(double abscissa) const
{
    if(!data.empty()) {
        const T firstDatum = data.front();
        if(firstDatum.abscissa >= abscissa) {
            return firstDatum;
        } else {
            T previousDatum;
            for(const auto & datum : data) {
                if(datum.abscissa == abscissa) {
                    // avoid interpolating exact matches
                    return datum;
                } else if(datum.abscissa > abscissa) {
                    return blendDatums(previousDatum, datum, (abscissa - previousDatum.abscissa) / (datum.abscissa - previousDatum.abscissa));
                }
                previousDatum = datum;
            }
            return previousDatum;
        }
    } else {
        return T();
    }
}

namespace
{
    template <typename T>
    bool lowerCompareLeq(const T & t, double abscissa)
    {
        return t.abscissa <= abscissa;
    }
    
    template <typename T>
    bool lowerCompareLe(const T & t, double abscissa)
    {
        return t.abscissa < abscissa;
    }
    
    template <typename T>
    bool upperCompareLeq(double abscissa, const T & t)
    {
        return abscissa <= t.abscissa;
    }
    
    template <typename T>
    bool upperCompareLe(double abscissa, const T & t)
    {
        return abscissa < t.abscissa;
    }
}

// TODO: unit tests

template <typename T>
long Charts::ContinuousSeries<T>::getIndexBeforeAbscissaValue(double abscissa, bool includeEqual) const
{
    if(data.empty()) {
        return Series::NO_SELECTION;
    } else {
        auto iter = std::lower_bound(data.begin(), data.end(), abscissa, includeEqual ? ::lowerCompareLeq<T> : ::lowerCompareLe<T>);
        if(iter == data.begin()) {
            return Series::NO_SELECTION;
        } else {
            return (iter - data.begin()) - 1;
        }
    }
}

// TODO: unit tests

template <typename T>
long Charts::ContinuousSeries<T>::getIndexAfterAbscissaValue(double abscissa, bool includeEqual) const
{
    TR_ASSERT(!"Needs testing");
    if(data.empty()) {
        return Series::NO_SELECTION;
    } else {
        const auto iter = std::upper_bound(data.begin(), data.end(), abscissa, includeEqual ? ::upperCompareLeq<T> : ::upperCompareLe<T>);
        if(iter == data.end()) {
            return Series::NO_SELECTION;
        } else {
            return (iter - data.begin());
        }
    }
}

template <typename T>
long Charts::ContinuousSeries<T>::getIndexNearestAbscissaValue(double abscissa) const
{
    if(data.empty()) {
        return Series::NO_SELECTION;
    } else {
        const auto last = std::lower_bound(data.begin(), data.end(), abscissa, ::lowerCompareLe<T>);
        if(last == data.begin()) {
            return 0;
        } else if(last == data.end()) {
            return (data.size() - 1);
        } else {
            const auto first = last - 1;
            if(glm::abs(first->abscissa - abscissa) < glm::abs(last->abscissa - abscissa)) {
                return (first - data.begin());
            } else {
                return (last - data.begin());
            }
        }
    }
}

template <typename T>
long Charts::ContinuousSeries<T>::getIndexNearestScreenPosition(const Charts::Point & position) const
{
    const glm::vec2 flippedPosition = Utils::pointToVec2Flipped(position, screenHeight);
    long closestIndex = Series::NO_SELECTION;
    double closestDistanceSquared = std::numeric_limits<glm::float_t>::max();
    for(size_t i = 0; i != data.size(); ++i) {
        const glm::float_t distanceSquared = getDatumScreenDistanceSquared(flippedPosition, i, glm::vec2(1.0));
        if(distanceSquared < closestDistanceSquared) {
            closestIndex = i;
            closestDistanceSquared = distanceSquared;
        }
    }
    return closestIndex;
}

// TODO: tidy up
template <typename T>
double Charts::ContinuousSeries<T>::getDatumSquaredDistanceToScreenPosition(long index, const Charts::Point & screenPosition) const
{
    if(TR_VERIFY(index >= 0) && (size_t(index) < data.size())) {
        const glm::vec2 flippedPosition = Utils::pointToVec2Flipped(screenPosition, screenHeight);
        return getDatumScreenDistanceSquared(flippedPosition, index, glm::vec2(1.f));
    } else {
        throw std::logic_error("Index out of range");
    }
}

template <typename T>
glm::dvec2 Charts::ContinuousSeries<T>::screenToDataRaw(const glm::vec2 & screen) const
{
    glm::dvec2 result;
    if(TR_VERIFY(abscissaAxis)) {
        result.x = abscissaAxis->screenToData(glm::dot(screen, abscissaAxis->getAxisDirection()));
    }
	if(const std::shared_ptr<ContinuousAxis> & ordinateAxis = TR_VERIFY(this->getOrdinateAxis())) {
        result.y = ordinateAxis->screenToData(glm::dot(screen, ordinateAxis->getAxisDirection()));
    }
    return result;
}

template <typename T>
glm::vec2 Charts::ContinuousSeries<T>::dataToScreenRaw(const glm::dvec2 & data) const
{
    glm::vec2 result;
    if(TR_VERIFY(abscissaAxis)) {
        result += glm::float_t(abscissaAxis->dataToScreen(data.x)) * abscissaAxis->getAxisDirection();
    }
	if(const std::shared_ptr<ContinuousAxis> & ordinateAxis = TR_VERIFY(this->getOrdinateAxis())) {
        result += glm::float_t(ordinateAxis->dataToScreen(data.y)) * ordinateAxis->getAxisDirection();
    }
    return result;
}

template <typename T>
Charts::Range Charts::ContinuousSeries<T>::getOrdinateRangeWithinAbscissaRange(const Charts::Range & abscissaRange) const
{
    Range result = Range::identity();
    for(const auto & datum : data) {
        if(datum.abscissa >= abscissaRange.min && datum.abscissa <= abscissaRange.max) {
            result = Range::merge(result, getDatumOrdinateRange(datum));
        }
    }
    result = Range::merge(result, getDatumOrdinateRange(interpolateDatum(abscissaRange.min)));
    result = Range::merge(result, getDatumOrdinateRange(interpolateDatum(abscissaRange.max)));
    return result;
}

#endif
