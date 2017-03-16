/**
*	created:		2013-4-16   0:40
*	filename: 		xSupport
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
//------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <MMSystem.h>
#include <assert.h>
#include <string>
//------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------
#include "xException.h"
#include "xTime.h"
#include "xString.h"
#include "xFile.h"
#include "xRand.h"
#include "xIdMaker.h"
#include "xIntHash.h"
#include "xLock.h"
#include "xDataStructure.h"
#include "xStringFile.h"
#include "xSettingFile.h"
#include "xSingleton.h"
#include "xEventBase.h"
#include "xStringsExpander.h"
//------------------------------------------------------------------------
#undef MAX
#undef MIN
#define MAX(a,b)	((a)>(b)?(a):(b))
#define	MIN(a,b)	((a)>(b)?(b):(a))
//------------------------------------------------------------------------