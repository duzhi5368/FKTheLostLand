/**
*	created:		2013-4-11   17:25
*	filename: 		FKBase
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <list>
#include <map>
#include <algorithm>
//------------------------------------------------------------------------
#include "../FKExports.h"
#include "../FKStructures.h"
#include "../FKBaseRender.h"
#include "../FKEvents.h"
#include "../FKUtility.h"
#include "../FKTextObject.h"
#include "../FKSkin.h"
#include "../FKControlList.h"
#include "../FKUserData.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Pos
	{
		enum
		{
			None		= 0,
			Left		= ( 1 << 1 ),
			Right		= ( 1 << 2 ),
			Top			= ( 1 << 3 ),
			Bottom		= ( 1 << 4 ),
			CenterV		= ( 1 << 5 ),
			CenterH		= ( 1 << 6 ),
			Fill		= ( 1 << 7 ),
			Center		= CenterV | CenterH,
		};
	}

	class UITexObjSimpleInfo;

	namespace Skin
	{
		class Base;
	}

	namespace Controls
	{
		class Canvas;

		class FK_EXPORT Base : public Event::Handler
		{
			public:

				typedef std::list<Base*> List;

				typedef std::map<FK2DEngine2::UnicodeString, FK2DEngine2::Event::Caller*> AccelMap;

				Base( Base* pParent, const FK2DEngine2::String & Name = "" );
				virtual ~Base();

				virtual const char* GetTypeName() { return "Base"; }

				virtual void DelayedDelete();
				virtual void PreDelete( FK2DEngine2::Skin::Base* skin ) {};

				virtual void SetParent( Controls::Base* pParent );
				virtual Controls::Base* GetParent() const { return m_Parent; }
				virtual Controls::Canvas* GetCanvas();

				virtual Base::List & GetChildren() { if ( m_InnerPanel ) { return m_InnerPanel->GetChildren(); } return Children; }
				virtual bool IsChild( Controls::Base* pChild );
				virtual unsigned int NumChildren();
				virtual Controls::Base* GetChild( unsigned int i );
				virtual bool SizeToChildren( bool w = true, bool h = true );
				virtual FK2DEngine2::Point ChildrenSize();
				virtual Controls::Base* FindChildByName( const FK2DEngine2::String & name, bool bRecursive = false );

				template <typename T> T* FindChild( const FK2DEngine2::String & name, bool bRecursive = false );

				virtual void SetName( const FK2DEngine2::String & name ) { m_Name = name; }
				virtual const FK2DEngine2::String & GetName() { return m_Name; }

				virtual void Think() {}

			protected:

				virtual void AddChild( Controls::Base* pChild );
				virtual void RemoveChild( Controls::Base* pParent );
				virtual void OnChildAdded( Controls::Base* pChild );
				virtual void OnChildRemoved( Controls::Base* pChild );

			public:

				virtual void RemoveAllChildren();

				virtual void SendToBack( void );
				virtual void BringToFront( void );
				virtual void BringNextToControl( Controls::Base* pChild, bool bBehind );

				virtual FK2DEngine2::Point LocalPosToCanvas( const FK2DEngine2::Point & in = Point( 0, 0 ) );
				virtual FK2DEngine2::Point CanvasPosToLocal( const FK2DEngine2::Point & in );

				virtual void Dock( int iDock );
				virtual int GetDock();

				virtual void RestrictToParent( bool restrict ) { m_bRestrictToParent = restrict; }
				virtual bool ShouldRestrictToParent() { return m_bRestrictToParent; }

				virtual int X() const { return m_Bounds.x; }
				virtual int Y() const { return m_Bounds.y; }
				virtual int Width() const { return m_Bounds.w; }
				virtual int Height() const { return m_Bounds.h; }
				virtual int Bottom() const { return m_Bounds.y + m_Bounds.h + m_Margin.bottom; }
				virtual int Right() const { return m_Bounds.x + m_Bounds.w + m_Margin.right; }

				virtual const Margin & GetMargin() const { return m_Margin; }
				virtual const Padding & GetPadding() const { return m_Padding; }

				virtual void SetPos( int x, int y );
				virtual void SetPos( const Point & p ) { return SetPos( p.x, p.y ); }
				virtual Point GetPos() { return Point( X(), Y() ); }
				virtual void SetWidth( int w ) { SetSize( w, Height() ); }
				virtual void SetHeight( int h ) { SetSize( Width(), h ); }
				virtual bool SetSize( int w, int h );
				virtual bool SetSize( const Point & p );
				virtual Point GetSize() { return Point( Width(), Height() ); }
				virtual bool SetBounds( int x, int y, int w, int h );
				virtual bool SetBounds( const FK2DEngine2::Rect & bounds );

				virtual void SetPadding( const Padding & padding );
				virtual void SetMargin( const Margin & margin );

				virtual void MoveTo( int x, int y );
				virtual void MoveBy( int x, int y );

				virtual const FK2DEngine2::Rect & GetBounds() const { return m_Bounds; }

				virtual Controls::Base* GetControlAt( int x, int y, bool bOnlyIfMouseEnabled = true );

			protected:

				virtual void OnBoundsChanged( FK2DEngine2::Rect oldBounds );
				virtual void OnChildBoundsChanged( FK2DEngine2::Rect oldChildBounds, Base* pChild );

				virtual void OnScaleChanged();

			public:

				virtual const FK2DEngine2::Rect & GetInnerBounds() const { return m_InnerBounds; }

			protected:

				FK2DEngine2::Rect m_InnerBounds;

			public:

				virtual const FK2DEngine2::Rect & GetRenderBounds() const { return m_RenderBounds; }

			protected:

				virtual void UpdateRenderBounds();

			public:

				virtual void DoRender( FK2DEngine2::Skin::Base* skin );
				virtual void DoCacheRender( FK2DEngine2::Skin::Base* skin, FK2DEngine2::Controls::Base* pMaster );
				virtual void RenderRecursive( FK2DEngine2::Skin::Base* skin, const FK2DEngine2::Rect & cliprect );

				virtual bool ShouldClip() { return true; }

			protected:

				virtual void Render( FK2DEngine2::Skin::Base* skin );
				virtual void RenderUnder( FK2DEngine2::Skin::Base* /*skin*/ ) {};
				virtual void RenderOver( FK2DEngine2::Skin::Base* /*skin*/ ) {};
				virtual void RenderFocus( FK2DEngine2::Skin::Base* /*skin*/ );

			public:

				virtual void SetHidden( bool hidden ) { if ( m_bHidden == hidden ) { return; } m_bHidden = hidden; Invalidate(); Redraw(); }
				virtual bool Hidden() const;
				virtual bool Visible() const;
				virtual void Hide() { SetHidden( true ); }
				virtual void Show() { SetHidden( false ); }

				virtual void SetSkin( Skin::Base* skin, bool doChildren = false );
				virtual FK2DEngine2::Skin::Base* GetSkin( void );

				virtual bool ShouldDrawBackground() { return m_bDrawBackground; }
				virtual void SetShouldDrawBackground( bool b ) { m_bDrawBackground = b; }

			protected:

				virtual void OnSkinChanged( FK2DEngine2::Skin::Base* newSkin );

			public:

				virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );
				virtual bool OnMouseWheeled( int iDelta );
				virtual void OnMouseClickLeft( int /*x*/, int /*y*/, bool /*bDown*/ ) {};
				virtual void OnMouseClickRight( int /*x*/, int /*y*/, bool /*bDown*/ ) {}
				virtual void OnMouseDoubleClickLeft( int x, int y ) { OnMouseClickLeft( x, y, true ); };
				virtual void OnMouseDoubleClickRight( int x, int y ) { OnMouseClickRight( x, y, true ); };
				virtual void OnLostKeyboardFocus() {}
				virtual void OnKeyboardFocus() {}

				virtual void SetMouseInputEnabled( bool b )	{ m_bMouseInputEnabled = b; }
				virtual bool GetMouseInputEnabled()	{ return m_bMouseInputEnabled; }

				virtual void SetKeyboardInputEnabled( bool b ) { m_bKeyboardInputEnabled = b; }
				virtual bool GetKeyboardInputEnabled() const { return m_bKeyboardInputEnabled; }
				virtual bool NeedsInputChars() { return false; }

				virtual bool OnChar( FK2DEngine2::UnicodeChar /*c*/ ) { return false; }

				virtual bool OnKeyPress( int iKey, bool bPress = true );
				virtual bool OnKeyRelease( int iKey );

				virtual void OnPaste( Controls::Base* /*pFrom*/ ) {}
				virtual void OnCopy( Controls::Base* /*pFrom*/ ) {}
				virtual void OnCut( Controls::Base* /*pFrom*/ ) {}
				virtual void OnSelectAll( Controls::Base* /*pFrom*/ ) {}

				virtual bool OnKeyTab( bool bDown );
				virtual bool OnKeySpace( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyReturn( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyBackspace( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyDelete( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyRight( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyLeft( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyHome( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyEnd( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyUp( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyDown( bool /*bDown*/ ) { return false; }
				virtual bool OnKeyEscape( bool /*bDown*/ ) { return false; }

				virtual void OnMouseEnter();
				virtual void OnMouseLeave();
				virtual bool IsHovered();
				virtual bool ShouldDrawHover();

				virtual void Touch();
				virtual void OnChildTouched( Controls::Base* pChild );

				virtual bool IsOnTop();

				virtual bool HasFocus();
				virtual void Focus();
				virtual void Blur();

				virtual void SetDisabled( bool active ) { if ( m_bDisabled == active ) { return; } m_bDisabled = active; Redraw(); }
				virtual bool IsDisabled() { return m_bDisabled; }

				virtual void Redraw() { UpdateColours(); m_bCacheTextureDirty = true; if ( m_Parent ) { m_Parent->Redraw(); } }
				virtual void UpdateColours() {};
				virtual void SetCacheToTexture() { m_bCacheToTexture = true; }
				virtual bool ShouldCacheToTexture() { return m_bCacheToTexture; }

				virtual void SetCursor( unsigned char c ) { m_Cursor = c; }
				virtual void UpdateCursor();

				virtual FK2DEngine2::Point GetMinimumSize() { return FK2DEngine2::Point( 1, 1 ); }
				virtual FK2DEngine2::Point GetMaximumSize() { return FK2DEngine2::Point( 4096, 4096 ); }

				virtual void SetToolTip( const FK2DEngine2::UITexObjSimpleInfo & strText );
				virtual void SetToolTip( Base* tooltip ) { m_ToolTip = tooltip; if ( m_ToolTip ) { m_ToolTip->SetParent( this ); m_ToolTip->SetHidden( true ); } }
				virtual Base* GetToolTip() { return m_ToolTip; }

				virtual bool IsMenuComponent();
				virtual void CloseMenus();

				virtual bool IsTabable() { return m_Tabable; }
				virtual void SetTabable( bool isTabable ) { m_Tabable = isTabable; }

				// ¿ì½Ý¼ü±í
				void DefaultAccel( FK2DEngine2::Controls::Base* /*pCtrl*/ ) { AcceleratePressed(); }
				virtual void AcceleratePressed() {};
				virtual bool AccelOnlyFocus() { return false; }
				virtual bool HandleAccelerator( FK2DEngine2::UnicodeString & accelerator );

				template <typename T>
				void AddAccelerator( const UITexObjSimpleInfo & accelerator, T func, FK2DEngine2::Event::Handler* handler = NULL )
				{
					if ( handler == NULL )
					{ handler = this; }

					FK2DEngine2::Event::Caller* caller = new FK2DEngine2::Event::Caller();
					caller->Add( handler, func );
					FK2DEngine2::UnicodeString str = accelerator.GetUnicode();
					FK2DEngine2::Utility::Strings::ToUpper( str );
					FK2DEngine2::Utility::Strings::Strip( str, L" " );
					m_Accelerators[ str ] = caller;
				}

				void AddAccelerator( const UITexObjSimpleInfo & accelerator )
				{
					AddAccelerator( accelerator, &Base::DefaultAccel, this );
				}

				AccelMap m_Accelerators;
				FK2DEngine2::Event::Caller	onHoverEnter;
				FK2DEngine2::Event::Caller	onHoverLeave;
				Base::List Children;

			protected:


				Base* m_Parent;

				Base* m_InnerPanel;
				virtual Base* Inner() { return m_InnerPanel; }

				Base* m_ActualParent;

				Base* m_ToolTip;

				Skin::Base* m_Skin;

				FK2DEngine2::Rect		m_Bounds;
				FK2DEngine2::Rect		m_RenderBounds;

				Padding		m_Padding;
				Margin		m_Margin;

				FK2DEngine2::String m_Name;


				bool m_bRestrictToParent;
				bool m_bDisabled;
				bool m_bHidden;
				bool m_bMouseInputEnabled;
				bool m_bKeyboardInputEnabled;
				bool m_bDrawBackground;

				int m_iDock;

				unsigned char	m_Cursor;

				bool m_Tabable;

			public:

				bool NeedsLayout() { return m_bNeedsLayout; }
				void Invalidate();
				void InvalidateParent() { if ( m_Parent ) { m_Parent->Invalidate(); } }
				void InvalidateChildren( bool bRecursive = false );
				void Position( int pos, int xpadding = 0, int ypadding = 0 );

			protected:

				virtual void RecurseLayout( Skin::Base* skin );
				virtual void Layout( Skin::Base* skin );
				virtual void PostLayout( Skin::Base* /*skin*/ ) {};

				bool m_bNeedsLayout;
				bool m_bCacheTextureDirty;
				bool m_bCacheToTexture;

			public:

				virtual void DragAndDrop_SetPackage( bool bDraggable, const String & strName = "", void* pUserData = NULL );
				virtual bool DragAndDrop_Draggable();
				virtual bool DragAndDrop_ShouldStartDrag() { return true; }
				virtual void DragAndDrop_StartDragging( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );
				virtual FK2DEngine2::DragAndDrop::Package* DragAndDrop_GetPackage( int x, int y );
				virtual void DragAndDrop_EndDragging( bool /*bSuccess*/, int /*x*/, int /*y*/ ) {};

			protected:

				DragAndDrop::Package*	m_DragAndDrop_Package;

			public:

				virtual void DragAndDrop_HoverEnter( FK2DEngine2::DragAndDrop::Package* /*pPackage*/, int /*x*/, int /*y*/ ) { }
				virtual void DragAndDrop_HoverLeave( FK2DEngine2::DragAndDrop::Package* /*pPackage*/ ) { }
				virtual void DragAndDrop_Hover( FK2DEngine2::DragAndDrop::Package* /*pPackage*/, int /*x*/, int /*y*/ ) {};
				virtual bool DragAndDrop_HandleDrop( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );
				virtual bool DragAndDrop_CanAcceptPackage( FK2DEngine2::DragAndDrop::Package* /*pPackage*/ ) { return false; }

			public:

				virtual void Anim_WidthIn( float fLength, float fDelay = 0.0f, float fEase = 1.0f );
				virtual void Anim_HeightIn( float fLength, float fDelay = 0.0f, float fEase = 1.0f );
				virtual void Anim_WidthOut( float fLength, bool bHide = true, float fDelay = 0.0f, float fEase = 1.0f );
				virtual void Anim_HeightOut( float fLength, bool bHide = true, float fDelay = 0.0f, float fEase = 1.0f );

			public:

				static const char* GetIdentifier()
				{
					static const char* ident = "Base";
					return ident;
				};

				virtual FK2DEngine2::Controls::Base* DynamicCast( const char* Variable )
				{
					return NULL;
				}


			public:

				void DoNotIncludeInSize() { m_bIncludeInSize = false; }
				bool ShouldIncludeInSize() { return m_bIncludeInSize; }

			protected:

				bool	m_bIncludeInSize;

			public:

				virtual UITexObjSimpleInfo GetChildValue( const FK2DEngine2::String & strName );
				virtual UITexObjSimpleInfo GetValue();
				virtual void SetValue( const UITexObjSimpleInfo & strValue );
				virtual void DoAction() {};
				virtual void SetAction( Event::Handler* pObject, Handler::FunctionWithInformation pFunction, const FK2DEngine2::Event::Packet & packet ) {};

				virtual int GetNamedChildren( FK2DEngine2::ControlList & list, const FK2DEngine2::String & strName, bool bDeep = true );
				virtual FK2DEngine2::ControlList GetNamedChildren( const FK2DEngine2::String & strName, bool bDeep = true );

			public:

				UserDataStorage	UserData;

		};
	}
}

//------------------------------------------------------------------------

template< class T >
T* fk_cast( FK2DEngine2::Controls::Base* p )
{
	if ( !p ) { return NULL; }

	FK2DEngine2::Controls::Base* pReturn = p->DynamicCast( T::GetIdentifier() );

	if ( !pReturn ) { return NULL; }

	return static_cast<T*>( pReturn );
}

//------------------------------------------------------------------------

template <typename T>
T* FK2DEngine2::Controls::Base::FindChild( const FK2DEngine2::String & name, bool bRecursive )
{
	return fk_cast<T> ( FindChildByName( name, bRecursive ) );
}

//------------------------------------------------------------------------

#define FK_DYNAMIC( ThisName, BaseName )									\
																			\
	static const char* GetIdentifier()										\
	{																		\
		static const char* ident = #BaseName ":" #ThisName;					\
		return ident;														\
	};																		\
	virtual FK2DEngine2::Controls::Base* DynamicCast( const char* Variable )\
	{																		\
		if ( GetIdentifier() == Variable )									\
		return this;														\
																			\
		return BaseClass::DynamicCast( Variable);							\
	}

#define FK_CLASS( ThisName, BaseName )\
		typedef BaseName BaseClass;\
		typedef ThisName ThisClass;\
 
#define FK_CONTROL( ThisName, BaseName )\
	public:\
	FK_CLASS( ThisName, BaseName )\
	FK_DYNAMIC( ThisName, BaseName )\
	virtual const char* GetTypeName(){ return #ThisName; }\
	virtual const char* GetBaseTypeName(){ return BaseClass::GetTypeName(); }\
	ThisName( FK2DEngine2::Controls::Base* pParent, const FK2DEngine2::String& pName = "" )

#define FK_CONTROL_INLINE( ThisName, BaseName )\
	FK_CONTROL( ThisName, BaseName ) : BaseClass( pParent, pName )

#define FK_CONTROL_CONSTRUCTOR( ThisName )\
	ThisName::ThisName( FK2DEngine2::Controls::Base* pParent, const FK2DEngine2::String& pName ) : BaseClass( pParent, pName )

//------------------------------------------------------------------------