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

#ifndef TRCharts_Impl_LineSeriesImpl_hpp
#define TRCharts_Impl_LineSeriesImpl_hpp

#include <TRCharts/LineSeries.hpp>
#include <TRCharts/ContinuousSeries.hpp>
#include <TRCharts/ScalarDatum.hpp>
#include <TRCharts/Impl/ContinuousSeriesImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{

	
	class LineSeries : public GeneratedLineSeries
	{
	public:
		LineSeries(void);

		virtual ~LineSeries(void);
        
		virtual void setLineStyle(const LineStyle & value);
        
		virtual const LineStyle & getLineStyle(void) const;
        
		virtual const std::shared_ptr<Charts::LineStyleSource> & getLineStyleSource(void) const;
        
		virtual void setLineStyleSource(const std::shared_ptr<Charts::LineStyleSource> & value);
        
		virtual void loadAdditionalData(void);
        
		virtual void preRenderImpl(TR3DUtils::RenderContext & context, const RenderArgs & args);
        
		virtual void render(TR3DUtils::RenderContext & context, const RenderArgs & args) const;
        
        virtual Range getAbscissaRange(void) const;
        
        virtual Range getOrdinateRange(void) const;
        
        virtual glm::float_t getDatumScreenDistanceSquared(const glm::vec2 & position, size_t index, const glm::vec2 & proj) const;
        
        virtual ScalarDatum blendDatums(const ScalarDatum & a, const ScalarDatum & b, const double t) const;
        
        virtual Range getDatumOrdinateRange(const ScalarDatum & datum) const;
        
        virtual void dispose(void);
        
    protected:
        virtual void createVertices(const IndexRange & indexRange, std::vector<glm::vec2> & vertices) const;
        
        virtual void createDatumColors(const IndexRange & indexRange, std::vector<glm::vec4> & colours) const;
        
        virtual void createDatumLineParams(const IndexRange & indexRange, std::vector<glm::vec2> & lineParams) const;
    
    protected:
        std::vector<Charts::LineStyle> datumLineStyles;
        
	private:
        /*// need a new 'block' for each change in line style
        struct RenderBlock
        {
            GLenum primitiveType;
            IndexRange indexRange;
            LineStyle lineStyle;
            
            std::shared_ptr<const TR3DUtils::RenderProgram> program;
            std::shared_ptr<TR3DUtils::RenderVAO> vao;
        };
        
		RenderBlock createBlock(TR3DUtils::RenderContext & context, const RenderArgs & args, const IndexRange & indexRange, const LineStyle & lineStyle);*/
                
		LineStyle lineStyle;
		std::shared_ptr<Charts::LineStyleSource> datumLineStyleSource;
        
        bool useDatumLineStyles;
        std::shared_ptr<const TR3DUtils::RenderProgram> program;
        std::shared_ptr<TR3DUtils::RenderVAO> vao;
	};
}

#endif
