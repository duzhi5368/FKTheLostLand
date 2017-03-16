/**
*	created:		2013-4-23   21:33
*	filename: 		FKFmodSound
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../Depend/fmod/inc/fmod.hpp"

#include "FKISound.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		class CFmodSound : public ISound
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"CFmodSound";
			}
			CFmodSound(const std::wstring & soundName);
			virtual ~CFmodSound();

			virtual ISound::HSOUND getHandle();

			bool loadSample(const std::wstring & fileName,FMOD::System * system);
			bool loadStream(const std::wstring & fileName,FMOD::System * system);
			bool releaseSound();
		private :
			FMOD::Sound * sound;
		};
	}
}
//------------------------------------------------------------------------