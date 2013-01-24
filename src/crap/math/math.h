////////////////////////////////////////////////////////
//	CRAP Library
//!		@file math.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Math functions using approximation and
// 		SSE instructions
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_MATH_MATH_H
#define CRAP_MATH_MATH_H

#include "config/math.h"

//lib namespace
namespace crap
{

class math
{
private:

	typedef
	union f32i32_t
	{
		f32 f; i32 i;
	} f32i32_t;

	static CRAP_INLINE i32
	f32toi32( const f32& x )
	{
//		union f32i32 { f32 f; i32 i; } uni;
		f32i32_t uni;
		uni.f = x;
		return uni.i;
	}

	static CRAP_INLINE f32
	i32tof32( const i32& x )
	{
//		union f32i32 { f32 f; i32 i; } uni;
		f32i32_t uni;
		uni.i = x;
		return uni.f;
	}

	static CRAP_INLINE f32
	inf( void )
	{
		return i32tof32(0x7F800000);
	}

	static CRAP_INLINE f32
	nan( void )
	{
		return i32tof32(0x7FC00000);
	}

	static CRAP_INLINE b8
	intSign( const f32& x )
	{
		i32 a = f32toi32(x);
		return (a > 0) && ((u32)a < 0x80000000U);
	}

	static CRAP_INLINE b8
	intSignDiff(const f32& x, const f32& y)
	{
		return ( f32toi32(x) ^ f32toi32(y) ) < 0;
	}

	static CRAP_INLINE f32
	fabs(const f32& x)
	{
		return i32tof32( f32toi32(x) & ~0x80000000 );
	}

	static CRAP_INLINE i32
	intFloor(const f32& x)
	{
		CRAP_ASSERT_DEBUG ( -4194304.0F <= x && x <= 4194303.0F , "intFloor limits overflow");

		/*i32 a = f32toi32( (3 << 22) + 0.5 + (f64) x );
		i32 b = f32toi32( (3 << 22) + 0.5 - (f64) x );*/

		i32 a = f32toi32( (3 << 22) + 0.5f + x );
		i32 b = f32toi32( (3 << 22) + 0.5f - x );
		return (a - b) >> 1;
	}

	static CRAP_INLINE i32
	intCeil( const f32& x )
	{
		CRAP_ASSERT_DEBUG ( -4194304.0F <= x && x <= 4194303.0F , "intFloor limits overflow");

		/*i32 a = f32toi32((3 << 22) + 0.5 + (f64) x);
		i32 b = f32toi32((3 << 22) + 0.5 - (f64) x);*/

		i32 a = f32toi32((3 << 22) + 0.5f + x);
		i32 b = f32toi32((3 << 22) + 0.5f - x);
		return (a - b + 1) >> 1;
	}

	static CRAP_INLINE i32
	intRound( const f32& x )
	{
	#if defined(CRAP_COMPILER_GCC) // && defined __i386__
		i32 res;
		__asm__ __volatile__ (
		  "fistpl %0 @n@t"
		: "=m" (res) : "t" (x) : "st");
		return res;
	#else
		return crap::math::intFloor(x + 0.5F);
	#endif
	}

	static CRAP_INLINE f32
	reCip( const f32& x )
	{
		CRAP_ASSERT_DEBUG ( x != 0.0F, "X is zero" );

	#if defined(CRAP_COMPILER_GCC)  && (CRAP_SIMD_VERSION >= CRAP_SIMD_SSE)
		f32 z;
		__asm__ __volatile__ (
		  "movss     %1, %%xmm0 @n@t"
		  "rcpss %%xmm0, %%xmm0 @n@t"
		  "movss %%xmm0, %0     @n@t"
		: "=m" (z) : "m" (x) : "xmm0", "memory");
		return z;
	#else
		f32 z = i32tof32( 0x7F000000 - f32toi32(x) );
		z *= 2.0F - z * x;
		return z;
	#endif
	}

	static CRAP_INLINE f32
	rsqrt( const f32& x )
	{
		CRAP_ASSERT_DEBUG (x >= 0.0F, "X is smaller or equal to zero.");

	#if defined(CRAP_COMPILER_GCC)  && (CRAP_SIMD_VERSION >= CRAP_SIMD_SSE)
		f32 z;
		__asm__ __volatile__ (
		  "movss       %1, %%xmm0 @n@t"
		  "rsqrtss %%xmm0, %%xmm0 @n@t"
		  "movss   %%xmm0, %0     @n@t"
		: "=m" (z) : "m" (x) : "xmm0", "memory");
	#else
		f32 z = i32tof32((0xBE6EFCBA - f32toi32(x)) >> 1);
		z *= 0.5F * (3.0F - z * z * x); /* repeat. */
	#endif
		z *= 0.5F * (3.0F - z * z * x);
		return z;
	}

