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

#ifndef Charts_Impl_FadeInEffectImpl_hpp
#define Charts_Impl_FadeInEffectImpl_hpp

#include <TRCharts/FadeInEffect.hpp>
#include <TRCharts/AnimationEffect.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class Drawable;

	
	class FadeInEffect : public GeneratedFadeInEffect
	{
	public:
		FadeInEffect(void);

		virtual ~FadeInEffect(void);

		virtual const std::vector<std::shared_ptr<Charts::Drawable>> & getDrawableList(void) const;

		virtual void setDrawableList(const std::vector<std::shared_ptr<Charts::Drawable>> & value);
        
		virtual void apply(double position, double duration) const;
        
	private:
		std::vector<std::shared_ptr<Charts::Drawable>> drawableList;
	};
}

#endif