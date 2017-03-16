/**
*	created:		2013-4-11   21:47
*	filename: 		FKAnim
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKUIOutSideHead.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Anim
	{
		//------------------------------------------------------------------------
		class FK_EXPORT Animation
		{
			public:

				typedef std::list<Animation*> ChildList;
				typedef std::map< FK2DEngine2::Controls::Base*, ChildList > List;

				virtual void Think() = 0;
				virtual bool Finished() { return false; }

				virtual ~Animation() {}

				FK2DEngine2::Controls::Base*	m_Control;
		};
		//------------------------------------------------------------------------
		FK_EXPORT void Add( FK2DEngine2::Controls::Base* control, Animation* animation );
		FK_EXPORT void Cancel( FK2DEngine2::Controls::Base* control );
		FK_EXPORT void Think();
		//------------------------------------------------------------------------
		// ¶¨Ê±¶¯»­
		class FK_EXPORT TimedAnimation : public Animation
		{
			public:

				TimedAnimation( float fLength, float fDelay = 0.0f, float fEase = -1.0f );

				virtual void Think();
				virtual bool Finished();

				virtual void OnStart() {}
				virtual void Run( float /*delta*/ ) {}
				virtual void OnFinish() {}

			protected:

				bool	m_bStarted;
				bool	m_bFinished;
				float	m_fStart;
				float	m_fEnd;
				float	m_fEase;
		};
		//------------------------------------------------------------------------
		namespace Size
		{
			class FK_EXPORT Height : public TimedAnimation
			{
				public:

					Height( int iStartSize, int iEndSize, float fLength, bool bHide = false, float fDelay = 0.0f, float fEase = -1.0f ) : TimedAnimation( fLength, fDelay, fEase )
					{
						m_iStartSize = iStartSize;
						m_iDelta = iEndSize - m_iStartSize;
						m_bHide = bHide;
					}

					virtual void OnStart() { m_Control->SetHeight( m_iStartSize ); }
					virtual void Run( float delta ) { m_Control->SetHeight( m_iStartSize + ( ( ( float ) m_iDelta ) * delta ) ); }
					virtual void OnFinish() { m_Control->SetHeight( m_iStartSize + m_iDelta ); m_Control->SetHidden( m_bHide ); }

				protected:

					int		m_iStartSize;
					int		m_iDelta;
					bool	m_bHide;
			};
			
			class Width : public TimedAnimation
			{
				public:

					Width( int iStartSize, int iEndSize, float fLength, bool bHide = false, float fDelay = 0.0f, float fEase = -1.0f ) : TimedAnimation( fLength, fDelay, fEase )
					{
						m_iStartSize = iStartSize;
						m_iDelta = iEndSize - m_iStartSize;
						m_bHide = bHide;
					}

					virtual void OnStart() { m_Control->SetWidth( m_iStartSize ); }
					virtual void Run( float delta ) { m_Control->SetWidth( m_iStartSize + ( ( ( float ) m_iDelta ) * delta ) ); }
					virtual void OnFinish() { m_Control->SetWidth( m_iStartSize + m_iDelta ); m_Control->SetHidden( m_bHide ); }

				protected:

					int		m_iStartSize;
					int		m_iDelta;
					bool	m_bHide;
			};
		}
		//------------------------------------------------------------------------
		namespace Pos
		{
			class FK_EXPORT X : public Anim::TimedAnimation
			{
				public:

					X( int iStartSize, int iEndSize, float fLength, bool bHide = false, float fDelay = 0.0f, float fEase = 1.0f ) : TimedAnimation( fLength, fDelay, fEase )
					{
						m_iStartSize = iStartSize;
						m_iDelta = iEndSize - m_iStartSize;
						m_bHide = bHide;
					}

					virtual void OnStart() { m_Control->SetPos( m_iStartSize, m_Control->GetPos().y ); }
					virtual void Run( float delta ) { m_Control->SetPos( m_iStartSize + ( ( ( float ) m_iDelta ) * delta ), m_Control->GetPos().y ); }
					virtual void OnFinish() { m_Control->SetPos( m_iStartSize + m_iDelta, m_Control->GetPos().y ); m_Control->SetHidden( m_bHide ); }

				protected:

					int		m_iStartSize;
					int		m_iDelta;
					bool	m_bHide;
			};
			
			class Y : public Anim::TimedAnimation
			{
				public:

					Y( int iStartSize, int iEndSize, float fLength, bool bHide = false, float fDelay = 0.0f, float fEase = 1.0f ) : TimedAnimation( fLength, fDelay, fEase )
					{
						m_iStartSize = iStartSize;
						m_iDelta = iEndSize - m_iStartSize;
						m_bHide = bHide;
					}

					virtual void OnStart() { m_Control->SetPos( m_Control->GetPos().x, m_iStartSize ); }
					virtual void Run( float delta ) { m_Control->SetPos( m_Control->GetPos().x, m_iStartSize + ( ( ( float ) m_iDelta ) * delta ) ); }
					virtual void OnFinish() { m_Control->SetPos( m_Control->GetPos().x, m_iStartSize + m_iDelta ); m_Control->SetHidden( m_bHide ); }

				protected:

					int		m_iStartSize;
					int		m_iDelta;
					bool	m_bHide;
			};
		}
		//------------------------------------------------------------------------
		namespace Tools
		{
			class Remove : public TimedAnimation
			{
				public:

					Remove( float fDelay = 0.0f ) : TimedAnimation( 0.0f, fDelay ) {}
					virtual void OnFinish() { m_Control->DelayedDelete(); }
			};
		}
	}
}
//------------------------------------------------------------------------