	static CRAP_INLINE f32
	sqrt(const f32& x)
	{
		CRAP_ASSERT_DEBUG (x >= 0.0F, "Squareroot from zero or less");
		return x * crap::math::rsqrt(x);
	}

	static CRAP_INLINE f32
	eps( const f32& x )
	{
		return ( crap::math::fabs(x) + 1.0F ) * CRAP_EPSILON;
	}

	static CRAP_INLINE i32
	eqz( const f32& x )
	{
		return crap::math::fabs(x) <= CRAP_EPSILON;
	}

	static CRAP_INLINE i32
	neqz( const f32& x )
	{
		return ! crap::math::eqz(x);
	}

	static CRAP_INLINE i32
	eq( const f32& x, const f32& y )
	{
		return crap::math::fabs(x - y) <= crap::math::eps(x);
	}

	static CRAP_INLINE i32
	neq( const f32& x, const f32& y )
	{
		return ! crap::math::eq(x, y);
	}

	static CRAP_INLINE i32
	lt( const f32& x, const f32& y )
	{
		return x < y - crap::math::eps(x);
	}

	static CRAP_INLINE i32
	gt( const f32& x, const f32& y )
	{
		return crap::math::lt(y, x);
	}

	static CRAP_INLINE i32
	leq( const f32& x, const f32& y )
	{
		return ! crap::math::gt(x, y);
	}

	static CRAP_INLINE i32
	geq( const f32& x, const f32& y )
	{
		return ! crap::math::lt(x, y);
	}

	static CRAP_INLINE f32
	fmin( const f32& a, const f32& b )
	{
		return a < b ? a : b;
	}

	static CRAP_INLINE f32
	fmax( const f32& a, const f32& b )
	{
		return a > b ? a : b;
	}

	static CRAP_INLINE f32
	clamp( const f32& x, const f32& a, const f32& b )
	{
		return crap::math::fmax( a, crap::math::fmin(b, x) );
	}

	static CRAP_INLINE f32
	sat( const f32& x )
	{
		return crap::math::clamp( x, 0.0F, 1.0F );
	}

	static CRAP_INLINE f32
	norm( const f32& x )
	{
		return x * 0.5F + 0.5F;
	}

	static CRAP_INLINE f32
	unit( const f32& x )
	{
		return x * 2.0F - 1.0F;
	}

	static CRAP_INLINE f32
	mean( const f32& x, const f32& y )
	{
		return (x + y) * 0.5F;
	}

	static CRAP_INLINE f32
	degree( const f32& x )
	{
		return x * ( 180.0F / CRAP_PI );
	}

	static CRAP_INLINE f32
	radian( const f32& x )
	{
		return x * ( CRAP_PI / 180.0F );
	}

	static CRAP_INLINE f32
	exp2approx( const f32& x )
	{
		f32 t0, t1;
		t1 =  x;
		t0 =           		0.1369765902E-1F;
		t0 = t0 * t1 + 	0.5169038746E-1F;
		t0 = t0 * t1 + 	0.2416384127F;
		t0 = t0 * t1 + 	0.6929661329F;
		t0 = t0 * t1 + 	1.0000037040F;
		return t0;
	}

	static CRAP_INLINE f32
	log2approx( const f32& x )
	{
		f32 t0, t1;
		t1 =  x;
		t0 =         		- 8.161580995E-2F;
		t0 = t0 * t1 + 	6.451423713E-1F;
		t0 = t0 * t1 - 	2.120675146F;
		t0 = t0 * t1 + 	4.070090803F;
		t0 = t0 * t1 - 	2.512854628F;
		return t0;
	}

	static CRAP_INLINE f32
	cosapprox( const f32& x )
	{
		f32 t0, t1;
		t1 =  x * x;
		t0 =         		- 0.0000002605F;
		t0 = t0 * t1 + 	0.0000247609F;
		t0 = t0 * t1 - 	0.0013888397F;
		t0 = t0 * t1 + 	0.0416666418F;
		t0 = t0 * t1 - 	0.4999999963F;
		t0 = t0 * t1 + 	1.0F;
		return t0;
	}

	static CRAP_INLINE f32
	arccosapprox( const f32& x )
	{
		f32 t0, t1;
		t1 =  x;
		t0 =         		- 0.0187293F;
		t0 = t0 * t1 + 	0.0742610F;
		t0 = t0 * t1 - 	0.2121144F;
		t0 = t0 * t1 + 	CRAP_PI_HALF;
		return t0;
	}

