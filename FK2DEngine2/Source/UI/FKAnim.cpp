/**
*	created:		2013-4-11   21:51
*	filename: 		FKAnim
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
static FK2DEngine2::Anim::Animation::List	g_Animations;
static FK2DEngine2::Anim::Animation::ChildList g_AnimationsListed;
//------------------------------------------------------------------------
void FK2DEngine2::Anim::Add( FK2DEngine2::Controls::Base* control, Animation* animation )
{
	animation->m_Control = control;
	g_Animations[control].push_back( animation );
}
//------------------------------------------------------------------------
void FK2DEngine2::Anim::Cancel( FK2DEngine2::Controls::Base* control )
{
	FK2DEngine2::Anim::Animation::List::iterator iAnimations;

	if ( ( iAnimations = g_Animations.find( control ) ) != g_Animations.end() )
	{
		FK2DEngine2::Anim::Animation::ChildList & ChildAnimationsForControl = iAnimations->second;
		FK2DEngine2::Anim::Animation::ChildList::iterator iAnimationChild = ChildAnimationsForControl.begin();

		if ( iAnimationChild != ChildAnimationsForControl.end() )
		{
			do
			{
				delete( *iAnimationChild );
			}
			while ( ++iAnimationChild != ChildAnimationsForControl.end() );
		}

		g_Animations.erase( iAnimations );
	}
}
//------------------------------------------------------------------------
void FK2DEngine2::Anim::Think()
{
	FK2DEngine2::Anim::Animation::List::iterator it = g_Animations.begin();

	if ( it != g_Animations.end() )
	{
		FK2DEngine2::Anim::Animation::ChildList::iterator itChild;
		FK2DEngine2::Anim::Animation* anim;

		do
		{
			if ( ( itChild = it->second.begin() ) != it->second.end() )
			{
				do
				{
					anim = *itChild;
					anim->Think();

					if ( anim->Finished() )
					{
						itChild = it->second.erase( itChild );
						delete anim;
					}
					else
					{
						++itChild;
					}
				}
				while ( itChild != it->second.end() );
			}
		}
		while ( ++it != g_Animations.end() );
	}
}
//------------------------------------------------------------------------
FK2DEngine2::Anim::TimedAnimation::TimedAnimation( float fLength, float fDelay, float fEase )
{
	m_fStart = Platform::GetTimeInSeconds() + fDelay;
	m_fEnd = m_fStart + fLength;
	m_fEase = fEase;
	m_bStarted = false;
	m_bFinished = false;
}
//------------------------------------------------------------------------
float GetEased( float fTime, float fEase )
{
	if ( fEase < 0 )
	{ return -fTime / 2 * ( cos( 3.14159f * fTime ) - 1 ); }

	return pow( fTime, fEase );
}
//------------------------------------------------------------------------
void FK2DEngine2::Anim::TimedAnimation::Think()
{
	if ( m_bFinished ) { return; }

	float fCurrent = Platform::GetTimeInSeconds();
	float fSecondsIn = fCurrent - m_fStart;

	if ( fSecondsIn < 0.0f ) { return; }

	if ( !m_bStarted )
	{
		m_bStarted = true;
		OnStart();
	}

	float fDelta = fSecondsIn / ( m_fEnd - m_fStart );

	if ( fDelta < 0.0f ) { fDelta = 0.0f; }

	if ( fDelta > 1.0f ) { fDelta = 1.0f; }

	float fEased = GetEased( fDelta, m_fEase );
	Run( fEased );

	if ( fDelta == 1.0f )
	{
		m_bFinished = true;
		OnFinish();
	}
}
//------------------------------------------------------------------------
bool FK2DEngine2::Anim::TimedAnimation::Finished()
{
	return m_bFinished;
}
//------------------------------------------------------------------------