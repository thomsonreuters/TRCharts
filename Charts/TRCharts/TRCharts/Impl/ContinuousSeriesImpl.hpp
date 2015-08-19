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

#ifndef TRCharts_Impl_ContinuousSeriesImpl_hpp
#define TRCharts_Impl_ContinuousSeriesImpl_hpp

#include <TRCharts/ContinuousSeries.hpp>
#include <TRCharts/DataTransform.hpp>
#include <TRCharts/Series.hpp>
#include <TRCharts/Range.hpp>
#include <TRCharts/Impl/SeriesImpl.hpp>
#include <TRCharts/Impl/Common.hpp>
#include <TRCharts/Impl/RenderArgs.hpp>

#include <TR3DUtils/RenderContext.hpp>

namespace Charts
{
	template <typename T> class ContinuousDataSource;
    class ColorSource;
	class ContinuousAxis;
    
	template <typename T>
	class ContinuousSeries : public GeneratedContinuousSeries<T>
	{
	public:
		ContinuousSeries(void);
        
		virtual ~ContinuousSeries(void);
        
        virtual void dispose(void);
        
		virtual const std::shared_ptr<Charts::ContinuousAxis> & getAbscissaAxis(void) const;
        
		virtual void setAbscissaAxis(const std::shared_ptr<Charts::ContinuousAxis> & value);
        
		virtual const std::shared_ptr<Charts::ContinuousDataSource<T>> & getDataSource(void) const;
        
		virtual void setDataSource(const std::shared_ptr<Charts::ContinuousDataSource<T>> & value);
        
		virtual const std::shared_ptr<Charts::ColorSource> & getColorSource(void) const;
        
		virtual void setColorSource(const std::shared_ptr<Charts::ColorSource> & value);
        
        // need to intercept this call and set dirty if a color source is active
		virtual void setColor(const Charts::Color & color);
        
        virtual DataTransform calculateStorageTransform(const Charts::Range & dataRange) const;
        
		virtual void loadData(void);
        
        // called when data has just been loaded based on dirty ranges, should override in subclasses
		virtual void loadAdditionalData(void);
        
        virtual void validateData(const IndexRange & indexRange);
        
        virtual void writeDataRangeToAxes(void) const;
        
		virtual bool update(const RenderArgs & args);
                
		virtual void preRender(TR3DUtils::RenderContext & context, const RenderArgs & args);
        
		virtual void preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args) = 0;
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const = 0;
        
		virtual Charts::Coordinates screenPositionToValue(const Charts::Point & screenPosition) const;
        
		virtual Charts::Point valueToScreenPosition(const Charts::Coordinates & value) const;
        
		virtual T getDatum(long index) const;
        
		virtual T interpolateDatum(double abscissa) const;
        
		virtual long getIndexBeforeAbscissaValue(double abscissa, bool includeEqual) const;
        
		virtual long getIndexAfterAbscissaValue(double abscissa, bool includeEqual) const;
        
		virtual long getIndexNearestAbscissaValue(double abscissa) const;
        
		virtual long getIndexNearestScreenPosition(const Charts::Point & screenPosition) const;
        
		virtual double getDatumSquaredDistanceToScreenPosition(long index, const Charts::Point & screenPosition) const;
        
		virtual glm::dvec2 screenToDataRaw(const glm::vec2 & screen) const;
        
		virtual glm::vec2 dataToScreenRaw(const glm::dvec2 & data) const;
        
        virtual Range getAbscissaRange(void) const = 0;
        
        virtual Range getOrdinateRange(void) const = 0;
        
        virtual glm::vec2 createVertex(double abscissa, double ordinate) const;
        
        virtual DataTransform getAbscissaRenderTransform(void) const;
        
        virtual DataTransform getOrdinateRenderTransform(void) const;
        
        virtual glm::vec2 getRenderValueScale(void) const;
        
        virtual glm::vec2 getRenderValueOffset(void) const;
        
        virtual glm::vec2 getRenderOffset(void) const;
        
        virtual const DataTransform & getAbscissaStorageTransform(void) const;
        
        virtual const DataTransform & getOrdinateStorageTransform(void) const;
        
        virtual glm::float_t getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const = 0;
        
        virtual T blendDatums(const T & a, const T & b, const double t) const = 0;
        
        virtual Range getDatumOrdinateRange(const T & datum) const = 0;
        
		virtual Charts::Range getOrdinateRangeWithinAbscissaRange(const Charts::Range & abscissaRange) const;
        
	protected:
        IndexRange dataSourceIndexRange;
        std::vector<T> data;
        bool useDatumColors;
        std::vector<glm::vec4> datumColors;
        glm::float_t screenHeight;
        glm::float_t abscissaScreenStart;
        glm::vec2 abscissaAxisDirection;
        glm::float_t ordinateScreenStart;
        glm::vec2 ordinateAxisDirection;
        DataTransform abscissaStorageTransform;
        DataTransform ordinateStorageTransform;
        size_t selectedIndex;
        
        // TODO make accessible?
        bool validateDataOnLoad;
        
	private:
		std::shared_ptr<Charts::ContinuousAxis> abscissaAxis;
		std::shared_ptr<Charts::ContinuousDataSource<T>> dataSource;
		std::shared_ptr<Charts::ColorSource> colorSource;
        
        Range abscissaRange;
        Range ordinateRange;
        bool wasDirty;
        bool needPrerender;
	};
}

#endif

#include <TRCharts/Impl/ContinuousSeriesImpl.impl.hpp>
