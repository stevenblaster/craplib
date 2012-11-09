////////////////////////////////////////////////////////
// CRAP Library
//		@file staticstack.h
//
//	Creator:
//		Steffen Kopany <steffen@kopany.at>
//
//	Author(s):
// 		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright (c) 2012 Steffen Kopany
//
//	Description:
//		@brief The container is simply said a stack
//		with fixed static size. It doesnt use allocators
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_STATICSTACK_H
#define CRAP_CONTAINER_STATICSTACK_H

#include "memory/allocatordefault.h"
#include "control/copyobject.h"
#include <stack>

//lib namespace
namespace crap
{

/*
 * @brief Stack template class
 */

template<typename T, typename Allocator = crap::allocator_default<T> >
class stack : public std::stack<T, Allocator>
{
};

/*
 * @brief Static stack template class
 */

template<typename T, size_t32 S>
class static_stack
{
private:
	T _array[S];
	size_t32 _size;

public:

	// @brief default constructor
	static_stack( void );

	// @brief copy constructor
	static_stack( const static_stack& other );

	// @brief assignment operator
	static_stack& operator=( const static_stack& other );

	// @brief returns current size of stack
	size_t32 size( void ) const;
	
	// @brief returns maximum size of stack
	size_t32 max_size( void ) const;

	// @brief returns if stack is empty
	bool is_empty( void ) const;
	
	// @brief returns if stack is full
	bool is_full( void ) const;

	// @brief returns reference to front object
	T& top( void );
	
	// @brief returns const reference to front object
	const T& top( void ) const;

	// @brief push new object to top of stack
	void push( const T& object );
	
	// @brief pop top element of stack
	void pop( void );

	// @brief clear stack
	void clear( void );
	
	// @brief stream operator
    template<typename U, u64 V>
	friend std::ostream& operator<<( std::ostream& out, const static_stack<U,V>& other );
};


template<typename T, size_t32 S>
static_stack<T,S>::static_stack( void ) : _size(0) 
{
}

template<typename T, size_t32 S>
static_stack<T,S>::static_stack( const static_stack& other ) : _size( other._size )
{
	copy_array( other._array, _array, S);
}

template<typename T, size_t32 S>
static_stack<T,S>& static_stack<T,S>::operator=( const static_stack& other )
{
	_size = other._size;
	copy_array( other._array, _array, S);
	return *this;
}

template<typename T, size_t32 S>
size_t32 static_stack<T,S>::size( void ) const
{
	return _size; 
}
	
template<typename T, size_t32 S>
size_t32 static_stack<T,S>::max_size( void ) const
{ 
	return S;
}

template<typename T, size_t32 S>
bool static_stack<T,S>::is_empty( void ) const
{
	return _size == 0;
}
	
template<typename T, size_t32 S>
bool static_stack<T,S>::is_full( void ) const
{
	return _size == S;
}

template<typename T, size_t32 S>
T& static_stack<T,S>::top( void )
{
	return _array[_size - 1];
}
	
template<typename T, size_t32 S>
const T& static_stack<T,S>::top( void ) const
{
	return _array[_size - 1];
}

template<typename T, size_t32 S>
void static_stack<T,S>::push( const T& object )
{
	CRAP_ASSERT_DEBUG( !is_full(), "QuickStack full" );
	_array[_size++] = object;
}
	
template<typename T, size_t32 S>
void static_stack<T,S>::pop( void )
{
	_size -= ( _size > 0 ) ? 1 : 0;
}

template<typename T, size_t32 S>
void static_stack<T,S>::clear( void )
{
	_size = 0 ;
}


}	// namespace crap

#endif // CRAP_CONTAINER_STATICSTACK_H
