////////////////////////////////////////////////////////
// CRAP Library
//	staticarraymap.h
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

#ifndef CRAP_CONTAINER_STATICARRAYMAP_H
#define CRAP_CONTAINER_STATICARRAYMAP_H

#include "container/staticarraylist.h"

namespace crap
{
namespace container
{

template<typename T, typename U>
struct Pair
{
    T key;
    U value;
};

template<typename T, typename U, u64 S>
class StaticArrayMap
{
public:

    typedef Pair<T, U> MapElement;

    StaticArrayMap();
    ~StaticArrayMap();
    StaticArrayMap( const StaticArrayMap& other );
    StaticArrayMap& operator=( const StaticArrayMap& other );

    MapElement& operator[]( u64 index );
    const MapElement& operator[]( u64 index ) const;

    bool containsKey( const T& findkey );
    bool containsValue( const U& findvalue ) const;

    U* findValue( const T& findkey );
    const T* findKey( const U& findvalue ) const;

    void add( const T& thekey, const U& thevalue );

    void remove( const T& deletekey );
    void remove( const U& deletevalue );

    bool isFull();
    bool isEmpty();

    u64 size();

private:
    StaticArrayList<MapElement, S> _list;
};

template<typename T, typename U, u64 S>
StaticArrayMap<T, U, S>::StaticArrayMap()
{
}

template<typename T, typename U, u64 S>
StaticArrayMap<T, U, S>::~StaticArrayMap()
{
}

template<typename T, typename U, u64 S>
StaticArrayMap<T, U, S>::StaticArrayMap( const StaticArrayMap<T, U, S>& other )
{
    _list = other._list;
}

template<typename T, typename U, u64 S>
StaticArrayMap<T, U, S>& StaticArrayMap<T, U, S>::operator=( const StaticArrayMap<T, U, S>& other )
{
    _list = other._list;
    return *this;
}

template<typename T, typename U, u64 S>
Pair<T, U>& StaticArrayMap<T, U, S>::operator[]( u64 index )
{
    return _list[index];
}

template<typename T, typename U, u64 S>
const Pair<T, U>& StaticArrayMap<T, U, S>::operator[]( u64 index ) const
{
    return _list[index];
}


template<typename T, typename U, u64 S>
bool StaticArrayMap<T, U, S>::containsKey( const T& findkey )
{
    return findValue( findkey ) != 0;
}

template<typename T, typename U, u64 S>
bool StaticArrayMap<T, U, S>::containsValue( const U& findvalue ) const
{
    return findKey( findvalue ) != 0;
}

template<typename T, typename U, u64 S>
U* StaticArrayMap<T, U, S>::findValue( const T& findkey )
{
    for( u64 i=0; i<_list.size(); ++i )
    {
        if( _list[i].key == findkey )
            return &_list[i].value;
    }

    return 0;
}

template<typename T, typename U, u64 S>
const T* StaticArrayMap<T, U, S>::findKey( const U& findvalue ) const
{
    for( u64 i=0; i<_list.size(); ++i )
    {
        if( _list[i].value == findvalue )
            return &_list[i].key;
    }

    return 0;
}

template<typename T, typename U, u64 S>
void StaticArrayMap<T, U, S>::add( const T& thekey, const U& thevalue )
{
    for( u64 i=0; i<_list.size(); ++i )
    {
        if( _list[i].key == thekey )
        {
            _list[i].value = thevalue;
            return;
        }
    }

    MapElement insert;
    insert.key = thekey;
    insert.value = thevalue;

    _list.insert( insert );
}

template<typename T, typename U, u64 S>
void StaticArrayMap<T, U, S>::remove( const T& deletekey )
{
    for( u64 i=0; i<_list.size(); ++i )
    {
        if( _list[i].key == deletekey )
        {
            _list.remove( i );
            return;
        }
    }
}

template<typename T, typename U, u64 S>
void StaticArrayMap<T, U, S>::remove( const U& deletevalue )
{
    for( u64 i=0; i<_list.size(); ++i )
    {
        if( _list[i].value == deletevalue )
        {
            _list.remove( i );
            return;
        }
    }
}

template<typename T, typename U, u64 S>
bool StaticArrayMap<T, U, S>::isFull()
{
    return _list.isFull();
}

template<typename T, typename U, u64 S>
bool StaticArrayMap<T, U, S>::isEmpty()
{
    return _list.isEmpty();
}

template<typename T, typename U, u64 S>
u64 StaticArrayMap<T, U, S>::size()
{
    return _list.size();
}

}	// namespace container
}	// namespace crap

#endif // CRAP_CONTAINER_STATICARRAYMAP_H
