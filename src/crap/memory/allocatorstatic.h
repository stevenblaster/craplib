////////////////////////////////////////////////////////
//	CRAP Library
//!		@file allocatorstatic.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Allocator using fixed number of alloctions
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_MEMORY_ALLOCATORSTATIC_H
#define CRAP_MEMORY_ALLOCATORSTATIC_H

#include "container/bitset.h"
#include "control/copyobject.h"

// lib namespace
namespace crap
{

template<typename T, size_t32 S>
class allocator_static
{
private:

	//bitset for indexing memory
	crap::bit_set<S> _index;
	u8 _memory[ sizeof(T) * S ];

public:

	//typedefs
	typedef T 					value_type;
	typedef value_type* 		pointer;
	typedef const value_type* 	const_pointer;
	typedef value_type& 		reference;
	typedef const value_type& 	const_reference;
	typedef std::size_t 		size_type;			//TODO
	typedef	std::ptrdiff_t		difference_type;	//TODO

	//! @brief rebind struct
	template<typename U>
	struct rebind
	{
		typedef allocator_static<U> other;
	};

	//! @brief constructor
	CRAP_INLINE explicit
	allocator_static();

	//! @brief destructor
	CRAP_INLINE
	~allocator_static();

	//! @brief copy constructor
	CRAP_INLINE explicit
	allocator_static( const allocator_static& other );

	//! @brief template copy constructor
	template<typename U>
	CRAP_INLINE explicit
	allocator_static( const allocator_static<U>& other );

	//! @brief return address of reference
	CRAP_INLINE 
	pointer address(reference r);

	//! @brief return const address of const reference
	CRAP_INLINE
	const_pointer address(const_reference r);

	//! @brief allocate amount of elements
	CRAP_INLINE
	pointer allocate(size_type cnt = 1, typename allocator_static<T>::const_pointer = 0);

	//! @brief deallocate amount of elements
	CRAP_INLINE
	void deallocate(pointer p, size_type s=1);

	//! @brief return maximum allocations
	CRAP_INLINE 
	size_type max_size( void ) const;

	//! @brief call constructor on object
	CRAP_INLINE 
	void construct(pointer p, const T& t);

	//! @brief call destructor on pointer
	CRAP_INLINE
	void destroy(pointer p);

	//! @brief comparision equal operator
	CRAP_INLINE
	bool operator==( const allocator_static& other );

	//! @brief conparision not equal operator
	CRAP_INLINE
	bool operator!=(allocator_static const& a);
};

//definitions

//cosntructor
template<typename T, size_t32 S>
explicit allocator_static<T,S>::allocator_static()
{
	_index.reset();
}

//destructor
template<typename T, size_t32 S>
allocator_static<T,S>::~allocator_static()
{

}

//copy constructor
template<typename T, size_t32 S>
allocator_static<T,S>::allocator_static( const allocator_static& other )
{
	_index = other._index;
	crap::copy_array( other._memory, _memory, S );
}

//template copy constructor
template<typename T, size_t32 S>
template<typename U>
allocator_static<T,S>::allocator_static( const allocator_static<U,S>& other )
{
	_index.reset();
}

// return address of reference
template<typename T, size_t32 S>
allocator_static<T,S>::pointer allocator_static<T,S>::address(reference r)
{
	return &r;
}

// return const address of const reference
template<typename T, size_t32 S>
allocator_static<T,S>::const_pointer allocator_static<T,S>::address(const_reference r)
{
	return &r;
}

//allocate amount of elements
template<typename T, size_t32 S>
allocator_static<T,S>::pointer allocator_static<T,S>::allocate(size_type cnt = 1, typename allocator_static<T>::const_pointer = 0)
{
	size_t32 position = _index.find_unset();

	while( position != -1 )
	{
		if( _index.find_set( position, count ) != -1 )
			position = _index.find_unset( position + _index.find_set( position, count ) );
		else
			break;
	}

	ASSERT_DEBUG( position != -1, "Could not allocate sufficiant block" );
	_index.set( position, count );
	return static_cast<T*>( &_memory[position * sizeof(T)] )
}

//deallocate amount of elements
template<typename T, size_t32 S>
void allocator_static<T,S>::deallocate(pointer p, size_type s=1)
{
	for( size_t32 i=0; i<S; ++i )
	{
		if( static_cast<T*>( _memory[i*sizeof(T)] ) == ptr )
		{
			_index.reset( i, count );
			return;
		}
	}
	ASSERT_ERROR( "Pointer not found in MemoryArray" );
}

// return maximum allocations
template<typename T, size_t32 S>
allocator_static<T,S>::size_type allocator_static<T,S>::max_size( void ) const
{
	return S;
}

// call constructor on object
template<typename T, size_t32 S>
void allocator_static<T,S>::construct(pointer p, const T& t)
{
	new(p) T(t);
}

// call destructor on pointer
template<typename T, size_t32 S>
void allocator_static<T,S>::destroy(pointer p)
{
	p->~T();
}

// comparision equal operator
template<typename T, size_t32 S>
bool allocator_static<T,S>::operator==( const allocator_static& other )
{
	return (void*)_memory == (void*)other._memory;
}

//conparision not equal operator
template<typename T, size_t32 S>
bool allocator_static<T,S>::operator!=( const allocator_static& a )
{
	return !operator==(a);
}

} //lib namespace

#endif CRAP_MEMORY_ALLOCATORSTATIC_H