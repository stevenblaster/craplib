////////////////////////////////////////////////////////
// CRAP Library
//!		@file matrix4.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Simple dataholding matrix4 plus general operators
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_GEOMETRY_MATRIX4_H
#define CRAP_GEOMETRY_MATRIX4_H

#include "control/asserts.h"
#include "math/vector3.h"

//lib namespace
namespace crap
{

/*
 *! @todo iso c11 allows anonymous structs??
 */
template<typename T>
struct matrix4
{
	//! @brief data structure
	union
	{
		struct
		{
			T xx, xy, xz, xw,
			  yx, yy, yz, yw,
			  zx, zy, zz, zw,
			  wx, wy, wz, ww;
		};
		struct
		{
			T _11, _12, _13, _14,
			  _21, _22, _23, _24,
			  _31, _32, _33, _34,
			  _41, _42, _43, _44;
		};
		T m[4][4];
	};

	//! @brief default constructor
	matrix4(void);

	//! @brief copy constructor
	matrix4( const matrix4& other );

	//! @brief assigment operator
	matrix4& operator=( const matrix4& other );

	//! @brief brackets operator
	T& operator()( const size_t32& x, const size_t32& y );

	//! brief const bracket operator
	const T& operator()( const size_t32& x, const size_t32& y ) const;

	//! @brief plus-assigment operator
	matrix4& operator+=( const matrix4& right );

	//! @brief plus-assigment operator with T
	matrix4& operator+=( const T& value );

	//! @brief plus operator
	matrix4 operator+( const matrix4& right ) const;

	//! @brief plus operator using T
	matrix4 operator+( const T& value ) const;

	//! @brief minus-assigment operator
	matrix4& operator-=( const matrix4& right );

	//! @brief minus-assigment operator with T
	matrix4& operator-=( const T& value );

	//! @brief minus operator
	matrix4 operator-( const matrix4& right ) const;

	//! @brief minus operator using T
	matrix4 operator-( const T& value ) const;

	//! @brief multiply-assigment operator
	matrix4& operator*=( const matrix4& right );

	//! @brief multiply-assigment operator with T
	matrix4& operator*=( const T& value );

	//! @brief multiply operator
	matrix4 operator*( const matrix4& right ) const;

	//! @brief multiply operator using T
	matrix4 operator*( const T& value ) const;

	//! @brief divide-assigment operator with T
	matrix4& operator/=( const T& value );

