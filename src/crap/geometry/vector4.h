////////////////////////////////////////////////////////
// CRAP Library
//!		@file vector4.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Simple dataholding vector4 plus general operators
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_VECTOR4_H
#define CRAP_VECTOR4_H

#include "control/asserts.h"

//lib namespace
namespace crap
{

//! @brief template struct
template<typename T>
struct vector4
{
	//data with public access
	union
	{
		T x;
		T r;
	};

	union
	{
		T y;
		T g;
	};

	union
	{
		T z;
		T b;
	};

	union
	{
		T w;
		T a;
		T i; //for quaternion - the imaginary number
	};

	//! @brief standard constructor
	vector4( void );

	//! @brief copy constructor
	vector4( const vector4& other );

	//! @brief value construcor
	vector4(const T& xx, const T& yy, const T& zz, const T& ww );

	//! @brief destructor
	~vector4( void );

	//! @brief assignment operator
	vector4& operator=( const vector4& other );

	//! @brief plus-assign operator
	vector4& operator+=( const vector4& other );

	//! @brief plus-assign operator using T
	vector4& operator+=( const T& other );

	//! @brief plus operator
	vector4 operator+(const vector4& right) const;

	//! @brief plus operator adding T to each value
	vector4 operator+( const T& right) const;

	//! @brief minus-assign operator
	vector4& operator-=( const vector4& other );

	//! @brief minus-assign operator using T
	vector4& operator-=( const T& other );

	//! @brief minus operator
	vector4 operator-( const vector4& right ) const;

	//! @brief minus operator subtracting T from each value
	vector4 operator-( const T& right ) const;

	//! @brief multiply-assign operator
	vector4& operator*=( const vector4& other );

	//! @brief multiply-assign operator using T
	vector4& operator*=( const T& other );

	//! @brief multiply operator
	vector4 operator*( const vector4& right ) const;

	//! @brief multiply operator using T
	vector4 operator*( const T& right ) const;

	//! @brief divisor-assign operator
	vector4& operator/=( const vector4& other );

	//! @brief divisor-assign operator using T
	vector4& operator/=( const T& other );

	//! @brief divisor operator
	vector4 operator/( const vector4& right) const;

	//! @brief divisor operator using T
	vector4 operator/( const T& right) const;
};

template<typename T>
vector4<T>::vector4( void ) : x(0), y(0), z(0), w(0)
{

}

template<typename T>
vector4<T>::vector4( const vector4& other ) : x(other.x), y(other.y), z(other.z), w(other.w)
{

}

template<typename T>
vector4<T>::vector4(const T& xx, const T& yy , const T& zz, const T& ww) : x(xx), y(yy), z(zz), w(ww)
{

}

template<typename T>
vector4<T>::~vector4( void )
{

}

template<typename T>
vector4<T>& vector4<T>::operator=( const vector4& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

template<typename T>
vector4<T>& vector4<T>::operator+=( const vector4& other )
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

template<typename T>
vector4<T>& vector4<T>::operator+=( const T& value )
{
	x += value;
	y += value;
	z += value;
	w += value;
	return *this;
}

template<typename T>
vector4<T> vector4<T>::operator+( const vector4& right ) const
{
	vector4 left(*this);
	left += right;
	return left;
}

template<typename T>
vector4<T> vector4<T>::operator+( const T& right ) const
{
	vector4 left(*this);
	left.x += right;
	left.y += right;
	left.z += right;
	left.w += right;
	return left;
}

template<typename T>
vector4<T>& vector4<T>::operator-=( const vector4& other )
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

template<typename T>
vector4<T>& vector4<T>::operator-=( const T& value )
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;
	return *this;
}


template<typename T>
vector4<T> vector4<T>::operator-( const vector4& right ) const
{
	vector4 left(*this);
	left -= right;
	return left;
}

template<typename T>
vector4<T> vector4<T>::operator-( const T& right ) const
{
	vector4 left(*this);
	left.x -= right;
	left.y -= right;
	left.z -= right;
	left.w -= right;
	return left;
}

template<typename T>
vector4<T>& vector4<T>::operator*=( const vector4& other )
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

template<typename T>
vector4<T>& vector4<T>::operator*=( const T& value )
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}

template<typename T>
vector4<T> vector4<T>::operator*( const vector4& right ) const
{
	vector4 left(*this);
	left *= right;
	return left;
}

template<typename T>
vector4<T> vector4<T>::operator*( const T& right ) const
{
	vector4 left(*this);
	left.x *= right;
	left.y *= right;
	left.z *= right;
	left.w *= right;
	return left;
}

template<typename T>
vector4<T>& vector4<T>::operator/=( const vector4& other )
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	return *this;
}

template<typename T>
vector4<T>& vector4<T>::operator/=( const T& value )
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
	return *this;
}

template<typename T>
vector4<T> vector4<T>::operator/( const vector4& right ) const
{
	vector4 left(*this);
	left /= right;
	return left;
}

template<typename T>
vector4<T> vector4<T>::operator/( const T& right ) const
{
	vector4 left(*this);
	left.x /= right;
	left.y /= right;
	left.z /= right;
	left.w /= right;
	return left;
}

//typedefs
typedef vector4<i16> vector4s;
typedef vector4<i32> vector4i;
typedef vector4<i64> vector4l;
typedef vector4<f32> vector4f;
typedef vector4<f64> vector4d;

//quaternion
template<typename T>
struct quaternion : public vector4<T> {};

}	// namespace crap

#endif // CRAP_VECTOR4_H
