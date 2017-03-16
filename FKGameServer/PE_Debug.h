/**
*	created:		2013-4-18   23:30
*	filename: 		PE_Debug
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class DumpBuffer ;
//------------------------------------------------------------------------
class PE_Debug
  {
  public :
    PE_Debug() ;
    ~PE_Debug() ;
    void ClearReport() ;
    void DumpDebugInfo( FILE*fp, const BYTE* caller, HINSTANCE hInstance ) ;
    void Display() ;
  private :
    // Report data
    enum { MAX_MODULENAME_LEN = 512, MAX_FILENAME_LEN = 256 } ;
    char latestModule[ MAX_MODULENAME_LEN ] ;
    char latestFile[ MAX_FILENAME_LEN ] ;
    // File mapping data
    HANDLE hFile ;
    HANDLE hFileMapping ;
    PIMAGE_DOS_HEADER fileBase ;
    // Pointers to debug information
    PIMAGE_NT_HEADERS NT_Header ;
    PIMAGE_COFF_SYMBOLS_HEADER COFFDebugInfo ;
    PIMAGE_SYMBOL COFFSymbolTable ;
    int COFFSymbolCount ;
    const char* stringTable ;

    void ClearFileCache() ;
    void ClearDebugPtrs() ;
    void MapFileInMemory( const char* module ) ;
    void FindDebugInfo() ;
    void DumpSymbolInfo( FILE*fp, DWORD relativeAddress ) ;
    void DumpLineNumber( FILE*fp, DWORD relativeAddress ) ;
    PIMAGE_COFF_SYMBOLS_HEADER GetDebugHeader() ;
    PIMAGE_SECTION_HEADER SectionHeaderFromName( const char* name ) ;
    const char* GetSymbolName( PIMAGE_SYMBOL sym ) ;
  } ;
//------------------------------------------------------------------------