/**
*	created:		2013-4-23   20:45
*	filename: 		FKITimer
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIBase.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace system
	{
		const float FPS_DEFAULT = 60.0f;
		const float FPS_LOWER_LIMIT = 10.0f;
		const float FPS_UPPER_LIMIT = 200.0f;
		
		class ITimer : public FK2DEngine2::core::IBase
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"ITimer";
			}
			void initFrameRate(float mrate = FPS_DEFAULT){
				if ((mrate < FPS_LOWER_LIMIT) ||  (mrate > FPS_UPPER_LIMIT)) 
					mrate = FPS_DEFAULT;
				framecount = 0;
				rate = mrate;
				rateticks =  (float)(1000.0 / mrate);
				lastticks = getTime();
			}
			float setFrameRate(float mrate){
				if ((mrate >= FPS_LOWER_LIMIT) && (mrate <= FPS_UPPER_LIMIT)) 
				{
					framecount = 0;
					float retrate = rate; 
					rate = mrate;
					rateticks = (float)(1000.0 /  mrate);
					return retrate;
				} 
				return 0;
			}
			float getFrameRate(){
				return rate;
			}
			void frameDelay(){
				unsigned long current_ticks;
				unsigned long target_ticks;
				unsigned long the_delay;

				framecount++;

				current_ticks = getTime();
				target_ticks = lastticks + (unsigned long) ((float) framecount * rateticks);

				if (current_ticks <= target_ticks) 
				{
					the_delay = target_ticks - current_ticks;
					delay(the_delay);
				} 
				else 
				{
					framecount = 0;
					lastticks = getTime();
				}
			}

		protected :
			virtual unsigned long getTime() = 0;
			virtual void delay(unsigned long delayTime) = 0;
		private:
			unsigned long framecount;
			float rateticks;
			unsigned long lastticks;
			float rate;
		};
	}
}
//------------------------------------------------------------------------ 