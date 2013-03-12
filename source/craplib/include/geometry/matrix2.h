////////////////////////////////////////////////////////
// CRAP Library
//!		@file matrix2.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Simple dataholding matrix2 plus general operators
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_GEOMETRY_MATRIX2_H
#define CRAP_GEOMETRY_MATRIX2_H

#include "control/asserts.h"

//lib namespace
namespace crap
{

/*
 *! @todo iso c11 allows anonymous structs??
 */
template<typename T>
struct matrix2
{
	//! @brief data structure
	union
	{
		struct
		{
			T xx, xy,
			  yx, yy;
		};
		struct
		{
			T _11, _12,
			  _21, _22;
		};
		T m[2][2];
	};

	//! @brief default constructor
	matrix2(void);

	//! @brief copy constructor
	matrix2( const matrix2& other );

	//! @brief assigment operator
	matrix2& operator=( const matrix2& other );

	//! @brief brackets operator
	T& operator()( const size_t32& x, const size_t32& y );

	//! brief const bracket operator
	const T& operator()( const size_t32& x, const size_t32& y ) const;

	//! @brief plus-assigment operator
	matrix2& operator+=( const matrix2& right );

	//! @brief plus-assigment operator with T
	matrix2& operator+=( const T& value );

	//! @brief plus operator
	matrix2 operator+( const matrix2& right ) const;

	//! @brief plus operator using T
	matrix2 operator+( const T& value ) const;

	//! @brief minus-assigment operator
	matrix2& operator-=( const matrix2& right );

	//! @brief minus-assigment operator with T
	matrix2& operator-=( const T& value );

	//! @brief minus operator
	matrix2 operator-( const matrix2& right ) const;

	//! @brief minus operator using T
	matrix2 operator-( const T& value ) const;

	//! @brief multiply-assigment operator
	matrix2& operator*=( const matrix2& right );

	//! @brief multiply-assigment operator with T
	matrix2& operator*=( const T& value );

	//! @brief multiply operator
	matrix2 operator*( const matrix2& right ) const;

	//! @brief multiply operator using T
	matrix2 operator*( const T& value ) const;

	//! @brief divide-assigment operator with T
	matrix2& operator/=( const T& value );

	//! @brief divide operator using T
	matrix2 operator/( const T& value ) const;

};

template<typename T>
matrix2<T>::matrix2(void)
{
	memset(m,0,sizeof(m));
}

template<typename T>
matrix2<T>::matrix2( const matrix2& other )
{
	memcpy(m, other.m, sizeof(m));
}

template<typename T>
matrix2<T>& matrix2<T>::operator=( const matrix2& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	memcpy(m, other.m, sizeof(m));
	return *this;
}

template<typename T>
T& matrix2<T>::operator()( const size_t32& x, const size_t32& y )
{
	return m[y][x];
}

template<typename T>
const T& matrix2<T>::operator()( const size_t32& x, const size_t32& y ) const
{
	return m[y][x];
}

template<typename T>
matrix2<T>& matrix2<T>::operator+=( const matrix2& right )
{
	xx += right.xx;
	xy += right.xy;
	yx += right.yx;
	yy += right.yy;
	return *this;
}

template<typename T>
matrix2<T>& matrix2<T>::operator+=( const T& value )
{
	xx += value;
	xy += value;
	yx += value;
	yy += value;
	return *this;
}

template<typename T>
matrix2<T> matrix2<T>::operator+( const matrix2& right ) const
{
	matrix2 rtn(*this);
	rtn += right;
	return rtn;
}

template<typename T>
matrix2<T> matrix2<T>::operator+( const T& value ) const
{
	matrix2 rtn(*this);
	rtn += value;
	return rtn;
}

template<typename T>
matrix2<T>& matrix2<T>::operator-=( const matrix2& right )
{
	xx -= right.xx;
	xy -= right.xy;
	yx -= right.yx;
	yy -= right.yy;
	return *this;
}

template<typename T>
matrix2<T>& matrix2<T>::operator-=( const T& value )
{
	xx -= value;
	xy -= value;
	yx -= value;
	yy -= value;
	return *this;
}

template<typename T>
matrix2<T> matrix2<T>::operator-( const matrix2& right ) const
{
	matrix2 rtn(*this);
	rtn -= right;
	return rtn;
}

template<typename T>
matrix2<T> matrix2<T>::operator-( const T& value ) const
{
	matrix2 rtn(*this);
	rtn -= value;
	return rtn;
}

template<typename T>
matrix2<T>& matrix2<T>::operator*=( const matrix2& right )
{
	xx = xx * right.xx + xy * right.yx;
	xy = xx * right.xy + xy * right.yy;

	yx = yx * right.xx + yy * right.yx;
	yy = yx * right.xy + yy * right.yy;
	return *this;
}

template<typename T>
matrix2<T>& matrix2<T>::operator*=( const T& value )
{
	xx *= value;
	xy *= value;
	yx *= value;
	yy *= value;
	return *this;
}

template<typename T>
matrix2<T> matrix2<T>::operator*( const matrix2& right ) const
{
	matrix2 rtn(*this);
	rtn *= right;
	return rtn;
}

template<typename T>
matrix2<T> matrix2<T>::operator*( const T& value ) const
{
	matrix2 rtn(*this);
	rtn *= value;
	return rtn;
}


template<typename T>
matrix2<T>& matrix2<T>::operator/=( const T& value )
{
	xx /= value;
	xy /= value;
	yx /= value;
	yy /= value;
	return *this;
}


template<typename T>
matrix2<T> matrix2<T>::operator/( const T& value ) const
{
	matrix2 rtn(*this);
	rtn /= value;
	return rtn;
}

//typedefs
typedef matrix2<i16> matrix2s;
typedef matrix2<i32> matrix2i;
typedef matrix2<i64> matrix2l;
typedef matrix2<f32> matrix2f;
typedef matrix2<f64> matrix2d;

}	//namespace crap

#endif // CRAP_GEOMETRY_MATRIX2_H
