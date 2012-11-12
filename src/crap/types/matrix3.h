////////////////////////////////////////////////////////
// CRAP Library
//!		@file matrix3.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Simple dataholding matrix3 plus general operators
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_MATRIX3_H
#define CRAP_MATRIX3_H

#include "control/asserts.h"

//lib namespace
namespace crap
{

/*
 *! @todo iso c11 allows anonymous structs??
 */
template<typename T>
struct matrix3
{
	//! @brief data structure
	union
	{
		struct
		{
			T xx, xy, xz,
			  yx, yy, yz,
			  zx, zy, zz;
		};
		struct
		{
			T _11, _12, _13,
			  _21, _22, _23,
			  _31, _32, _33;
		};
		T m[3][3];
	};

	//! @brief default constructor
	matrix3(void);

	//! @brief copy constructor
	matrix3( const matrix3& other );

	//! @brief assigment operator
	matrix3& operator=( const matrix3& other );

	//! @brief brackets operator
	T& operator()( const size_t32& x, const size_t32& y );

	//! brief const bracket operator
	const T& operator()( const size_t32& x, const size_t32& y ) const;

	//! @brief plus-assigment operator
	matrix3& operator+=( const matrix3& right );

	//! @brief plus-assigment operator with T
	matrix3& operator+=( const T& value );

	//! @brief plus operator
	matrix3 operator+( const matrix3& right ) const;

	//! @brief plus operator using T
	matrix3 operator+( const T& value ) const;

	//! @brief minus-assigment operator
	matrix3& operator-=( const matrix3& right );

	//! @brief minus-assigment operator with T
	matrix3& operator-=( const T& value );

	//! @brief minus operator
	matrix3 operator-( const matrix3& right ) const;

	//! @brief minus operator using T
	matrix3 operator-( const T& value ) const;

	//! @brief multiply-assigment operator
	matrix3& operator*=( const matrix3& right );

	//! @brief multiply-assigment operator with T
	matrix3& operator*=( const T& value );

	//! @brief multiply operator
	matrix3 operator*( const matrix3& right ) const;

	//! @brief multiply operator using T
	matrix3 operator*( const T& value ) const;

	//! @brief divide-assigment operator with T
	matrix3& operator/=( const T& value );

	//! @brief divide operator using T
	matrix3 operator/( const T& value ) const;

};

template<typename T>
matrix3<T>::matrix3(void)
{
	memset(m,0,sizeof(m));
}

template<typename T>
matrix3<T>::matrix3( const matrix3& other )
{
	memcpy(m, other.m, sizeof(m));
}

template<typename T>
matrix3<T>& matrix3<T>::operator=( const matrix3& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	memcpy(m, other.m, sizeof(m));
	return *this;
}

template<typename T>
T& matrix3<T>::operator()( const size_t32& x, const size_t32& y )
{
	return m[y][x];
}

template<typename T>
const T& matrix3<T>::operator()( const size_t32& x, const size_t32& y ) const
{
	return m[y][x];
}

template<typename T>
matrix3<T>& matrix3<T>::operator+=( const matrix3& right )
{
	xx += right.xx;
	xy += right.xy;
	xz += right.xz;
	yx += right.yx;
	yy += right.yy;
	yz += right.yz;
	zx += right.zx;
	zy += right.zy;
	zz += right.zz;
	return *this;
}

template<typename T>
matrix3<T>& matrix3<T>::operator+=( const T& value )
{
	xx += value;
	xy += value;
	xz += value;
	yx += value;
	yy += value;
	yz += value;
	zx += value;
	zy += value;
	zz += value;
	return *this;
}

template<typename T>
matrix3<T> matrix3<T>::operator+( const matrix3& right ) const
{
	matrix3 rtn(*this);
	rtn += right;
	return rtn;
}

template<typename T>
matrix3<T> matrix3<T>::operator+( const T& value ) const
{
	matrix3 rtn(*this);
	rtn += value;
	return rtn;
}

template<typename T>
matrix3<T>& matrix3<T>::operator-=( const matrix3& right )
{
	xx -= right.xx;
	xy -= right.xy;
	xz -= right.xz;
	yx -= right.yx;
	yy -= right.yy;
	yz -= right.yz;
	zx -= right.zx;
	zy -= right.zy;
	zz -= right.zz;
	return *this;
}

template<typename T>
matrix3<T>& matrix3<T>::operator-=( const T& value )
{
	xx -= value;
	xy -= value;
	xz -= value;
	yx -= value;
	yy -= value;
	yz -= value;
	zx -= value;
	zy -= value;
	zz -= value;
	return *this;
}

template<typename T>
matrix3<T> matrix3<T>::operator-( const matrix3& right ) const
{
	matrix3 rtn(*this);
	rtn -= right;
	return rtn;
}

template<typename T>
matrix3<T> matrix3<T>::operator-( const T& value ) const
{
	matrix3 rtn(*this);
	rtn -= value;
	return rtn;
}

template<typename T>
matrix3<T>& matrix3<T>::operator*=( const matrix3& right )
{
	xx = xx * right.xx + xy * right.yx + xz * right.zx;
	xy = xx * right.xy + xy * right.yy + xz * right.zy;
	xz = xx * right.xz + xy * right.yz + xz * right.zz;

	yx = yx * right.xx + yy * right.yx + yz * right.zx;
	yy = yx * right.xy + yy * right.yy + yz * right.zy;
	yz = yx * right.xz + yy * right.yz + yz * right.zz;

	zx = zx * right.xx + zy * right.yx + zz * right.zx;
	zy = zx * right.xy + zy * right.yy + zz * right.zy;
	zz = zx * right.xz + zy * right.yz + zz * right.zz;
	return *this;
}

template<typename T>
matrix3<T>& matrix3<T>::operator*=( const T& value )
{
	xx *= value;
	xy *= value;
	xz *= value;
	yx *= value;
	yy *= value;
	yz *= value;
	zx *= value;
	zy *= value;
	zz *= value;
	return *this;
}

template<typename T>
matrix3<T> matrix3<T>::operator*( const matrix3& right ) const
{
	matrix3 rtn(*this);
	rtn *= right;
	return rtn;
}

template<typename T>
matrix3<T> matrix3<T>::operator*( const T& value ) const
{
	matrix3 rtn(*this);
	rtn *= value;
	return rtn;
}


template<typename T>
matrix3<T>& matrix3<T>::operator/=( const T& value )
{
	xx /= value;
	xy /= value;
	xz /= value;
	yx /= value;
	yy /= value;
	yz /= value;
	zx /= value;
	zy /= value;
	zz /= value;
	return *this;
}


template<typename T>
matrix3<T> matrix3<T>::operator/( const T& value ) const
{
	matrix3 rtn(*this);
	rtn /= value;
	return rtn;
}

//typedefs
typedef matrix3<i16> mat3s;
typedef matrix3<i32> mat3i;
typedef matrix3<i64> mat3l;
typedef matrix3<f32> mat3f;
typedef matrix3<f64> mat3d;

}	// namespace crap

#endif // CRAP_MATRIX3_H
