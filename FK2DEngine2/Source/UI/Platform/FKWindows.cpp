/**
*	created:		2013-4-11   21:22
*	filename: 		FKWindows
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#ifdef _WIN32

	#ifndef _WIN32_WINNT
	#	define _WIN32_WINNT 0x06000000
	#else
	#	if _WIN32_WINNT < 0x06000000
	#		error "Not support platform."
	#	endif
	#endif
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
#include <windows.h>
#include <ShlObj.h>
#include <Shobjidl.h>
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Platform;
//------------------------------------------------------------------------
#define FILESTRING_SIZE			256
#define FILTERBUFFER_SIZE		512
//------------------------------------------------------------------------
static FK2DEngine2::Input::Windows FKInput;
//------------------------------------------------------------------------
static LPCTSTR iCursorConversion[] =
{
	IDC_ARROW,
	IDC_IBEAM,
	IDC_SIZENS,
	IDC_SIZEWE,
	IDC_SIZENWSE,
	IDC_SIZENESW,
	IDC_SIZEALL,
	IDC_NO,
	IDC_WAIT,
	IDC_HAND
};
//------------------------------------------------------------------------
void FK2DEngine2::Platform::SetCursor( unsigned char iCursor )
{
	::SetCursor( LoadCursor( NULL, iCursorConversion[iCursor] ) );
}
//------------------------------------------------------------------------
void FK2DEngine2::Platform::GetCursorPos( FK2DEngine2::Point & po )
{
	POINT p;
	::GetCursorPos( &p );
	po.x = p.x;
	po.y = p.y;
}
//------------------------------------------------------------------------
void FK2DEngine2::Platform::GetDesktopSize( int & w, int & h )
{
	w = GetSystemMetrics( SM_CXFULLSCREEN );
	h = GetSystemMetrics( SM_CYFULLSCREEN );
}
//------------------------------------------------------------------------
FK2DEngine2::UnicodeString FK2DEngine2::Platform::GetClipboardText()
{
	if ( !OpenClipboard( NULL ) ) { return L""; }

	HANDLE hData = GetClipboardData( CF_UNICODETEXT );

	if ( hData == NULL )
	{
		CloseClipboard();
		return L"";
	}

	wchar_t* buffer = ( wchar_t* ) GlobalLock( hData );
	UnicodeString str = buffer;
	GlobalUnlock( hData );
	CloseClipboard();
	return str;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Platform::SetClipboardText( const FK2DEngine2::UnicodeString & str )
{
	if ( !OpenClipboard( NULL ) ) { return false; }

	EmptyClipboard();
	size_t iDataSize = ( str.length() + 1 ) * sizeof( wchar_t );
	HGLOBAL clipbuffer = GlobalAlloc( GMEM_DDESHARE, iDataSize );
	wchar_t* buffer = ( wchar_t* ) GlobalLock( clipbuffer );
	wcscpy( buffer, str.c_str() );
	GlobalUnlock( clipbuffer );
	SetClipboardData( CF_UNICODETEXT, clipbuffer );
	CloseClipboard();
	return true;
}
//------------------------------------------------------------------------
double GetPerformanceFrequency()
{
	static double Frequency = 0.0f;

	if ( Frequency == 0.0f )
	{
		__int64 perfFreq;
		QueryPerformanceFrequency( ( LARGE_INTEGER* ) &perfFreq );
		Frequency = 1.0 / ( double ) perfFreq;
	}

	return Frequency;
}
//------------------------------------------------------------------------
float FK2DEngine2::Platform::GetTimeInSeconds()
{
	static float fCurrentTime = 0.0f;
	static __int64 iLastTime = 0;
	__int64 thistime;
	QueryPerformanceCounter( ( LARGE_INTEGER* ) &thistime );
	float fSecondsDifference = ( double )( thistime - iLastTime ) * GetPerformanceFrequency();

	if ( fSecondsDifference > 0.1f ) { fSecondsDifference = 0.1f; }

	fCurrentTime += fSecondsDifference;
	iLastTime = thistime;
	return fCurrentTime;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Platform::FileOpen( const String & Name, const String & StartPath,
									 const String & Extension, FK2DEngine2::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
{
	char Filestring[FILESTRING_SIZE];
	String returnstring;
	char FilterBuffer[FILTERBUFFER_SIZE];
	{
		memset( FilterBuffer, 0, sizeof( FilterBuffer ) );
		memcpy( FilterBuffer, Extension.c_str(), FK2DEngine2::Min( Extension.length(), sizeof( FilterBuffer ) ) );

		for ( int i = 0; i < FILTERBUFFER_SIZE; i++ )
		{
			if ( FilterBuffer[i] == '|' )
			{ FilterBuffer[i] = 0; }
		}
	}
	OPENFILENAMEA opf;
	opf.hwndOwner = 0;
	opf.lpstrFilter = FilterBuffer;
	opf.lpstrCustomFilter = 0;
	opf.nMaxCustFilter = 0L;
	opf.nFilterIndex = 1L;
	opf.lpstrFile = Filestring;
	opf.lpstrFile[0] = '\0';
	opf.nMaxFile = FILESTRING_SIZE;
	opf.lpstrFileTitle = 0;
	opf.nMaxFileTitle = 50;
	opf.lpstrInitialDir = StartPath.c_str();
	opf.lpstrTitle = Name.c_str();
	opf.nFileOffset = 0;
	opf.nFileExtension = 0;
	opf.lpstrDefExt = "*.*";
	opf.lpfnHook = NULL;
	opf.lCustData = 0;
	opf.Flags = ( OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ) & ~OFN_ALLOWMULTISELECT;
	opf.lStructSize = sizeof( OPENFILENAME );

	if ( GetOpenFileNameA( &opf ) )
	{
		if ( pHandler && fnCallback )
		{
			FK2DEngine2::Event::Information info;
			info.Control		= NULL;
			info.ControlCaller	= NULL;
			info.String			= opf.lpstrFile;
			( pHandler->*fnCallback )( info );
		}
	}

	return true;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Platform::FolderOpen( const String & Name, const String & StartPath,
									   FK2DEngine2::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
{
	IFileDialog* pfd = NULL;
	bool bSuccess = false;

	if ( CoCreateInstance( CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &pfd ) ) != S_OK )
	{ return bSuccess; }

	DWORD dwOptions;

	if ( pfd->GetOptions( &dwOptions ) != S_OK )
	{
		pfd->Release();
		return bSuccess;
	}

	pfd->SetOptions( dwOptions | FOS_PICKFOLDERS );

	if ( pfd->Show( NULL ) == S_OK )
	{
		IShellItem* psi;

		if ( pfd->GetResult( &psi ) == S_OK )
		{
			WCHAR* strOut = NULL;

			if ( psi->GetDisplayName( SIGDN_DESKTOPABSOLUTEPARSING, &strOut ) != S_OK )
			{
				return bSuccess;
			}

			if ( pHandler && fnCallback )
			{
				FK2DEngine2::Event::Information info;
				info.Control		= NULL;
				info.ControlCaller	= NULL;
				info.String			= FK2DEngine2::Utility::UnicodeToString( strOut );
				( pHandler->*fnCallback )( info );
			}

			CoTaskMemFree( strOut );
			psi->Release();
			bSuccess = true;
		}
	}

	pfd->Release();
	return bSuccess;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Platform::FileSave( const String & Name, const String & StartPath, const String & Extension,
									 FK2DEngine2::Event::Handler* pHandler, FK2DEngine2::Event::Handler::FunctionWithInformation fnCallback )
{
	char Filestring[FILESTRING_SIZE];
	String returnstring;
	char FilterBuffer[FILTERBUFFER_SIZE];
	{
		memset( FilterBuffer, 0, sizeof( FilterBuffer ) );
		memcpy( FilterBuffer, Extension.c_str(), FK2DEngine2::Min( Extension.size(), sizeof( FilterBuffer ) ) );

		for ( int i = 0; i < FILTERBUFFER_SIZE; i++ )
		{
			if ( FilterBuffer[i] == '|' )
			{ FilterBuffer[i] = 0; }
		}
	}
	OPENFILENAMEA opf;
	opf.hwndOwner = 0;
	opf.lpstrFilter = FilterBuffer;
	opf.lpstrCustomFilter = 0;
	opf.nMaxCustFilter = 0L;
	opf.nFilterIndex = 1L;
	opf.lpstrFile = Filestring;
	opf.lpstrFile[0] = '\0';
	opf.nMaxFile = FILESTRING_SIZE;
	opf.lpstrFileTitle = 0;
	opf.nMaxFileTitle = 50;
	opf.lpstrInitialDir = StartPath.c_str();
	opf.lpstrTitle = Name.c_str();
	opf.nFileOffset = 0;
	opf.nFileExtension = 0;
	opf.lpstrDefExt = "*.*";
	opf.lpfnHook = NULL;
	opf.lCustData = 0;
	opf.Flags = ( OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ) & ~OFN_ALLOWMULTISELECT;
	opf.lStructSize = sizeof( OPENFILENAME );

	if ( GetSaveFileNameA( &opf ) )
	{
		if ( pHandler && fnCallback )
		{
			FK2DEngine2::Event::Information info;
			info.Control		= NULL;
			info.ControlCaller	= NULL;
			info.String			= opf.lpstrFile;
			( pHandler->*fnCallback )( info );
		}
	}

	return true;
}
//------------------------------------------------------------------------
void* FK2DEngine2::Platform::CreatePlatformWindow( int x, int y, int w, int h, const FK2DEngine2::String & strWindowTitle )
{
	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
	WNDCLASSA	wc;
	ZeroMemory( &wc, sizeof( wc ) );
	wc.style			= CS_OWNDC | CS_DROPSHADOW;
	wc.lpfnWndProc		= DefWindowProc;
	wc.hInstance		= GetModuleHandle( NULL );
	wc.lpszClassName	= "FK_Window_Class";
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	RegisterClassA( &wc );
	HWND hWindow = CreateWindowExA( WS_EX_APPWINDOW | WS_EX_ACCEPTFILES, wc.lpszClassName, strWindowTitle.c_str(), WS_POPUP | WS_VISIBLE, x, y, w, h, NULL, NULL, GetModuleHandle( NULL ), NULL );
	ShowWindow( hWindow, SW_SHOW );
	SetForegroundWindow( hWindow );
	SetFocus( hWindow );
	{
		HRGN rgn = CreateRoundRectRgn( 0, 0, w + 1, h + 1, 4, 4 );
		SetWindowRgn( hWindow, rgn, false );
	}
	return ( void* ) hWindow;
}
//------------------------------------------------------------------------
void FK2DEngine2::Platform::DestroyPlatformWindow( void* pPtr )
{
	DestroyWindow( ( HWND ) pPtr );
	CoUninitialize();
}
//------------------------------------------------------------------------
void FK2DEngine2::Platform::MessagePump( void* pWindow, FK2DEngine2::Controls::Canvas* ptarget )
{
	FKInput.Initialize( ptarget );
	MSG msg;

	while ( PeekMessage( &msg, ( HWND ) pWindow, 0, 0, PM_REMOVE ) )
	{
		if ( FKInput.ProcessMessage( msg ) )
		{ continue; }

		if ( msg.message == WM_PAINT )
		{
			ptarget->Redraw();
		}

		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	{
		static HWND g_LastFocus = NULL;

		if ( GetActiveWindow()  != g_LastFocus )
		{
			g_LastFocus = GetActiveWindow();
			ptarget->Redraw();
		}
	}
}
//------------------------------------------------------------------------
void FK2DEngine2::Platform::SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h )
{
	SetWindowPos( ( HWND ) pPtr, HWND_NOTOPMOST, x, y, w, h, SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOSENDCHANGING );
	{
		HRGN rgn = CreateRoundRectRgn( 0, 0, w + 1, h + 1, 4, 4 );
		SetWindowRgn( ( HWND ) pPtr, rgn, false );
	}
}
//------------------------------------------------------------------------
void FK2DEngine2::Platform::SetWindowMaximized( void* pPtr, bool bMax, FK2DEngine2::Point & pNewPos, FK2DEngine2::Point & pNewSize )
{
	if ( bMax )
	{
		ShowWindow( ( HWND ) pPtr, SW_SHOWMAXIMIZED );
		RECT rect;
		SystemParametersInfo( SPI_GETWORKAREA, 0, &rect, 0 );
		SetWindowPos( ( HWND ) pPtr, HWND_NOTOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOSENDCHANGING );
		{
			SetWindowRgn( ( HWND ) pPtr, NULL, false );
		}
	}
	else
	{
		ShowWindow( ( HWND ) pPtr, SW_RESTORE );
		{
			RECT r;
			GetWindowRect( ( HWND ) pPtr, &r );
			HRGN rgn = CreateRoundRectRgn( 0, 0, ( r.right - r.left ) + 1, ( r.bottom - r.top ) + 1, 4, 4 );
			SetWindowRgn( ( HWND ) pPtr, rgn, false );
		}
	}

	RECT r;
	GetWindowRect( ( HWND ) pPtr, &r );
	pNewSize.x = r.right - r.left;
	pNewSize.y = r.bottom - r.top ;
	pNewPos.x = r.left;
	pNewPos.y = r.top;
}
//------------------------------------------------------------------------
void FK2DEngine2::Platform::SetWindowMinimized( void* pPtr, bool bMinimized )
{
	if ( bMinimized )
	{
		ShowWindow( ( HWND ) pPtr, SW_SHOWMINIMIZED );
	}
	else
	{
		ShowWindow( ( HWND ) pPtr, SW_RESTORE );
	}
}
//------------------------------------------------------------------------
bool FK2DEngine2::Platform::HasFocusPlatformWindow( void* pPtr )
{
	return GetActiveWindow() == ( HWND ) pPtr;
}
//------------------------------------------------------------------------
void FK2DEngine2::Platform::Sleep( unsigned int iMS )
{
	::Sleep( iMS );
}
//------------------------------------------------------------------------
#endif // WIN32
//------------------------------------------------------------------------