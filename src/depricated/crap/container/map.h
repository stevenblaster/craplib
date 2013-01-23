////////////////////////////////////////////////////////
// CRAP Library
//	xxx.h
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

#ifndef CRAP_CONTAINER_MAP_H
#define CRAP_CONTAINER_MAP_H

#include "container/list.h"

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

template< typename T, typename U, u64 S=0, class L = crap::container::List< crap::container::Pair<T,U>,S > >
class Map
{
public:

    typedef Pair<T, U> MapElement;

    Map();
    ~Map();
    Map( const Map& other );
    Map& operator=( const Map& other );

    MapElement& operator[]( u64 index );
    const MapElement& operator[]( u64 index ) const;

	Iterator<MapElement> begin( void ) { return _list.begin(); }
	Iterator<MapElement> end( void ) { return _list.end(); }

    bool containsKey( const T& findkey );
    bool containsValue( const U& findvalue );

    U* findValue( const T& findkey );
    T* findKey( const U& findvalue );

    void add( const T& thekey, const U& thevalue );

    void remove( const T& deletekey );
    void remove( const U& deletevalue );

    bool isFull();
    bool isEmpty();

    u64 size();

    template< typename W, typename X, u64 Y, class Z >
	friend std::ostream& operator<<( std::ostream& out, const Map<W,X,Y,Z>& other );


private:
    L _list;
};

template<typename T, typename U, u64 S, class L>
Map<T,U,S,L>::Map()
{
}

template<typename T, typename U, u64 S, class L>
Map<T,U,S,L>::~Map()
{
}

template<typename T, typename U, u64 S, class L>
Map<T,U,S,L>::Map( const Map<T,U,S,L>& other )
{
    _list = other._list;
}

template<typename T, typename U, u64 S, class L>
Map<T,U,S,L>& Map<T,U,S,L>::operator=( const Map<T,U,S,L>& other )
{
    _list = other._list;
    return *this;
}

template<typename T, typename U, u64 S, class L>
Pair<T, U>& Map<T,U,S,L>::operator[]( u64 index )
{
    return _list[index];
}

template<typename T, typename U, u64 S, class L>
const Pair<T, U>& Map<T,U,S,L>::operator[]( u64 index ) const
{
    return _list[index];
}


template<typename T, typename U, u64 S, class L>
bool Map<T,U,S,L>::containsKey( const T& findkey )
{
    return findValue( findkey ) != 0;
}

template<typename T, typename U, u64 S, class L>
bool Map<T,U,S,L>::containsValue( const U& findvalue )
{
    return findKey( findvalue ) != 0;
}

template<typename T, typename U, u64 S, class L>
U* Map<T,U,S,L>::findValue( const T& findkey )
{
	for( Iterator<MapElement> it = _list.begin(); it != _list.end(); ++it )
	{
//		std::cout << "key found:" << it->key << " key searched:" << findkey << std::endl;
		if( it->key == findkey )
			return &it->value;
	}
//	std::cout << "end" << std::endl;

    return 0;
}

template<typename T, typename U, u64 S, class L>
T* Map<T,U,S,L>::findKey( const U& findvalue )
{
	for( Iterator<MapElement> it = _list.begin(); it != _list.end(); ++it )
	{
		if( it->value == findvalue )
			return &it->key;
	}
//    for( u64 i=0; i<_list.size(); ++i )
//    {
//        if( _list[i].value == findvalue )
//            return &_list[i].key;
//    }

    return 0;
}

template<typename T, typename U, u64 S, class L>
void Map<T,U,S,L>::add( const T& thekey, const U& thevalue )
{
	//update?
	for( Iterator<MapElement> it = _list.begin(); it != _list.end(); ++it )
	{
		if( it->key == thekey )
		{
			it->value = thevalue;
			return;
		}
	}
    MapElement insert;
    insert.key = thekey;
    insert.value = thevalue;

    _list.insert( insert );
}

template<typename T, typename U, u64 S, class L>
void Map<T,U,S,L>::remove( const T& deletekey )
{
	for( Iterator<MapElement> it = _list.begin(); it != _list.end(); ++it )
	{
		if( it->key == deletekey )
		{
			_list.erase(it);
			return;
		}
	}
//    for( u64 i=0; i<_list.size(); ++i )
//    {
//        if( _list[i].key == deletekey )
//        {
//            _list.remove( i );
//            return;
//        }
//    }
}

template<typename T, typename U, u64 S, class L>
void Map<T,U,S,L>::remove( const U& deletevalue )
{
	for( Iterator<MapElement> it = _list.begin(); it != _list.end(); ++it )
	{
		if( it->value == deletevalue )
		{
			_list.erase(it);
			return;
		}
	}
//    for( u64 i=0; i<_list.size(); ++i )
//    {
//        if( _list[i].value == deletevalue )
//        {
//            _list.remove( i );
//            return;
//        }
//    }
}

template<typename T, typename U, u64 S, class L>
bool Map<T,U,S,L>::isFull()
{
    return _list.isFull();
}

template<typename T, typename U, u64 S, class L>
bool Map<T,U,S,L>::isEmpty()
{
    return _list.isEmpty();
}

template<typename T, typename U, u64 S, class L>
u64 Map<T,U,S,L>::size()
{
    return _list.size();
}

template< typename W, typename X, u64 Y, class Z >
std::ostream& operator<<( std::ostream& out, const Map<W,X,Y,Z>& other )
{
//	for(Iterator< Pair<W,X> > it = other.begin(); it != other.end(); ++it)
//	{
//		out << "key:" << it->key << " value:" << it->value << std::endl;
//	}
	out << other._list;
	return out;
}

template<typename T, typename U, u64 S>
class StaticMap : public Map< T, U, S, crap::container::StaticList< crap::container::Pair<T,U>, S> >
{
};

template< typename W, typename X, u64 Y >
std::ostream& operator<<( std::ostream& out, StaticMap<W,X,Y>& other )
{
	for(Iterator< Pair<W,X> > it = other.begin(); it != other.end(); ++it)
	{
		out << "key:" << it->key << " value:" << it->value << std::endl;
	}
	return out;
}

}	// namespace container
}	// namespace crap

#endif // CRAP_CONTAINER_MAP_H
