/**
*	created:		2013-5-28   16:36
*	filename: 		BaseWnd
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <Windows.h>
#include <windowsx.h>
//------------------------------------------------------------------------
class CEGBaseWnd;
//------------------------------------------------------------------------
class CEGWndMsgFilter
{
public:
	//	如果需要处理某条消息,或者禁止缺省的消息处理,请返回TRUE
	virtual BOOL	FilterMessage( CEGBaseWnd * pWnd, UINT	uMsg, WPARAM wParam, LPARAM lParam ) = 0;
};
//------------------------------------------------------------------------
// 确定窗口
BOOL ConfirmBox( HWND hWnd, CHAR * pszCaption, CHAR * pszText );
//------------------------------------------------------------------------
class CEGBaseWnd
{
public:
	CEGBaseWnd(void);
	virtual ~CEGBaseWnd(void);
	// 如果需要处理某条消息,或者禁止缺省的消息处理,请返回TRUE
	virtual BOOL		OnMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}
	// 子类继承回调函数
	virtual VOID		OnCreate( HWND hWnd ){}
	virtual BOOL		OnDrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct ){ return FALSE;}
	virtual VOID		OnNotify( NMHDR * pnmhdr ){}
public:
	BOOL				Show()										{ return ShowWindow( m_hWnd, SW_SHOW );}
	BOOL				Hide()										{ return ShowWindow( m_hWnd, SW_HIDE );}
	BOOL				Enable()									{ return EnableWindow( m_hWnd, TRUE );}
	BOOL				Disable()									{ return EnableWindow( m_hWnd, FALSE ); }
	HWND				SetFocus()									{ return ::SetFocus( m_hWnd ); }
	BOOL				IsVisible()									{ return IsWindowVisible( m_hWnd ); }
	BOOL				SetText(const CHAR * pText )				{ return SetWindowText(m_hWnd, pText );}
	int					GetText(CHAR * pText, int length )			{ return GetWindowText( m_hWnd, pText, length );}
	VOID				SetId(UINT id)								{ m_Id = id; SetWindowLong( m_hWnd, GWL_ID, (LONG)id);}
	UINT				GetId()										{ return m_Id;}
	HWND				GetHandle()									{ return m_hWnd;}
	CEGWndMsgFilter *	GetMsgFilter()								{ return m_pMsgFilter;}
	VOID				SetMsgFilter( CEGWndMsgFilter * pMsgFilter ){ m_pMsgFilter = pMsgFilter;}
	DWORD				GetStyle()									{ return (DWORD)GetWindowLong( m_hWnd, GWL_STYLE);}
	HDC					GetDC()										{ return ::GetDC( m_hWnd );}
	BOOL				ReleaseDC( HDC dc )							{ return ::ReleaseDC( m_hWnd, dc );}
	HFONT				GetFont()									{ return (HFONT)SendMessage( m_hWnd, WM_GETFONT, 0, 0 ); }
	VOID				SetFont( HFONT	hFont )
	{ 
		SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE );
		HWND	hWnd = GetWindow( m_hWnd, GW_CHILD );
		while( hWnd != NULL )
		{
			CEGBaseWnd * pWnd = GetWndObject( hWnd );
			if( pWnd != NULL )
				pWnd->SetFont( hFont );
			
			hWnd = GetWindow( hWnd, GW_HWNDNEXT );
		}
	}
	VOID				ReDraw()
	{
		InvalidateRect( m_hWnd, NULL, FALSE );
	}
	CEGBaseWnd *		GetWndObject( HWND hWnd )
	{
		return (CEGBaseWnd*)GetWindowLong( hWnd, GWL_USERDATA );
	}
	DWORD				SetSytle(DWORD dwStyle)
	{
		DWORD	dwRet = (DWORD)SetWindowLong( m_hWnd, GWL_STYLE, dwStyle );
		ApplyStyleChange();
		return dwRet;
	}
	VOID				AddStyle(DWORD dwStyle)
	{
		DWORD	dwOldStyle = GetStyle();
		dwOldStyle|= dwStyle;
		SetSytle( dwOldStyle );
	}
	VOID				RemoveStyle( DWORD dwStyle )
	{
		DWORD	dwOldStyle = GetStyle();
		DWORD	dwRStyle = (dwOldStyle & dwStyle);
		if( dwRStyle != 0 )
			dwOldStyle ^= dwRStyle;
		SetSytle(dwOldStyle);
	}
protected:
	VOID				ApplyStyleChange()
	{
		RECT	rect;
		if( !GetWindowRect(m_hWnd, &rect ) )
			return;
		DWORD	dwStyle = this->GetStyle();

		AdjustWindowRect(&rect, dwStyle, FALSE );
	}
	BOOL				HandleWnd();
	// 消息回调
	HRESULT				MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static HRESULT		GlobeMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
protected:
	HWND				m_hWnd;
	LONG				m_lOldProc;
	UINT				m_Id;
	HRESULT				m_hResult;
	CEGWndMsgFilter *	m_pMsgFilter;
};
//------------------------------------------------------------------------