	//! @brief divide operator using T
	matrix4 operator/( const T& value ) const;

};

template<typename T>
matrix4<T>::matrix4(void)
{
	memset(m,0,sizeof(m));
}

template<typename T>
matrix4<T>::matrix4( const matrix4& other )
{
	memcpy(m, other.m, sizeof(m));
}

template<typename T>
matrix4<T>& matrix4<T>::operator=( const matrix4& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	memcpy(m, other.m, sizeof(m));
	return *this;
}

template<typename T>
T& matrix4<T>::operator()( const size_t32& x, const size_t32& y )
{
	return m[y][x];
}

template<typename T>
const T& matrix4<T>::operator()( const size_t32& x, const size_t32& y ) const
{
	return m[y][x];
}

template<typename T>
matrix4<T>& matrix4<T>::operator+=( const matrix4& right )
{
	xx += right.xx;
	xy += right.xy;
	xz += right.xz;
	xw += right.xw;
	yx += right.yx;
	yy += right.yy;
	yz += right.yz;
	yw += right.yw;
	zx += right.zx;
	zy += right.zy;
	zz += right.zz;
	zw += right.zw;
	wx += right.wx;
	wy += right.wy;
	wz += right.wz;
	ww += right.ww;
	return *this;
}

template<typename T>
matrix4<T>& matrix4<T>::operator+=( const T& value )
{
	xx += value;
	xy += value;
	xz += value;
	xw += value;
	yx += value;
	yy += value;
	yz += value;
	yw += value;
	zx += value;
	zy += value;
	zz += value;
	zw += value;
	wx += value;
	wy += value;
	wz += value;
	ww += value;
	return *this;
}

template<typename T>
matrix4<T> matrix4<T>::operator+( const matrix4& right ) const
{
	matrix4 rtn(*this);
	rtn += right;
	return rtn;
}

template<typename T>
matrix4<T> matrix4<T>::operator+( const T& value ) const
{
	matrix4 rtn(*this);
	rtn += value;
	return rtn;
}

template<typename T>
matrix4<T>& matrix4<T>::operator-=( const matrix4& right )
{
	xx -= right.xx;
	xy -= right.xy;
	xz -= right.xz;
	xw -= right.xw;
	yx -= right.yx;
	yy -= right.yy;
	yz -= right.yz;
	yw -= right.yw;
	zx -= right.zx;
	zy -= right.zy;
	zz -= right.zz;
	zw -= right.zw;
	wx -= right.wx;
	wy -= right.wy;
	wz -= right.wz;
	ww -= right.ww;

	return *this;
}

template<typename T>
matrix4<T>& matrix4<T>::operator-=( const T& value )
{
	xx -= value;
	xy -= value;
	xz -= value;
	xw -= value;
	yx -= value;
	yy -= value;
	yz -= value;
	yw -= value;
	zx -= value;
	zy -= value;
	zz -= value;
	zw -= value;
	wx -= value;
	wy -= value;
	wz -= value;
	ww -= value;
	return *this;
}

template<typename T>
matrix4<T> matrix4<T>::operator-( const matrix4& right ) const
{
	matrix4 rtn(*this);
	rtn -= right;
	return rtn;
}

template<typename T>
matrix4<T> matrix4<T>::operator-( const T& value ) const
{
	matrix4 rtn(*this);
	rtn -= value;
	return rtn;
}

template<typename T>
matrix4<T>& matrix4<T>::operator*=( const matrix4& right )
{
	xx = xx * right.xx + xy * right.yx + xz * right.zx + xw * right.wx;
	xy = xx * right.xy + xy * right.yy + xz * right.zy + xw * right.wy;
	xz = xx * right.xz + xy * right.yz + xz * right.zz + xw * right.wz;
	xw = xx * right.xw + xy * right.yw + xz * right.zw + xw * right.ww;

	yx = yx * right.xx + yy * right.yx + yz * right.zx + yw * right.wx;
	yy = yx * right.xy + yy * right.yy + yz * right.zy + yw * right.wy;
	yz = yx * right.xz + yy * right.yz + yz * right.zz + yw * right.wz;
	yw = yx * right.xw + yy * right.yw + yz * right.zw + yw * right.ww;

	zx = zx * right.xx + zy * right.yx + zz * right.zx + zw * right.wx;
	zy = zx * right.xy + zy * right.yy + zz * right.zy + zw * right.wy;
	zz = zx * right.xz + zy * right.yz + zz * right.zz + zw * right.wz;
	zw = zx * right.xw + zy * right.yw + zz * right.zw + zw * right.ww;

	wx = wx * right.xx + wy * right.yx + wz * right.zx + ww * right.wx;
	wy = wx * right.xy + wy * right.yy + wz * right.zy + ww * right.wy;
	wz = wx * right.xz + wy * right.yz + wz * right.zz + ww * right.wz;
	ww = wx * right.xw + wy * right.yw + wz * right.zw + ww * right.ww;
	return *this;
}

template<typename T>
matrix4<T>& matrix4<T>::operator*=( const T& value )
{
	xx *= value;
	xy *= value;
	xz *= value;
	xw *= value;
	yx *= value;
	yy *= value;
	yz *= value;
	yw *= value;
	zx *= value;
	zy *= value;
	zz *= value;
	zw *= value;
	wx *= value;
	wy *= value;
	wz *= value;
	ww *= value;
	return *this;
}

template<typename T>
matrix4<T> matrix4<T>::operator*( const matrix4& right ) const
{
	matrix4 rtn(*this);
	rtn *= right;
	return rtn;
}

template<typename T>
matrix4<T> matrix4<T>::operator*( const T& value ) const
{
	matrix4 rtn(*this);
	rtn *= value;
	return rtn;
}


template<typename T>
matrix4<T>& matrix4<T>::operator/=( const T& value )
{
	xx /= value;
	xy /= value;
	xz /= value;
	xw /= value;
	yx /= value;
	yy /= value;
	yz /= value;
	yw /= value;
	zx /= value;
	zy /= value;
	zz /= value;
	zw /= value;
	wx /= value;
	wy /= value;
	wz /= value;
	ww /= value;
	return *this;
}


template<typename T>
matrix4<T> matrix4<T>::operator/( const T& value ) const
{
	matrix4 rtn(*this);
	rtn /= value;
	return rtn;
}


//typedefs
typedef matrix4<i16> matrix4s;
typedef matrix4<i32> matrix4i;
typedef matrix4<i64> matrix4l;
typedef matrix4<f32> matrix4f;
typedef matrix4<f64> matrix4d;

}	// namespace crap

#endif // CRAP_GEOMETRY_MATRIX4_H
