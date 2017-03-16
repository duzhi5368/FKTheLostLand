/**
*	created:		2013-4-16   4:14
*	filename: 		xSettingFile
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CSettingFile
{
public:
	BOOL	Open( const char * pszFile )
	{
		if( !m_sfSetting.LoadFile((char*)pszFile) )return FALSE;
		m_sfSetting.MakeDeflate();
		return TRUE;
	}
	VOID	Close()
	{
		m_sfSetting.Destroy();
	}
	const char * GetString( const char * pszSection, const char * pszItemName, const char * pszDefValue = NULL )
	{
		char * p = GetSettingString( pszSection, pszItemName );
		if( p == NULL )return pszDefValue;
		return p;
	}
	int	GetInteger( const char * pszSection, const char * pszItemName, int DefValue = 0 )
	{
		char * p = GetSettingString( pszSection, pszItemName );
		if( p == NULL )return DefValue;
		return atoi(p);
	}
private:
	int	FindSectionLine( const char * pszSection )
	{
		if( pszSection == NULL )
			return 0;
		int linecount = m_sfSetting.GetLineCount();
		int sectionlength = (int)strlen( pszSection );
		for( int i = 0;i < linecount;i ++ )
		{
			char * p = m_sfSetting[i];

			if( *p == '[' && *(p+sectionlength+1)==']' )
			{
				if( strnicmp( p+1, pszSection, sectionlength ) == 0 )
					return (i+1);
			}
		}
		return -1;
	}
	char * GetSettingString(  const char * pszSection, const char * pszItemName )
	{
		int startindex = 0;
		if( pszSection != NULL )
		{
			startindex = FindSectionLine( pszSection );
			if( startindex == -1 )return NULL;
		}

		int itemnamelength = (int)strlen( pszItemName );
		if( itemnamelength == 0 )return NULL;

		int linecount = m_sfSetting.GetLineCount();
		for( int i = startindex;i < linecount;i ++ )
		{
			char * p = m_sfSetting[i];
			//	如果到达下一个section， 返回错误
			if( *p == '[' )return NULL;
			//	如果是ItemName=这样的句式，进入进一步搜索
			if( *(p+itemnamelength) == '=' )
			{
				if( strnicmp( p, pszItemName, itemnamelength ) == 0 )
				{
					if( *(p+itemnamelength+1) == '\"' )
					{
						char * pret = (p+itemnamelength+2);
						int length = (int)strlen( pret );
						if( *( pret + length-1 ) == '\"' )
							*( pret + length-1 ) = 0;
						return pret;
					}
					return (p+itemnamelength+1);
				}
			}
		}
		return NULL;

	}
	int	FindSettingLine( const char * pszSection, const char * pszItemName )
	{
		int startindex = 0;
		if( pszSection != NULL )
		{
			startindex = FindSectionLine( pszSection );
			if( startindex == -1 )return -1;
		}

		int itemnamelength = (int)strlen( pszItemName );
		if( itemnamelength == 0 )return -1;

		int linecount = m_sfSetting.GetLineCount();
		for( int i = startindex;i < linecount;i ++ )
		{
			char * p = m_sfSetting[i];
			//	如果到达下一个section， 返回错误
			if( *p == '[' )return -1;
			//	如果是ItemName=这样的句式，进入进一步搜索
			if( *(p+itemnamelength) == '=' )
			{
				if( strnicmp( p, pszItemName, itemnamelength ) == 0 )
					return i;
			}
		}
		return -1;
	}
	CStringFile m_sfSetting;
};
//------------------------------------------------------------------------