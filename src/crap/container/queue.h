////////////////////////////////////////////////////////
// CRAP Library
//		@file static_queue.h
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
//		@brief Queue container class, currently contains
//		stl implementation plus a simple and fast 
//		static queue
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_QUEUE_H
#define CRAP_CONTAINER_QUEUE_H

#include <queue>
#include "control/copyobject.h"
#include "memory/allocatordefault.h"

//lib namespace
namespace crap
{
	
/*
 * @brief Queue class
 */	

template<typename T, typename Allocator = crap::allocator_default<T> >
class queue : public std::queue<T, Allocator>
{

};

/*
 * @brief Static queue class
 */

template<typename T, size_t32 S>
class static_queue
{
private:

	/*
	 * Class members
	 */
	 
    T _array[S];
    size_t32 _size;
    size_t32 _front;

public:

	// @brief standard constructor
    static_queue( void );

	// @brief copy constructor
    static_queue( const static_queue& other );

	// @brief assignment operator
    static_queue& operator=( const static_queue& other );

	// @brief returns current size
    size_t32 size( void ) const;

	// @brief returns total size
    size_t32 max_size( void ) const;

	// @brief returns if queue is empty
    bool is_empty( void ) const;

	// @brief returns if queue is full
    bool is_full( void ) const;

	// @brief returns reference to front
    T& front( void );
	
	// @brief returns const reference to front
    const T& front( void ) const;

	// @brief returns reference to back
    T& back( void );

	// @brief returns const reference to back
    const T& back( void ) const;

	// @brief pushes element to end of queue
    void push( const T& object );

	// @brief pops element at front of queue
    void pop( void );

	// @brief clear queue
    void clear( void );

	// @brief stream operator
    template<typename U, u64 V>
	friend std::ostream& operator<<( std::ostream& out, const static_queue<U,V>& other );
};

/*
 * Implementations
 */
 
//constructor
template<typename T, size_t32 S>
static_queue<T,S>::static_queue( void ) : _size(0), _front(0) 
{
}

//copy constructor
template<typename T, size_t32 S>
static_queue<T,S>::static_queue( const static_queue& other ) : _size( other._size ), _front( other._front )
{
	copy_array( other._array, _array, S);
}

//assignment operator
template<typename T, size_t32 S>
static_queue<T,S>& static_queue<T,S>::operator=( const static_queue& other )
{
	_size = other._size;
	_front = other._front;
	copy_array( other._array, _array, S );
	return *this;
}

//current size
template<typename T, size_t32 S>
size_t32 static_queue<T,S>::size( void ) const
{
	return _size;
}

//total size
template<typename T, size_t32 S>
size_t32 static_queue<T,S>::max_size( void ) const
{
	return S;
}

//returns if empty
template<typename T, size_t32 S>
bool static_queue<T,S>::is_empty( void ) const
{
    return _size == 0;
}

//returns if full
template<typename T, size_t32 S>
bool static_queue<T,S>::is_full( void ) const
{
	return _size == S;
}

//front element
template<typename T, size_t32 S>
T& static_queue<T,S>::front( void )
{
	CRAP_ASSERT_DEBUG( !is_empty(), "Static queue empty" );
	return _array[(_front) % S];
}

//const front element
template<typename T, size_t32 S>
const T& static_queue<T,S>::front( void ) const
{
	CRAP_ASSERT_DEBUG( !is_empty(), "Static queue empty" );
	return _array[(_front) % S];
}

//back element
template<typename T, size_t32 S>
T& static_queue<T,S>::back( void )
{
	CRAP_ASSERT_DEBUG( !is_empty(), "Static queue empty" );
	return _array[(_front + _size -1) % S];
}

//const back element
template<typename T, size_t32 S>
const T& static_queue<T,S>::back( void ) const
{
	CRAP_ASSERT_DEBUG( !is_empty(), "Static queue empty" );
	return _array[(_front + _size -1) % S];
}

//push element back
template<typename T, size_t32 S>
void static_queue<T,S>::push( const T& object )
{
	CRAP_ASSERT_DEBUG( !is_full(), "Static queue full" );
	_array[(_front + _size) % S] = object;
	++_size;
}

//pop element fron
template<typename T, size_t32 S>
void static_queue<T,S>::pop( void )
{
	CRAP_ASSERT_DEBUG( !is_empty(), "Static queue empty" );
	_front = (_front+1) % S;
	--_size;
}

//clear queue
template<typename T, size_t32 S>
void static_queue<T,S>::clear( void )
{
	_size = 0 ;
}

//stream operator
template<typename U, u64 V>
std::ostream& operator<<( std::ostream& out, const static_queue<U,V>& other )
{
    for( u64 i=0; i<other._size; ++i )
    	out << other._array[ (other._front + i) % V ] << " ";

	out << std::endl;
    return out;
}

}	// namespace crap


#endif // CRAP_CONTAINER_QUEUE_H
