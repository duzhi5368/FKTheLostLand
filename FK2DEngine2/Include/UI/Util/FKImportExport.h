/**
*	created:		2013-4-11   22:45
*	filename: 		FKImportExport
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ImportExport
	{
		class Base
		{
		public:

			Base();

			virtual FK2DEngine2::String Name() = 0;

			virtual bool CanImport() = 0;
			virtual void Import( FK2DEngine2::Controls::Base* pRoot, const FK2DEngine2::String & strFilename ) = 0;

			virtual bool CanExport() = 0;
			virtual void Export( FK2DEngine2::Controls::Base* pRoot, const FK2DEngine2::String & strFilename ) = 0;

		public:

			typedef std::list<ImportExport::Base*> List;

		protected:

		};

		ImportExport::Base::List & GetList();
		ImportExport::Base* Find( FK2DEngine2::String strName );

		namespace Tools
		{
			ControlList GetExportableChildren( FK2DEngine2::Controls::Base* pRoot );
		}
	}
}
//------------------------------------------------------------------------
#define FK_IMPORTEXPORT( name )\
	void FKIMPORTEXPORT_##name()\
{\
	static name my_instance;\
}
//------------------------------------------------------------------------
#define DECLARE_FK_IMPORTEXPORT( name )\
	void FKIMPORTEXPORT_##name();\
	FKIMPORTEXPORT_##name();
//------------------------------------------------------------------------