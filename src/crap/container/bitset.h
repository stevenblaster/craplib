////////////////////////////////////////////////////////
// CRAP Library
//		@file bitset.h
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
//		@brief The container allocates memory
//		and allows bit manipulation
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_BITSET_H
#define CRAP_CONTAINER_BITSET_H

#include "container/bitmask.h"

//lib namespace
namespace crap
{
	
/*
 * @brief Bit manipulating template class
 */

template<size_t32 S>
class bit_set : public bit_mask
{
private:

	/*
	 * Class members
	 */
	
	u8 _memory[S]; // memory for mask
	
public:
	
	// @brief default constructor
	bit_set(void);
	
	// @brief copy constructor
	bit_set( const bit_set& other );
	
	// @brief destructor
	~bit_set( void );
	
	// @brief assignment operator
	bit_set& operator=( const bit_set& other );
	
	// @brief assignment operator with pointer
	bit_set& operator=( void* other );

	// @brief plus-equal operator
	bit_set& operator+=( const bit_set& other );
	
	// @brief plus-equal operator with pointer
	bit_set& operator+=( void* other );

	// @brief minus-equal operator
    bit_set& operator-=( const bit_set& other );
	
	// @brief minus-equal operator with pointer
    bit_set& operator-=( void* other );
	
	// @brief stream operator
	template<size_t32 U>
    friend std::ostream& operator<<( std::ostream& out, const bit_set<U>& bitmask );
};

/*
 * definitions
 */

//constructor
template<size_t32 S>
bit_set<S>::bit_set( void ) : bit_mask( _memory, S )
{
	reset();
}

//copy constructor
template<size_t32 S>
bit_set<S>::bit_set( const bit_set& other ) : bit_mask( _memory, S)
{
	memcpy( _memory, other._memory, S );
}

//destructor
template<size_t32 S>
bit_set<S>::~bit_set( void )
{

}

//assignment operator
template<size_t32 S>
bit_set<S>& bit_set<S>::operator=( const bit_set& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	memcpy( _memory, other._memory, S );
	return *this;
}

//assignment operator
template<size_t32 S>
bit_set<S>& bit_set<S>::operator=( void* other )
{
	CRAP_ASSERT_DEBUG(_memory != other, "Assignment operator on same pointer");
	memcpy( _memory, other, S );
	return *this;
}

//plus equal
template<size_t32 S>
bit_set<S>& bit_set<S>::operator+=( const bit_set& other )
{
	this->bit_mask += other.bit_mask;
	return *this;
}

//plus equal
template<size_t32 S>
bit_set<S>& bit_set<S>::operator+=( void* other )
{
	this->bit_mask += other;
	return *this;
}

//minus equal
template<size_t32 S>
bit_set<S>& bit_set<S>::operator-=( const bit_set& other )
{
	this->bit_mask -= other.bit_mask;
	return *this;
}

//minus equal
template<size_t32 S>
bit_set<S>& bit_set<S>::operator-=( void* other )
{
	this->bit_mask -= other;
	return *this;
}

//stream operator
template<size_t32 U>
std::ostream& operator<<( std::ostream& out, const bit_set<U>& bitset )
{
	out << bitset.bit_mask;
	return out;
}


}	// namespace crap

#endif // CRAP_CONTAINER_BITSET_H
