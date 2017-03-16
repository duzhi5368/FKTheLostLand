/**
*	created:		2013-4-12   21:42
*	filename: 		FKRichLabel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKBase.h"
#include "FKText.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT RichLabel : public Controls::Base
		{
			public:

				FK_CONTROL( RichLabel, FK2DEngine2::Controls::Base );

				void AddLineBreak();
				void AddText( const FK2DEngine2::UITexObjSimpleInfo & text, FK2DEngine2::Color color, FK2DEngine2::Font* font = NULL );

				virtual bool SizeToChildren( bool w = true, bool h = true );

			protected:

				struct DividedText
				{
					typedef std::list<DividedText> List;
					DividedText()
					{
						type = 0;
						font = NULL;
					}

					unsigned char			type;
					FK2DEngine2::UnicodeString		text;
					FK2DEngine2::Color				color;
					FK2DEngine2::Font*				font;
				};

				void Layout( FK2DEngine2::Skin::Base* skin );
				void SplitLabel( const FK2DEngine2::UnicodeString & text, FK2DEngine2::Font* pFont, const DividedText & txt, int & x, int & y, int & lineheight );
				void CreateNewline( int & x, int & y, int & lineheight );
				void CreateLabel( const FK2DEngine2::UnicodeString & text, const DividedText & txt, int & x, int & y, int & lineheight, bool NoSplit );
				void Rebuild();

				void OnBoundsChanged( FK2DEngine2::Rect oldBounds );

				DividedText::List	m_TextBlocks;
				bool				m_bNeedsRebuild;
		};
	}
}
//------------------------------------------------------------------------