/**
*	created:		2013-4-11   19:44
*	filename: 		FKCanvas
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <set>
#include "FKBase.h"
#include "../FKInputHandler.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT Canvas : public Base
		{
			public:

				typedef Controls::Base BaseClass;

				Canvas( Skin::Base* pSkin );
				virtual ~Canvas();

				// 初始化
				virtual void Initialize() {};

				// 绘制Canvas
				virtual void RenderCanvas();

				// 每帧调用一次，进行输入处理
				virtual void DoThink();

				// 判断 / 设置 一个面板是否需要重新绘制
				virtual bool NeedsRedraw() { return m_bNeedsRedraw; }
				virtual void Redraw() { m_bNeedsRedraw = true; }

				// 内部函数，不建议调用
				virtual void Render( Skin::Base* pRender );

				// 子面板可以不停调用 parent->GetCanvas() 直到最顶层父类面板
				virtual Controls::Canvas* GetCanvas() { return this; }

				virtual void SetScale( float f );
				virtual float Scale() const { return m_fScale; }

				virtual void OnBoundsChanged( FK2DEngine2::Rect oldBounds );

				// 释放全部子面板【注：本函数在析构已调用】
				virtual void ReleaseChildren();

				// 延迟删除
				virtual void AddDelayedDelete( Controls::Base* pControl );
				virtual void ProcessDelayedDeletes();

				Controls::Base*	FirstTab;
				Controls::Base*	NextTab;

				// 输入处理
				virtual bool InputMouseMoved( int x, int y, int deltaX, int deltaY );
				virtual bool InputMouseButton( int iButton, bool bDown );
				virtual bool InputKey( int iKey, bool bDown );
				virtual bool InputCharacter( FK2DEngine2::UnicodeChar chr );
				virtual bool InputMouseWheel( int val );
				virtual bool InputQuit() { return true; };

				// 背景处理
				virtual void SetBackgroundColor( const FK2DEngine2::Color & color ) { m_BackgroundColor = color; }
				virtual void SetDrawBackground( bool bShouldDraw ) { m_bDrawBackground = bShouldDraw; }

			protected:

				bool	m_bNeedsRedraw;
				bool	m_bAnyDelete;
				float	m_fScale;

				Controls::Base::List	m_DeleteList;
				std::set< Controls::Base* > m_DeleteSet;
				friend class Controls::Base;
				void PreDeleteCanvas( Controls::Base* );

				bool			m_bDrawBackground;
				FK2DEngine2::Color		m_BackgroundColor;


		};
	}
}
//------------------------------------------------------------------------