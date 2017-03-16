/**
*	created:		2013-4-23   21:43
*	filename: 		FKFmodChannel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKFmodChannel.h"
//------------------------------------------------------------------------
#pragma comment (lib,"fmodex_vc.lib")
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		float CFmodChannel::getVolume()
		{
			float ret;
			FMOD_RESULT result = channel->getVolume(&ret);
			if (result != FMOD_OK)
				return 0.0f;
			return ret;
		}

		float CFmodChannel::getPan()
		{
			float ret ;
			FMOD_RESULT result = channel->getPan(&ret);
			if (result != FMOD_OK)
				return 0.0f;
			return ret;
		}

		int CFmodChannel::getLoopCount()
		{
			int ret;
			FMOD_RESULT result = channel->getLoopCount(&ret);
			if (result != FMOD_OK)
				return -1;
			return ret;
		}

		void CFmodChannel::setVolume(float volume)
		{
			if (volume > 1.0f) volume = 1.0f;
			if (volume < 0.0f) volume = 0.0f;
			channel->setVolume(volume);
		}

		void CFmodChannel::setPan(float pan)
		{
			if (pan > 1.0f) pan = 1.0f;
			if (pan < -1.0f) pan = -1.0f;
			channel->setPan(pan);
		}

		void CFmodChannel::setLoopCount(int loopCount)
		{
			channel->setLoopCount(loopCount);
		}

		bool CFmodChannel::isPlaying()
		{
			bool ret ;
			FMOD_RESULT result =  channel->isPlaying(&ret);
			if (result != FMOD_OK)
				return false;
			return ret;
		}

		void CFmodChannel::setPaused(bool pause)
		{
			channel->setPaused(pause);
		}

		void CFmodChannel::stop()
		{
			channel->stop();
		}

		bool CFmodChannel::isValid()
		{
			bool playing;
			FMOD_RESULT result = channel->isPlaying(&playing);
			if (result == FMOD_ERR_INVALID_HANDLE)
				return true;
			return false;
		}

		IChannel::HCHANNEL CFmodChannel::getHandle()
		{
			return (IChannel::HCHANNEL)(channel);
		}
	}
}
//------------------------------------------------------------------------