/**
*	created:		2013-4-23   21:36
*	filename: 		FKFmodChannel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../Depend/fmod/inc/fmod.hpp"

#include "FKIChannel.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		class CFmodChannel : public IChannel
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"CFmodChannel";
			}

			CFmodChannel(FMOD::Channel * channel_){
				channel = channel_;
			}

			virtual float getVolume();

			virtual float getPan();

			virtual int getLoopCount();

			virtual void setVolume(float volume);

			virtual void setPan(float pan);

			virtual void setLoopCount(int loopCount);

			virtual bool isPlaying();

			virtual void setPaused(bool pause);

			virtual void stop();

			virtual bool isValid();

			virtual IChannel::HCHANNEL getHandle();
		private:
			FMOD::Channel * channel;

		};
	}
}
//------------------------------------------------------------------------