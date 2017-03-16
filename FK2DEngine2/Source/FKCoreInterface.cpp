/**
*	created:		2013-4-23   15:13
*	filename: 		FKCoreInterface
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKCoreInterface.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core
	{
		std::istream & operator >> (std::istream & inStream,IPersistence & persistence)
		{
			persistence.readFromStream(inStream);
			return inStream;
		}
		std::ostream & operator << (std::ostream & outStream,IPersistence & persistence)
		{
			persistence.writeToStream(outStream);
			return outStream;
		}
	}
}
//------------------------------------------------------------------------