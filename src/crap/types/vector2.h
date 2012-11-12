////////////////////////////////////////////////////////
// CRAP Library
//!		@file vector2.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Simple dataholding vector2 plus general operators
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_VECTOR2_H
#define CRAP_VECTOR2_H

#include "control/asserts.h"

//lib namespace
namespace crap
{

//! @brief template struct
template<typename T>
struct vector2
{
	//data with public access
	T x,y;

	//! @brief standard constructor
	vector2( void );

	//! @brief copy constructor
	vector2( const vector2& other );

	//! @brief value construcor
	vector2( const T& xx, const T& yy );

	//! @brief destructor
	~vector2( void );

	//! @brief assignment operator
	vector2& operator=( const vector2& other );

	//! @brief plus-assign operator
	vector2& operator+=( const vector2& other );

	//! @brief plus-assign operator using T
	vector2& operator+=( const T& value );

	//! @brief plus operator
	vector2 operator+(const vector2& right) const;

	//! @brief plus operator adding T to each value
	vector2 operator+( const T& right) const;

	//! @brief minus-assign operator
	vector2& operator-=( const vector2& other );

	//! @brief minus-assign operator using T
	vector2& operator-=( const T& value );

	//! @brief minus operator
	vector2 operator-( const vector2& right ) const;

	//! @brief minus operator subtracting T from each value
	vector2 operator-( const T& right ) const;

	//! @brief multiply-assign operator
	vector2& operator*=( const vector2& other );

	//! @brief multiply-assign operator using T
	vector2& operator*=( const T& value );

	//! @brief multiply operator
	vector2 operator*( const vector2& right ) const;

	//! @brief multiply operator using T
	vector2 operator*( const T& right ) const;

	//! @brief divisor-assign operator
	vector2& operator/=( const vector2& other );

	//! @brief divisor-assign operator using T
	vector2& operator/=( const T& value );

	//! @brief divisor operator
	vector2 operator/( const vector2& right) const;

	//! @brief divisor operator using T
	vector2 operator/( const T& right) const;
};

template<typename T>
vector2<T>::vector2( void ) : x(0), y(0)
{

}

template<typename T>
vector2<T>::vector2( const vector2& other ) : x(other.x), y(other.y)
{

}

template<typename T>
vector2<T>::vector2( const T& xx, const T& yy ) : x(xx), y(yy)
{

}

template<typename T>
vector2<T>::~vector2( void )
{

}

template<typename T>
vector2<T>& vector2<T>::operator=( const vector2& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	x = other.x;
	y = other.y;
	return *this;
}

template<typename T>
vector2<T>& vector2<T>::operator+=( const vector2& other )
{
	x += other.x;
	y += other.y;
	return *this;
}

template<typename T>
vector2<T>& vector2<T>::operator+=( const T& value )
{
	x += value;
	y += value;
	return *this;
}

template<typename T>
vector2<T> vector2<T>::operator+( const vector2& right ) const
{
	vector2 left(*this);
	left += right;
	return left;
}

template<typename T>
vector2<T> vector2<T>::operator+( const T& right ) const
{
	vector2 left(*this);
	left.x += right;
	left.y += right;
	return left;
}

template<typename T>
vector2<T>& vector2<T>::operator-=( const vector2& other )
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template<typename T>
vector2<T>& vector2<T>::operator-=( const T& value )
{
	x -= value;
	y -= value;
	return *this;
}

template<typename T>
vector2<T> vector2<T>::operator-( const vector2& right ) const
{
	vector2 left(*this);
	left -= right;
	return left;
}

template<typename T>
vector2<T> vector2<T>::operator-( const T& right ) const
{
	vector2 left(*this);
	left.x -= right;
	left.y -= right;
	return left;
}

template<typename T>
vector2<T>& vector2<T>::operator*=( const vector2& other )
{
	x *= other.x;
	y *= other.y;
	return *this;
}

template<typename T>
vector2<T>& vector2<T>::operator*=( const T& value )
{
	x *= value;
	y *= value;
	return *this;
}


template<typename T>
vector2<T> vector2<T>::operator*( const vector2& right ) const
{
	vector2 left(*this);
	left *= right;
	return left;
}

template<typename T>
vector2<T> vector2<T>::operator*( const T& right ) const
{
	vector2 left(*this);
	left.x *= right;
	left.y *= right;
	return left;
}

template<typename T>
vector2<T>& vector2<T>::operator/=( const vector2& other )
{
	x /= other.x;
	y /= other.y;
	return *this;
}

template<typename T>
vector2<T>& vector2<T>::operator/=( const T& value )
{
	x /= value;
	y /= value;
	return *this;
}

template<typename T>
vector2<T> vector2<T>::operator/( const vector2& right ) const
{
	vector2 left(*this);
	left /= right;
	return left;
}

template<typename T>
vector2<T> vector2<T>::operator/( const T& right ) const
{
	vector2 left(*this);
	left.x /= right;
	left.y /= right;
	return left;
}

//typedefs
typedef vector2<i16> vec2s;
typedef vector2<i32> vec2i;
typedef vector2<i64> vec2l;
typedef vector2<f32> vec2f;
typedef vector2<f64> vec2d;

}	// namespace crap

#endif // CRAP_VECTOR2_H