	static CRAP_INLINE f32
	arctanapprox( const f32& x )
	{
		f32 t0, t1;
		t1 =  x * x;
		t0 =         		- 0.013480470F;
		t0 = t0 * t1 + 	0.057477314F;
		t0 = t0 * t1 - 	0.121239071F;
		t0 = t0 * t1 + 	0.195635925F;
		t0 = t0 * t1 - 	0.332994597F;
		t0 = t0 * t1 + 	0.999995630F;
		t0 = t0 * x;
		return t0;
	}

public:

	static CRAP_INLINE f32
	modf( const f32& x, f32* p )
	{
		f32i32_t ux, ur;
		i32 mask;
		ux.f = x;
		ur.i = ((ux.i & ~0x80000000) >> 23) - 127;
		p[0] = 0.0F;

		if (ur.i >= 0)
		{
			mask = (1 << (23 - ur.i)) - 1;
			ur.i = ux.i & ~mask;
			ux.f = x - ur.f;
			p[0] = ur.f;
		}
		return ux.f;
	}

	static CRAP_INLINE f32
	trunc( const f32& x )
	{
		f32 res;
		crap::math::modf( x, &res );
		return res;
	}

	static CRAP_INLINE f32
	frac( const f32& x)
	{
		f32 nil;
		return crap::math::modf(x, &nil);
	}

	static CRAP_INLINE f32
	fmod( const f32& x, const f32& y )
	{
		CRAP_ASSERT_DEBUG( y != 0.0F, "Y is zero" );
		return y * crap::math::frac( x / y );
	}

	static CRAP_INLINE f32
	drem( const f32& x, const f32& y )
	{
		CRAP_ASSERT_DEBUG( y != 0.0F, "Y is zero" );
		return x - y * crap::math::intRound( x / y );
	}

	static CRAP_INLINE f32
	wrap( const f32& x, const f32& y )
	{
		CRAP_ASSERT_DEBUG( y != 0.0F, "Y is zero" );
		return x - y * crap::math::intFloor(x / y);
	}

	//static CRAP_INLINE f32
	//crap::math::wrap2(f32, f32 min, f32 max);

	static CRAP_INLINE f32
	log2( const f32& x )
	{
		CRAP_ASSERT_DEBUG( x >= 0.0F, "X higher/euqal zero" );
		f32i32_t u;
		i32 lg2;
		u.f = x;
		lg2 = (u.i >> 23) - 127;
		u.i = (u.i & ~0x7F800000) | 0x3F800000;
		return crap::math::log2approx(u.f) + lg2;
	}

	static CRAP_INLINE f32
	log( const f32& x )
	{
		CRAP_ASSERT_DEBUG( x >= 0.0F, "X higher/euqal zero" );
		return crap::math::log2(x) * CRAP_LN_2;
	}

	static CRAP_INLINE f32
	exp2( const f32& x )
	{
		f32i32_t ux, ur;
		i32 xneg, xexp;
		ur.f = x;
		ux.i = ur.i & ~0x80000000;
		xneg = ux.i != ur.i;
		xexp = (ux.i >> 23) - 127;
		ur.f = 1.0F;

		if (xneg != 0 && xexp > 4)
			return 0.0F;

		if (xexp > 0)
		{
			ur.i = (ux.i & 0x7FFFFF) | 0x800000;
			ur.i = ((ur.i >> (23 - xexp)) + 127) << 23;
			ux.i = ((ux.i << xexp) & 0x7FFFFF) | 0x3F800000;
			ux.f = ux.f - 1.0F;
		}

		ur.f = ur.f * crap::math::exp2approx(ux.f);

		if (xneg == 0)
			return ur.f;

		return 1.0F / ur.f;
	}

	static CRAP_INLINE f32
	exp( const f32& x )
	{
		return crap::math::exp2( x * CRAP_LOG2E );
	}

	static CRAP_INLINE f32
	pow( const f32& x, const f32& y )
	{
		CRAP_ASSERT_DEBUG (x >= 0.0F || y == crap::math::trunc(y), "X lower then zero or y != trunc(y)");

		if ( f32toi32(crap::math::fabs(x)) != 0)
		{
			if ( f32toi32(crap::math::fabs(y)) != 0x3F800000 )
				return crap::math::exp2(y * crap::math::log2(crap::math::fabs(x)));

			if ( f32toi32(y) & 0x80000000 )
				return 1.0F / x;

			return x;
		}
		return 0.0F;
	}

