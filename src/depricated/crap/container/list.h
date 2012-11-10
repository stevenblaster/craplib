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
#ifndef CRAP_CONTAINER_LIST_H
#define CRAP_CONTAINER_LIST_H

#include "container/deque.h"

namespace crap
{
namespace container
{

template<typename T, u64 S = 0, class D = crap::container::Deque<T,S> >
class List
{
private:
    D _deque;

public:

	Iterator<T> begin() { return _deque.begin(); }
	Iterator<T> end() { return _deque.end(); }

    List( void );
    List( const List<T,S,D>& other );

    List<T,S,D>& operator=( const List<T,S,D>& other );

    T& operator[]( const u64 index );
    const T& operator[]( const u64 index ) const;

    u64 size( void ) const;
    u64 maxSize( void ) const;

    bool isEmpty( void ) const;
    bool isFull( void ) const;

    void insert( const T& object , Iterator<T> position = Iterator<T>() );
    void erase( const Iterator<T>& position );
    void remove( const T& object );

    void clear( void );

    Iterator<T> search( const T& object );

    template<typename U>
    friend std::ostream& operator<<( std::ostream& out, const List<U>& other );
};

template<typename T, u64 S, class D>
List<T,S,D>::List( void )
{
}

template<typename T, u64 S, class D>
List<T,S,D>::List( const List<T,S,D>& other )
{
    _deque = other._deque;
}

template<typename T, u64 S, class D>
List<T,S,D>& List<T,S,D>::operator=( const List<T,S,D>& other )
{
    _deque = other._deque;
    return *this;
}

template<typename T, u64 S, class D>
T& List<T,S,D>::operator[]( const u64 index )
{
	return _deque[index];
}

template<typename T, u64 S, class D>
const T& List<T,S,D>::operator[]( const u64 index ) const
{
	return _deque[index];
}

template<typename T, u64 S, class D>
u64 List<T,S,D>::size( void ) const
{
   return _deque.size();
}

template<typename T, u64 S, class D>
u64 List<T,S,D>::maxSize( void ) const
{
	return _deque.maxSize();
}

template<typename T, u64 S, class D>
bool List<T,S,D>::isEmpty( void ) const
{
    return _deque.isEmpty();
}

template<typename T, u64 S, class D>
bool List<T,S,D>::isFull( void ) const
{
	return _deque.isFull();
}

template<typename T, u64 S, class D>
void List<T,S,D>::insert( const T& object , Iterator<T> position )
{
	_deque.insert( object, position );
}

template<typename T, u64 S, class D>
void List<T,S,D>::erase( const Iterator<T>& position )
{
	_deque.erase( position );
}

template<typename T, u64 S, class D>
void List<T,S,D>::remove( const T& object )
{
	Iterator<T> it = _deque.search( object );
	if( it.ptr() != 0 )
		erase(it);
}

template<typename T, u64 S, class D>
Iterator<T> List<T,S,D>::search( const T& object )
{
    return _deque.search( object );
}

template<typename T, u64 S, class D>
void List<T,S,D>::clear( void )
{
	_deque.clear();
}

template<typename U>
std::ostream& operator<<( std::ostream& out, const List<U>& other )
{
	out << other._deque;
	return out;
}

template<typename T, u64 S>
class StaticList : public List< T, S, crap::container::StaticDeque<T, S> >
{

};



}	// namespace container
}	// namespace crap

#endif // CRAP_CONTAINER_LIST_H
