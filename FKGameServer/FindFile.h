/**
*	created:		2013-4-18   23:11
*	filename: 		FindFile
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#pragma warning(disable:4996)
//------------------------------------------------------------------------
class CFindFile
{
public:
	CFindFile(void){}
	virtual ~CFindFile(void){}
    //文件路径  文件名字 子文件夹 额外参数
	BOOL StartFind( const char * pszPath, const char * pszFindName, BOOL bFindSubFolder = FALSE, UINT nParam = 0 )
	{
		WIN32_FIND_DATA	wfd;  //关于文件的全部属性信息
		HANDLE	hFindFile = INVALID_HANDLE_VALUE;
		CHAR	szFileName[1024];
		CHAR	szExt[32];
		CHAR	szExtTest[32];

		_makepath( szFileName, NULL, pszPath, "*.*", NULL );
		_splitpath( pszFindName, NULL, NULL, NULL, szExt );

		hFindFile = FindFirstFile( szFileName, &wfd );
		if( hFindFile != INVALID_HANDLE_VALUE )
		{
			do {
				if( (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 )
				{
					if( wfd.cFileName[0] != '.' )
					{
						if( bFindSubFolder )
						{
							_makepath( szFileName, NULL, pszPath, wfd.cFileName, NULL );
							StartFind( szFileName, pszFindName, TRUE, nParam );
						}
					}

				}
				else
				{
					_splitpath( wfd.cFileName, NULL, NULL, NULL, szExtTest );
					if( stricmp( szExtTest, szExt ) == 0 )
					{
						_makepath( szFileName, NULL, pszPath, wfd.cFileName, NULL );

						OnFoundFile( szFileName, nParam );	
					}
				}
			} while(FindNextFile( hFindFile, &wfd));
			FindClose( hFindFile );
		}
		return TRUE;
	}
protected:
	virtual VOID OnFoundFile( const char * pszFilename, UINT nParam = 0 ){}
};