	static CRAP_INLINE f32
	cos( const f32& x )
	{
		f32 cres;
		i32 quad = 0;
		f32 y = crap::math::wrap( x, CRAP_PI * 2 );

		if ( y > CRAP_PI )
		{
			y = CRAP_PI * 2 - y;
		}

		if ( y > CRAP_PI_HALF )
		{
			y = CRAP_PI - y;
			quad |= 1;
		}

		cres = crap::math::cosapprox(y);
		return (quad & 1) ? -cres : cres;
	}

	static CRAP_INLINE f32
	sin( const f32& x )
	{
		return crap::math::cos( CRAP_PI_HALF - x );
	}

	static CRAP_INLINE void
	sincos( const f32& x, f32* s, f32* c )
	{
		f32 sres, cres;
		i32 quad = 0;
		f32 y = crap::math::wrap( x, CRAP_PI * 2 );

		if ( y > CRAP_PI )
		{
			y = CRAP_PI * 2 - y;
			quad |= 2;
		 }

		if ( y > CRAP_PI_HALF )
		{
			y = CRAP_PI - y;
			quad |= 1;
		}

		sres = crap::math::cosapprox( CRAP_PI_HALF - y );
		cres = crap::math::cosapprox(x);

		s[0] = (quad & 2) ? -sres : sres;
		c[0] = (quad & 1) ? -cres : cres;
	}

	static CRAP_INLINE f32
	tan( const f32& x )
	{
		f32 s, c;
		crap::math::sincos(x, &s, &c);
		return s / c;
	}

	static CRAP_INLINE f32
	cosh( const f32& x )
	{
		return 0.5F * ( crap::math::exp(x) + crap::math::exp(-x) );
	}

	static CRAP_INLINE f32
	sinh( const f32& x )
	{
		return 0.5F * ( crap::math::exp(x) - crap::math::exp(-x) );
	}

	static CRAP_INLINE f32
	tanh( const f32& x )
	{
		f32 t = crap::math::exp( 2.0F * x );
		return ( t - 1.0F ) / ( t + 1.0F );
	}

	static CRAP_INLINE f32
	acos( const f32& x )
	{
		CRAP_ASSERT_DEBUG( -1.0F <= x && x <= 1.0F, "X not between -1 and 1" );

		f32 neg, t;
		neg = (f32) ( x < 0.0F );
		f32 y = crap::math::fabs(x);

		t = crap::math::arccosapprox(y);
		t = t * crap::math::sqrt(1.0F - y);
		t = t - 2.0F * neg * t;
		return neg * CRAP_PI + t;
	}

	static CRAP_INLINE f32
	asin( const f32& x )
	{
		CRAP_ASSERT_DEBUG( -1.0F <= x && x <= 1.0F, "X not between -1 and 1" );

		f32 neg, t;
		neg = (f32) ( x < 0.0F );
		f32 y = crap::math::fabs(x);

		t = crap::math::arccosapprox(y);
		t = CRAP_PI_HALF - t * crap::math::sqrt( 1.0F - y );
		return t - 2.0F * neg * t;
	}

	static CRAP_INLINE f32
	atan2( const f32& y, const f32& x )
	{
		f32 ax, ay;
		f32 t0, t1;
		ax = crap::math::fabs(x);
		ay = crap::math::fabs(y);
		t0 = crap::math::fmax(ax, ay);
		t1 = crap::math::fmin(ax, ay);

		t0 = 1.0F / t0;
		t0 = crap::math::arctanapprox(t0 * t1);

		t0 = (ax < ay)  ? CRAP_PI_HALF - t0 : t0;
		t0 = (x < 0.0F) ? CRAP_PI - t0 : t0;
		t0 = (y < 0.0F) ? -t0 : t0;
		return t0;
	}

	static CRAP_INLINE f32
	atan( const f32& x )
	{
		return crap::math::atan2( x, 1.0F );
	}

	static CRAP_INLINE f32
	acosh( const f32& x )
	{
		CRAP_ASSERT_DEBUG ( x > 1.0F, "X not bigger then 1" );
		return crap::math::log(x + crap::math::sqrt( x * x - 1.0F ));
	}

	static CRAP_INLINE f32
	asinh( const f32& x )
	{
		return crap::math::log(x + crap::math::sqrt( x * x + 1.0F ));
	}

	static CRAP_INLINE f32
	atanh( const f32& x )
	{
		CRAP_ASSERT_DEBUG( -1.0F <= x && x <= 1.0F, "X not between -1 and 1" );
		return 0.5F * (crap::math::log(1.0F + x) - crap::math::log(1.0F - x));
	}

};

}	// namespace crap


#endif // CRAP_MATH_MATH_H
