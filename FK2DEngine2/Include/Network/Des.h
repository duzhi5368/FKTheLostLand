/**
*	created:		2013-5-10   5:49
*	filename: 		Des
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#ifndef byte
#  define byte(x,n)   ((unsigned char)((x) >> (8 * (n))))
#endif

#ifndef _MSC_VER

#define rotr(x,n)   (((x) >> ((int)(n))) | ((x) << (32 - (int)(n))))
#define rotl(x,n)   (((x) << ((int)(n))) | ((x) >> (32 - (int)(n))))

#else

#include <stdlib.h>

#pragma intrinsic(_lrotr,_lrotl)
#define rotr(x,n)   _lrotr(x,n)
#define rotl(x,n)   _lrotl(x,n)

#endif

#define bit_swap(a,b,n,m)       \
	tt = ((a >> n) ^ b) & m;    \
	b ^= tt; a ^= (tt << n)

#define ip_old(x,y)                     \
	bit_swap((x),(y),  4, 0x0f0f0f0fL); \
	bit_swap((y),(x), 16, 0x0000ffffL); \
	bit_swap((x),(y),  2, 0x33333333L); \
	bit_swap((y),(x),  8, 0x00ff00ffL); \
	bit_swap((x),(y),  1, 0x55555555L); \
	(x) = rotl((x), 1);                 \
	(y) = rotl((y), 1)

#define fp_old(x,y)                     \
	(y) = rotr((y), 1);                 \
	(x) = rotr((x), 1);                 \
	bit_swap((x),(y),  1, 0x55555555L); \
	bit_swap((y),(x),  8, 0x00ff00ffL); \
	bit_swap((x),(y),  2, 0x33333333L); \
	bit_swap((y),(x), 16, 0x0000ffffL); \
	bit_swap((x),(y),  4, 0x0f0f0f0fL)

#define ip(x,y)                     \
	(x) = rotr((x), 4);             \
	tt = ((x) ^ (y)) & 0x0f0f0f0fL; \
	(y) ^= tt;                      \
	(x) = rotr((x) ^ tt, 12);       \
	tt = ((y) ^ (x)) & 0xffff0000L; \
	(y) ^= tt;                      \
	(x) = rotr((x) ^ tt, 18);       \
	tt = ((x) ^ (y)) & 0x33333333L; \
	(y) ^= tt;                      \
	(x) = rotr((x) ^ tt, 22);       \
	tt = ((y) ^ (x)) & 0xff00ff00L; \
	(y) ^= tt;                      \
	(x) = rotr((x) ^ tt,  9);       \
	tt = ((x) ^ (y)) & 0x55555555L; \
	(x) = rotl((x) ^ tt, 2);        \
	(y) = rotl((y) ^ tt, 1)

#define fp(x,y)                     \
	(y) = rotr((y), 1);             \
	(x) = rotr((x), 2);             \
	tt = ((x) ^ (y)) & 0x55555555L; \
	(y) ^= tt;                      \
	(x) = rotl((x) ^ tt,  9);       \
	tt = ((y) ^ (x)) & 0xff00ff00L; \
	(y) ^= tt;                      \
	(x) = rotl((x) ^ tt, 22);       \
	tt = ((x) ^ (y)) & 0x33333333L; \
	(y) ^= tt;                      \
	(x) = rotl((x) ^ tt, 18);       \
	tt = ((y) ^ (x)) & 0xffff0000L; \
	(y) ^= tt;                      \
	(x) = rotl((x) ^ tt, 12);       \
	tt = ((x) ^ (y)) & 0x0f0f0f0fL; \
	(y) ^= tt;                      \
	(x) = rotl((x) ^ tt, 4)

#ifdef  BIG_TABLES

#define round(x0,x1,ki)                                        \
	l1  = (rotr(x1, 4) ^ *(((unsigned long*)key) + ki + 1));   \
	l0  = (x1 ^ *(((unsigned long*)key) + ki));                \
	x0 ^= sx_tab[0][byte(l0,0)] | sx_tab[1][byte(l1,0)]        \
	| sx_tab[2][byte(l0,1)] | sx_tab[3][byte(l1,1)]        \
	| sx_tab[4][byte(l0,2)] | sx_tab[5][byte(l1,2)]        \
	| sx_tab[6][byte(l0,3)] | sx_tab[7][byte(l1,3)]

#else

#define round(x0,x1,ki)                                                     \
	l1  = (rotr(x1, 4) ^ *(((unsigned long*)key) + ki + 1)) & 0x3f3f3f3f;   \
	l0  = (x1 ^ *(((unsigned long*)key) + ki)) & 0x3f3f3f3f;                \
	x0 ^= sx_tab[0][byte(l0,0)] | sx_tab[1][byte(l1,0)]                     \
	| sx_tab[2][byte(l0,1)] | sx_tab[3][byte(l1,1)]                     \
	| sx_tab[4][byte(l0,2)] | sx_tab[5][byte(l1,2)]                     \
	| sx_tab[6][byte(l0,3)] | sx_tab[7][byte(l1,3)]

#endif

#ifdef  __cplusplus

extern "C"
{
	void des_ky(void *kval, void *key);
	void des_ec(const void *i_blk, void *o_blk, void *key);
	void des_dc(const void *i_blk, void *o_blk, void *key);
};

#else

void des_ky(void *kval, void *key);
void des_ec(const void *i_blk, void *o_blk, void *key);
void des_dc(const void *i_blk, void *o_blk, void *key);

#endif
//------------------------------------------------------------------------