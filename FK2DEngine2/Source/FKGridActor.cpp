/**
*	created:		2013-5-1   19:58
*	filename: 		FKGridActor
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKGridActor.h"
#include "../Include/FKS2DObject.h"
#include "../Include/FK2DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace actor
	{
		//------------------------------------------------------------------------
		CGridActor::CGridActor()
		{
			//yay for magic numbers! (default parameters of the grid)
			_lineColor = FK2DEngine2::Color(.76f, .83f, 1.0f);
			_axisColor = FK2DEngine2::Color(1.0f, .41f, .6f);
			_interval = 1.0f;
			_minCoord = FK2DEngine2::math::Vector2(-100.0f, -100.0f);
			_maxCoord = FK2DEngine2::math::Vector2(100.0f, 100.0f);
		}

		CGridActor::CGridActor(FK2DEngine2::Color lines, FK2DEngine2::Color axis,
			float interval, FK2DEngine2::math::Vector2 minCoord, FK2DEngine2::math::Vector2 maxCoord)
		{
			_lineColor = lines;
			_axisColor = axis;
			_interval = interval;
			_minCoord = minCoord;
			_maxCoord = maxCoord;
		}

		void CGridActor::SetLineColor(FK2DEngine2::Color lineCol)
		{
			_lineColor = lineCol;
		}

		const FK2DEngine2::Color CGridActor::GetLineColor()
		{
			return _lineColor;
		}

		void CGridActor::SetAxisColor(FK2DEngine2::Color axisCol)
		{
			_axisColor = axisCol;
		}

		const FK2DEngine2::Color CGridActor::GetAxisColor()
		{
			return _axisColor;
		}

		void CGridActor::SetInterval(float interval)
		{
			_interval = interval;
		}

		const float CGridActor::GetInterval()
		{
			return _interval;
		}

		void CGridActor::SetMinCoord(FK2DEngine2::math::Vector2 minCoord)
		{
			_minCoord = minCoord;
		}

		const FK2DEngine2::math::Vector2 CGridActor::GetMinCoord()
		{
			return _minCoord;
		}

		void CGridActor::SetMaxCoord(FK2DEngine2::math::Vector2 maxCoord)
		{
			_maxCoord = maxCoord;
		}

		const FK2DEngine2::math::Vector2 CGridActor::GetMaxCoord()
		{
			return _maxCoord;
		}

		void CGridActor::Render()
		{
			//float i;
			//for(i = _minCoord.X; i < _maxCoord.X; i += _interval)
			//{
			//	FK2DEngine2::scene::S2D::S2DLine line;
			//	theWorld.RenderLine( line, i, _maxCoord.Y, 0 );
			//}
			//for(i = _minCoord.Y; i < _maxCoord.Y; i += _interval)
			//{
			//	FK2DEngine2::scene::S2D::S2DLine line;
			//	theWorld.RenderLine( line, _maxCoord.X, i, 0 );
			//}
		}
		//------------------------------------------------------------------------
	}
}