////////////////////////////////////////////////////////
//	CRAP Library
//!		@file bitmask.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief The container receives a certain
//		memory address and allows bit manipulation
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_BITMASK_H
#define CRAP_CONTAINER_BITMASK_H

#include "control/asserts.h"

//lib namespace
namespace crap
{

/*
 *! @brief Bit manipulating class
 */

class bit_mask
{

protected:

	/*
	 * Class members
	 */

	void* _pointer;		//start of memory
	size_t32 _bits;		//number of bits
	size_t32 _bytes;	//number of bytes

public:

	//! @brief Default constructor
	bit_mask( void );

	//! @brief Copy constructor
	bit_mask( const bit_mask& other );

	//! @brief Constructer using parameters for initialization
	bit_mask( void* pointer , size_t32 size);

	//! @brief Destructor
	~bit_mask( void );

	//! @brief Initialization
	void init( void* pointer , size_t32 size);

	//! @brief Assignment operator
	bit_mask& operator=( const bit_mask& other );

	//! @brief Assignment operator - using void pointer and old size
	bit_mask& operator=( void* other );

	//! @brief Plus equal operator
	bit_mask& operator+=( const bit_mask& other );

	//! @brief Plus equal operator - using void pointer and old size
	bit_mask& operator+=( void* other );

	//! @brief Minus equal operator
	bit_mask& operator-=( const bit_mask& other );

	//! @brief Minus equal operator - using void pointer and old size
	bit_mask& operator-=( void* other );

	//! @brief Comparision operator
	bool operator==( const bit_mask& other ) const;

	//! @brief Comparision operator - using void pointer and old size
	bool operator==( void* other ) const;

	//! @brief Accessor on certain bit
	bool operator[]( size_t32 position ) const;

	//! @brief Test if all bits are set
	bool test( void ) const;

	//! @brief Test if certain bit is set
	bool test( size_t32 position ) const;

	//! @brief Test if a sequence of bits is set, lenght as number of bits
	bool test( size_t32 position, size_t32 lenght ) const;

	//! @brief Set all bits
	void set( void );

	//! @brief Set certain bit
	void set( size_t32 position );

	//! @brief Set a sequence of bits
	void set( size_t32 position, size_t32 lenght );

	//! @brief Reset all bits
	void reset( void );

	//! @brief Reset certain bit
	void reset( size_t32 position );

	//! @brief Reset a sequence of bits
	void reset( size_t32 from, size_t32 to );

	//! @brief Flip all bits
	void flip( void );

	//! @brief Flip certain bit
	void flip( size_t32 position );

	//! @brief Flip a sequence of bits
	void flip( size_t32 from, size_t32 to );

	//! @brief Find first set bit from position, returns -1 is failed
	i32 find_set( size_t32 position = 0 ) const;

	//! @brief Find first set bit in sequence, returns -1 is failed
	i32 find_set( size_t32 from, size_t32 length ) const;

	//! @brief Find first unset bit from position, returns -1 is failed
	i32 find_unset( size_t32 position = 0 ) const;

	//! @brief Find first set bit in sequence, returns -1 is failed
	i32 find_unset( size_t32 from, size_t32 length) const;

	//! @brief Return pointer to memory
	void* pointer( void ) const;

	//! @brief Return size of manipulated bits
	size_t32 size( void ) const;

	//! @brief Return size of manipulated bytes
	size_t32 used_bytes( void ) const;

	//! @brief Declare stream operator as friend
	friend std::ostream& operator<<( std::ostream& out, const bit_mask& bitmask );
};

}	// namespace crap

#endif // CRAP_CONTAINER_BITMASK_H
