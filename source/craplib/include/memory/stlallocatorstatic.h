////////////////////////////////////////////////////////
//	CRAP Library
//!		@file stlallocatorstatic.h
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
class stl_allocator_static
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
    typedef size_t32	 		size_type;			//TODO
    typedef	std::ptrdiff_t		difference_type;	//TODO

    //! @brief rebind struct
    template<typename U, size_t32 V>
    struct rebind
    {
        typedef stl_allocator_static<U,V> other;
    };

    //! @brief constructor
    CRAP_INLINE explicit
    stl_allocator_static();

    //! @brief destructor
    CRAP_INLINE
    ~stl_allocator_static();

    //! @brief copy constructor
    CRAP_INLINE explicit
    stl_allocator_static( const stl_allocator_static& other );

    //! @brief template copy constructor
    template<typename U, size_t32 V>
    CRAP_INLINE explicit
    stl_allocator_static( const stl_allocator_static<U,V>& other );

    //! @brief return address of reference
    CRAP_INLINE
    pointer address(reference r);

    //! @brief return const address of const reference
    CRAP_INLINE
    const_pointer address(const_reference r);

    //! @brief allocate amount of elements
    CRAP_INLINE
    pointer allocate(size_type cnt = 1, typename stl_allocator_static<T,S>::const_pointer = 0);

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
    bool operator==( const stl_allocator_static& other );

    //! @brief conparision not equal operator
    CRAP_INLINE
    bool operator!=(stl_allocator_static const& a);
};

//definitions

//cosntructor
template<typename T, size_t32 S>
stl_allocator_static<T,S>::stl_allocator_static()
{
    _index.reset();
}

//destructor
template<typename T, size_t32 S>
stl_allocator_static<T,S>::~stl_allocator_static()
{

}

//copy constructor
template<typename T, size_t32 S>
stl_allocator_static<T,S>::stl_allocator_static( const stl_allocator_static& other )
{
    _index = other._index;
    crap::copy_array( other._memory, _memory, S );
}

//template copy constructor
template<typename T, size_t32 S>
template<typename U, size_t32 V>
stl_allocator_static<T,S>::stl_allocator_static( const stl_allocator_static<U,V>& other )
{
    _index.reset();
}

// return address of reference
template<typename T, size_t32 S>
T* stl_allocator_static<T,S>::address(reference r)
{
    return &r;
}

// return const address of const reference
template<typename T, size_t32 S>
const T* stl_allocator_static<T,S>::address(const_reference r)
{
    return &r;
}

//allocate amount of elements
template<typename T, size_t32 S>
T* stl_allocator_static<T,S>::allocate(size_type cnt /* = 1 */, typename stl_allocator_static<T,S>::const_pointer ptr /*= 0*/)
{
    size_t32 position = _index.find_unset();

    while( position != -1 )
    {
        if( _index.find_set( position, cnt ) != -1 )
            position = _index.find_unset( position + _index.find_set( position, cnt ) );
        else
            break;
    }

    CRAP_ASSERT_DEBUG( position != -1, "Could not allocate sufficiant block" );
    _index.set( position, cnt );
    return static_cast<T*>( (void*)&_memory[position * sizeof(T)] );
}

//deallocate amount of elements
template<typename T, size_t32 S>
void stl_allocator_static<T,S>::deallocate(pointer p, size_type s /*=1*/)
{
    for( size_t32 i=0; i<S; ++i )
    {
        if( static_cast<T*>( (void*)&_memory[i*sizeof(T)] ) == p )
        {
            _index.reset( i, s );
            return;
        }
    }
    CRAP_ASSERT_ERROR( "Pointer not found in MemoryArray" );
}

// return maximum allocations
template<typename T, size_t32 S>
size_t32 stl_allocator_static<T,S>::max_size( void ) const
{
    return S;
}

// call constructor on object
template<typename T, size_t32 S>
void stl_allocator_static<T,S>::construct(pointer p, const T& t)
{
    new(p) T(t);
}

// call destructor on pointer
template<typename T, size_t32 S>
void stl_allocator_static<T,S>::destroy(pointer p)
{
    p->~T();
}

// comparision equal operator
template<typename T, size_t32 S>
bool stl_allocator_static<T,S>::operator==( const stl_allocator_static& other )
{
    return (void*)_memory == (void*)other._memory;
}

//conparision not equal operator
template<typename T, size_t32 S>
bool stl_allocator_static<T,S>::operator!=( const stl_allocator_static& a )
{
    return !operator==(a);
}

} //lib namespace

#endif CRAP_MEMORY_ALLOCATORSTATIC_H
