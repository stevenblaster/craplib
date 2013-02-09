////////////////////////////////////////////////////////
// CRAP Library
//!		@file vector3.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Simple dataholding vector3 plus general operators
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_VECTOR3_H
#define CRAP_VECTOR3_H

#include "control/asserts.h"

//lib namespace
namespace crap
{

//! @brief template struct
template<typename T>
struct vector3
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

	//! @brief standard constructor
	vector3( void );

	//! @brief copy constructor
	vector3( const vector3& other );

	//! @brief value construcor
	vector3(const T& xx, const T& yy, const T& zz );

	//! @brief destructor
	~vector3( void );

	//! @brief assignment operator
	vector3& operator=( const vector3& other );

	//! @brief plus-assign operator
	vector3& operator+=( const vector3& other );

	//! @brief plus-assign operator using T
	vector3& operator+=( const T& value );

	//! @brief plus operator
	vector3 operator+(const vector3& right) const;

	//! @brief plus operator adding T to each value
	vector3 operator+( const T& right) const;

	//! @brief minus-assign operator
	vector3& operator-=( const vector3& other );

	//! @brief minus-assign operator using T
	vector3& operator-=( const T& value );

	//! @brief minus operator
	vector3 operator-( const vector3& right ) const;

	//! @brief minus operator subtracting T from each value
	vector3 operator-( const T& right ) const;

	//! @brief multiply-assign operator
	vector3& operator*=( const vector3& other );

	//! @brief multiply-assign operator using T
	vector3& operator*=( const T& other );

	//! @brief multiply operator
	vector3 operator*( const vector3& right ) const;

	//! @brief multiply operator using T
	vector3 operator*( const T& right ) const;

	//! @brief divisor-assign operator
	vector3& operator/=( const vector3& other );

	//! @brief divisor-assign operator using T
	vector3& operator/=( const T& value );

	//! @brief divisor operator
	vector3 operator/( const vector3& right) const;

	//! @brief divisor operator using T
	vector3 operator/( const T& right) const;
};

template<typename T>
vector3<T>::vector3( void ) : x(0), y(0), z(0)
{

}

template<typename T>
vector3<T>::vector3( const vector3& other ) : x(other.x), y(other.y), z(other.z)
{

}

template<typename T>
vector3<T>::vector3(const T& xx, const T& yy , const T& zz) : x(xx), y(yy), z(zz)
{

}

template<typename T>
vector3<T>::~vector3( void )
{

}

template<typename T>
vector3<T>& vector3<T>::operator=( const vector3& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

template<typename T>
vector3<T>& vector3<T>::operator+=( const vector3& other )
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

template<typename T>
vector3<T>& vector3<T>::operator+=( const T& value )
{
	x += value;
	y += value;
	z += value;
	return *this;
}

template<typename T>
vector3<T> vector3<T>::operator+( const vector3& right ) const
{
	vector3 left(*this);
	left += right;
	return left;
}

template<typename T>
vector3<T> vector3<T>::operator+( const T& right ) const
{
	vector3 left(*this);
	left.x += right;
	left.y += right;
	left.z += right;
	return left;
}

template<typename T>
vector3<T>& vector3<T>::operator-=( const vector3& other )
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

template<typename T>
vector3<T>& vector3<T>::operator-=( const T& value )
{
	x -= value;
	y -= value;
	z -= value;
	return *this;
}


template<typename T>
vector3<T> vector3<T>::operator-( const vector3& right ) const
{
	vector3 left(*this);
	left -= right;
	return left;
}

template<typename T>
vector3<T> vector3<T>::operator-( const T& right ) const
{
	vector3 left(*this);
	left.x -= right;
	left.y -= right;
	left.z -= right;
	return left;
}

template<typename T>
vector3<T>& vector3<T>::operator*=( const vector3& other )
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

template<typename T>
vector3<T>& vector3<T>::operator*=( const T& value )
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

template<typename T>
vector3<T> vector3<T>::operator*( const vector3& right ) const
{
	vector3 left(*this);
	left *= right;
	return left;
}

template<typename T>
vector3<T> vector3<T>::operator*( const T& right ) const
{
	vector3 left(*this);
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}

template<typename T>
vector3<T>& vector3<T>::operator/=( const vector3& other )
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

template<typename T>
vector3<T>& vector3<T>::operator/=( const T& value )
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

template<typename T>
vector3<T> vector3<T>::operator/( const vector3& right ) const
{
	vector3 left(*this);
	left /= right;
	return left;
}

template<typename T>
vector3<T> vector3<T>::operator/( const T& right ) const
{
	vector3 left(*this);
	left.x /= right;
	left.y /= right;
	left.z /= right;
	return left;
}

//typedefs
typedef vector3<i16> vector3s;
typedef vector3<i32> vector3i;
typedef vector3<i64> vector3l;
typedef vector3<f32> vector3f;
typedef vector3<f64> vector3d;

}	// namespace crap

#endif // CRAP_VECTOR3_H
