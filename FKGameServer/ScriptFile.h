/**
*	created:		2013-4-19   9:32
*	filename: 		ScriptFile
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CScriptFile
{
public:
	CScriptFile(void);
	virtual ~CScriptFile(void);
	BOOL	Load( const char * pszFileName );
	VOID	Close();
	char * FirstLine();
	char * NextLine();
	char * PrevLine();
	char * CurrentLine();
	UINT	GetCurrentLineNumber();
	VOID	SetLineIndex( UINT index )
	{
		m_nLineIndex = index;
	}
	const char * GetFileName(){ return m_szFileName;}
protected:
	BOOL	ProtectedLoad();
	char	m_szFileName[1024];
	UINT	m_nLineIndex;
	CStringFile m_fScript;
	BYTE *	m_pData;
};
//------------------------------------------------------------------------