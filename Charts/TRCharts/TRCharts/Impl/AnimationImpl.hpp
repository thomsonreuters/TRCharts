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

#ifndef Charts_Impl_AnimationImpl_hpp
#define Charts_Impl_AnimationImpl_hpp

#include <TRCharts/Animation.hpp>
#include <TRCharts/Attachable.hpp>
#include <TRCharts/Impl/AttachableImpl.hpp>
#include <TRCharts/Impl/Common.hpp>

namespace Charts
{
	class AnimationEffect;
	class AnimationDelegate;

	
	class Animation : public GeneratedAnimation
	{
	public:
        enum State
        {
            UNSTARTED,
            STARTED,
            CANCEL,
            CANCELLED,
            COMPLETED,
            REMOVE
        };
        
		Animation(void);

		virtual ~Animation(void);
        
		virtual void attach(void);
        
		virtual double getDuration(void) const;

		virtual void setDuration(double value);

		virtual double getPosition(void) const;

		virtual void setPosition(double value);

		virtual const std::vector<std::shared_ptr<Charts::AnimationEffect>> & getEffectList(void) const;

		virtual void setEffectList(const std::vector<std::shared_ptr<Charts::AnimationEffect>> & value);

		virtual const std::shared_ptr<Charts::AnimationDelegate> & getDelegate(void) const;

		virtual void setDelegate(const std::shared_ptr<Charts::AnimationDelegate> & value);
        
		virtual void restart(void);
        
		virtual void complete(void);
        
		virtual void cancel(void);
        
        virtual void update(double elapsedSeconds);
        
        virtual void postUpdate(void);
        
        virtual bool doRemove(void) const;

	private:
		double duration;
		double position;
		std::vector<std::shared_ptr<Charts::AnimationEffect>> effectList;
		std::shared_ptr<Charts::AnimationDelegate> delegate;
        
		State state;
	};
}

#endif