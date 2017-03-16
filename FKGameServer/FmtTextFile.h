/**
*	created:		2013-4-18   23:18
*	filename: 		FmtTextFile
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
enum	fmt_type
{
	FT_STRING,
	FT_BYTE,
	FT_WORD,
	FT_DWORD,
};
//------------------------------------------------------------------------
struct fmt_struct_element
{
	fmt_struct_element()
	{
		wType = 0;
		wLength = 0;
		pNext = NULL;
	}
	WORD	wType;
	WORD	wLength;
	fmt_struct_element * pNext;
};
//------------------------------------------------------------------------
class CFmtTextFile
{
public:
	CFmtTextFile( const char * pszStruct, const char * pszFile = NULL, BOOL bCSV = FALSE );
	virtual ~CFmtTextFile(void);
public:
	BOOL	Load( const char * pszFile, BOOL bCSV = FALSE );
	int		GetCount(){ return m_sfFile.GetLineCount();}
	BOOL	GetStruct( int line, LPVOID lpStruct );
protected:
	char		m_szStruct[1024];
	BOOL		m_bLoaded;
	CStringFile m_sfFile;
	BOOL		m_bCSV;
	fmt_struct_element	*m_pStructDesc;
	int			m_iStructElements;
	int			m_iMaxParams;
	char **		Params;
	int			nParam;
};
//------------------------------------------------------------------------