////////////////////////////////////////////////////////
// CRAP Library
//	staticarraylist.h
//
//	Creator:
//		Steffen Kopany <steffen@kopany.at>
//
//	Author(s):
// 	Steffen Kopany <steffen@kopany.at>
//
//	Copyright (c) 2012 Steffen Kopany
//
//	Description:
//		The description can take
//		more then one line
//
//	Status (scratch, developed, final):
//		scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_STATICARRAYLIST_H
#define CRAP_CONTAINER_STATICARRAYLIST_H

#include "memory/staticallocator.h"

namespace crap
{
namespace container
{

template<typename T, u64 S>
class StaticArrayList
{
private:
    memory::StaticAllocator<T, S> _memory;
    u64 _size;

public:

	class  Iterator
	{
		private:
			StaticArrayList<T,S>* _list;
			u64 _current;

		public:
			Iterator( void );
			Iterator( StaticArrayList<T,S>* list, u64 pos = 0 );
			void operator++( void );
			void operator--( void );
			T* operator->( void );
			T& operator*( void );
			const T& operator*( void ) const;
	};

	Iterator begin() { return Iterator(this, 0);}
	Iterator end() {return Iterator(this, _size-1);} //TODO: continue

    StaticArrayList( void );
    StaticArrayList( const StaticArrayList<T, S>& other );

    StaticArrayList<T, S>& operator=( const StaticArrayList<T, S>& other );

    T& operator[]( const u64 index );
    const T& operator[]( const u64 index ) const;

    u64 size( void ) const;
    bool isEmpty( void ) const;
    bool isFull( void ) const;

    void insert( const T& object );
    void remove( T* object );
    void remove( u64 index );

    i64 search( const T& object );
};

template<typename T, u64 S>
StaticArrayList<T,S>::StaticArrayList( void )
{
    _memory.clear();
    _size = 0;
}

template<typename T, u64 S>
StaticArrayList<T,S>::StaticArrayList( const StaticArrayList<T, S>& other )
{
    _memory = other._memory;
    _size = other._size;
}

template<typename T, u64 S>
StaticArrayList<T, S>& StaticArrayList<T, S>::operator=( const StaticArrayList<T, S>& other )
{
    //check for same address happens in allocator
    SCOPE_MUTEX( _memory.mutex() );

    _memory = other._memory;
    return *this;
}

template<typename T, u64 S>
T& StaticArrayList<T, S>::operator[]( const u64 index )
{
	CRAP_ASSERT_DEBUG( index < S, "Index higher then size" );

    SCOPE_MUTEX( _memory.mutex() );

    u64 used_index = 0;
    for( u64 i=0; i<S; ++i )
    {
        if( _memory.isUsed( i ) )
        {
            if( used_index++ == index )
                return _memory[ i ];
        }
    }
    CRAP_ASSERT_ERROR( "Index not found" );
    return _memory[0];
}

template<typename T, u64 S>
const T& StaticArrayList<T, S>::operator[]( const u64 index ) const
{
	CRAP_ASSERT_DEBUG( index < S, "Index higher then size" );

    u64 used_index = 0;
    for( u64 i=0; i<S; ++i )
    {
        if( _memory.isUsed( i ) )
        {
            if( used_index++ == index )
                return _memory[ i ];
        }
    }
    CRAP_ASSERT_ERROR( "Index not found" );
    return _memory[0];
}

template<typename T, u64 S>
u64 StaticArrayList<T, S>::size( void ) const
{
   return _size;
}

template<typename T, u64 S>
bool StaticArrayList<T, S>::isEmpty( void ) const
{
    return _size == 0;
}

template<typename T, u64 S>
bool StaticArrayList<T, S>::isFull( void ) const
{
    return _size == S;
}

template<typename T, u64 S>
void StaticArrayList<T, S>::insert( const T& object )
{
    *static_cast<T*>( _memory.allocate() ) = object;
    ++_size;
}

template<typename T, u64 S>
void StaticArrayList<T, S>::remove( T* object )
{
	_memory.deallocate( object );
	--_size;
}

template<typename T, u64 S>
void StaticArrayList<T, S>::remove( u64 index )
{
	_memory.deallocate( &(operator[]( index )) );
	--_size;
}

template<typename T, u64 S>
i64 StaticArrayList<T, S>::search( const T& object )
{
//    SCOPE_MUTEX( _memory.mutex() );

    for( u64 i=0; i<_size; ++i )
    {
		if( operator[](i) == object )
        	return (i64) i;
    }
    return -1;
}

template<typename T, u64 S>
StaticArrayList<T, S>::Iterator::Iterator( void ) : _list(0), _current(0)
{
}

template<typename T, u64 S>
StaticArrayList<T, S>::Iterator::Iterator( StaticArrayList<T,S>* list, u64 pos ) : _list(list), _current(pos)
{
}

template<typename T, u64 S>
void StaticArrayList<T, S>::Iterator::operator++( void )
{
	++_current;
}

template<typename T, u64 S>
void StaticArrayList<T, S>::Iterator::operator--( void )
{
	--_current;
}

template<typename T, u64 S>
T* StaticArrayList<T, S>::Iterator::operator->( void )
{
	return *_list[_current];
}

template<typename T, u64 S>
T& StaticArrayList<T, S>::Iterator::operator*( void )
{
	return _list[_current];
}

template<typename T, u64 S>
const T& StaticArrayList<T, S>::Iterator::operator*( void ) const
{
	return _list[_current];
}

}	// namespace container
}	// namespace crap

#endif // CRAP_CONTAINER_STATICARRAYLIST_H
