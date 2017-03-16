/**
*	created:		2013-4-23   15:32
*	filename: 		FKSColor
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		class SColor
		{
		public :
			SColor(){
				r = g = b = a = 0.0f;
			}
			SColor(float r_,float g_,float b_,float a_ = 1.0f)
				:r(r_),g(g_),b(b_),a(a_){}
			SColor(unsigned int color){
				unsigned int ri,gi,bi,ai;
				ai = (color & 0xff000000) >> 24;
				ri = (color & 0x00ff0000) >> 16;
				gi = (color & 0x0000ff00) >> 8;
				bi = (color & 0x000000ff);
				r = (float)ri / 255.0f;
				g = (float)gi / 255.0f;
				b = (float)bi / 255.0f;
				a = (float)ai / 255.0f;
			}
			
			SColor operator * (float m) const {
				return SColor(r * m,g * m,b * m,a);
			}
			unsigned int getDwordValue() const{
				unsigned int ri,gi,bi,ai;
				ai = (unsigned int)(a * 255.0f);
				ri = (unsigned int)(r * 255.0f);
				gi = (unsigned int)(g * 255.0f);
				bi = (unsigned int)(b * 255.0f);
				return (((ai) << 24) + ((ri) << 16) + ((gi) << 8) + bi);
			}
		static const SColor & white(){
			static SColor c(1,1,1,1);
			return c;
		}
		static const SColor & black(){
			static SColor c(0,0,0,1);
			return c;
		}
		static const SColor & red(){
			static SColor c(1,0,0,1);
			return c;
		}
		static const SColor & green(){
			static SColor c(0,1,0,1);
			return c;
		}
		static const SColor & blue(){
			static SColor c(0,0,1,1);
			return c;
		}
		static const SColor & purple(){
			static SColor c(0.7f,0,1,1);
			return c;
		}
		static const SColor & cyan(){
			static SColor c(0,0.7f,1,1);
			return c;
		}
		static const SColor & yellow(){
			static SColor c(1,1,0,1);
			return c;
		}
		static const SColor & brown(){
			static SColor c(0.5f,0.5f,0,1);
			return c;
		}
		static const SColor & orange(){
			static SColor c(1,0.5f,0,1);
			return c;
		}
		static const SColor & gray(){
			static SColor c(0.7f,0.7f,0.7f,1);
			return c;
		}
		static const SColor & achromatism(){
			static SColor c(0,0,0,0);
			return c;
		}
		public :
			float r;
			float g;
			float b;
			float a;
		};
	}
}
//------------------------------------------------------------------------