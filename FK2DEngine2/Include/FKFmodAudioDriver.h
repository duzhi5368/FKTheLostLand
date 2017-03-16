/**
*	created:		2013-4-23   21:37
*	filename: 		FKFmodAudioDriver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../Depend/fmod/inc/fmod.hpp"

#include "FKIAudioDriver.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		class CFmodAudioDriver : public IAudioDriver
		{
		public:
			virtual const std::wstring getTypeInfo() const {
				return L"CFmodAudioDriver";
			}

			CFmodAudioDriver();

			virtual ~CFmodAudioDriver();

			virtual bool initDriver();

			virtual bool updateDriver();

			virtual bool shutDriver();

			virtual IChannel * playSound(ISound * sound,float volume = 1.0f,float pan = 0.0f,int loopCount = 0,bool getChannel = false);

			virtual ISound * loadSound(const std::wstring & soundName,const std::wstring & fileName,E_SOUND_TYPE type);

			virtual bool freeSound(const std::wstring & soundName);
			
			virtual bool freeSound(ISound * sound);

		private:
			FMOD::System * system;
		};
	}
}
//------------------------------------------------------------------------