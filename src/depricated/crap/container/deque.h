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
#ifndef CRAP_CONTAINER_DEQUE_H
#define CRAP_CONTAINER_DEQUE_H

#include "container/listelement.h"
#include "container/iterator.h"

#include "control/copyobject.h"

#include "memory/standardallocator.h"
#include "memory/poolallocator.h"

namespace crap
{
namespace container
{

template<typename T, u64 S = 0, class A = memory::StandardAllocator< ListElement<T> > >
class Deque
{

private:

	A _memory;
    u64 _size;
    crap::threading::Mutex _mutex;

	ListElement<T>* _first;
	ListElement<T>* _last;

public:

	Iterator<T> begin() const { return Iterator<T>(_first); }
	Iterator<T> end() const { return Iterator<T>(); }

    Deque( void );
    Deque( const Deque<T,S,A>& other );

    Deque<T,S,A>& operator=( const Deque<T,S,A>& other );

    T& operator[]( const u64 index );
    const T& operator[]( const u64 index ) const;

    T& front( void );
    const T& front( void ) const;

    T& back( void );
    const T& back( void ) const;

    void push_front( const T& object );
    void push_back( const T& object );

    void pop_front( void );
    void pop_back( void );

    u64 size( void ) const;
    u64 maxSize( void ) const;

    bool isEmpty( void ) const;
    bool isFull( void ) const;

    void insert( const T& object , Iterator<T> position = Iterator<T>() );
    void erase( const Iterator<T>& position );

	void clear( void );

    Iterator<T> search( const T& object );

    template<typename U>
    friend std::ostream& operator<<( std::ostream& out, const Deque<U>& other );
};


template<typename T, u64 S, class A>
Deque<T,S,A>::Deque( void ) : _size(0), _first(0), _last(0)
{

}

template<typename T, u64 S, class A>
Deque<T,S,A>::Deque( const Deque<T,S,A>& other ) : _size(0), _first(0), _last(0)
{
    for( Iterator<T> it = other.begin(); it != other.end(); ++it )
    {
    	push_back( *it );
    }
    _size = other._size;
}

template<typename T, u64 S, class A>
Deque<T,S,A>& Deque<T,S,A>::operator=( const Deque<T,S,A>& other )
{
//	SCOPE_MUTEX( _mutex );

	clear();

	for( Iterator<T> it = other.begin(); it != other.end(); ++it )
    {
    	push_back( *it );
    }
    _size = other._size;
    return *this;
}

template<typename T, u64 S, class A>
T& Deque<T,S,A>::operator[]( const u64 index )
{
	ASSERT_DEBUG( index < _size , "Index higher then size");

	ListElement<T>* value = 0;
	u64 local_index = 0;

	for( Iterator<T> it = begin(); it != end(); ++it )
    {
    	if( local_index++ == index )
    	{
    		value = it.ptr();
    		break;
    	}
    }
    ASSERT_DEBUG( value != 0, "Index not found");
	return value->object;
}

template<typename T, u64 S, class A>
const T& Deque<T,S,A>::operator[]( const u64 index ) const
{
	ASSERT_DEBUG( index < _size , "Index higher then size");

	T* value = 0;
	u64 local_index = 0;

	for( Iterator<T> it = begin(); it != end(); ++it )
    {
    	if( local_index++ == index )
    	{
    		value = it->object;
    		break;
    	}
    }
    ASSERT_DEBUG( value != 0, "Index not found");
	return *value;
}

template<typename T, u64 S, class A>
T& Deque<T,S,A>::front( void )
{
	ASSERT_DEBUG( _size >0 , "List is empty" );
	return _first->object;
}

template<typename T, u64 S, class A>
const T& Deque<T,S,A>::front( void ) const
{
	ASSERT_DEBUG( _size >0 , "List is empty" );
	return _first->object;
}

template<typename T, u64 S, class A>
T& Deque<T,S,A>::back( void )
{
	ASSERT_DEBUG( _size >0 , "List is empty" );
	return _last->object;
}

template<typename T, u64 S, class A>
const T& Deque<T,S,A>::back( void ) const
{
	ASSERT_DEBUG( _size >0 , "List is empty" );
	return _last->object;
}

template<typename T, u64 S, class A>
void Deque<T,S,A>::push_back( const T& object )
{
//	SCOPE_MUTEX( _mutex );
	ASSERT_DEBUG( !isFull(), "No space available" );

	ListElement<T>* new_element = _memory.allocate();
	crap::control::copyObject( &object, &new_element->object );

	if( _size == 0 )
	{
		_first = new_element;
		_last = new_element;

		new_element->next = 0;
		new_element->previous = 0;
	}
	else
	{
		new_element->next = 0;
		new_element->previous = _last;

		_last->next = new_element;
		_last = new_element;
	}

	++_size;
}

template<typename T, u64 S, class A>
void Deque<T,S,A>::push_front( const T& object )
{
//	SCOPE_MUTEX( _mutex );
	ASSERT_DEBUG( !isFull(), "No space available" );

	ListElement<T>* new_element = _memory.allocate();
	crap::control::copyObject( &object, &new_element->object );

	if( _size == 0 )
	{
		_first = new_element;
		_last = new_element;

		new_element->next = 0;
		new_element->previous = 0;
	}
	else
	{
		new_element->next = _first;
		new_element->previous = 0;

		_first->previous = new_element;
		_first = new_element;
	}

	++_size;
}

template<typename T, u64 S, class A>
void Deque<T,S,A>::pop_front( void )
{
//	SCOPE_MUTEX( _mutex );

	if( _size == 0)
		return;

	ListElement<T>* delete_element = _first;
	_first = _first->next;

	_memory.deallocate( delete_element );

	--_size;

	if( _size == 0 )
	{
		_first = 0;
		_last = 0;
	}
}

template<typename T, u64 S, class A>
void Deque<T,S,A>::pop_back( void )
{
//	SCOPE_MUTEX( _mutex );

	if( _size == 0)
		return;

	ListElement<T>* delete_element = _last;
	_last = _last->previous;

	_memory.deallocate( delete_element );

	--_size;

	if( _size == 0 )
	{
		_first = 0;
		_last = 0;
	}
}


template<typename T, u64 S, class A>
u64 Deque<T,S,A>::size( void ) const
{
   return _size;
}

template<typename T, u64 S, class A>
u64 Deque<T,S,A>::maxSize( void ) const
{
	return ( S != 0 ) ? S : crap::control::Limits<u64>::MAX;
}

template<typename T, u64 S, class A>
bool Deque<T,S,A>::isEmpty( void ) const
{
    return _size == 0;
}

template<typename T, u64 S, class A>
bool Deque<T,S,A>::isFull( void ) const
{
    return (S == 0) ? false : _size == S;
}

template<typename T, u64 S, class A>
void Deque<T,S,A>::insert( const T& object , Iterator<T> position )
{
//	SCOPE_MUTEX( _mutex );

	ASSERT_DEBUG( !isFull(), "No space available" );

	if( position.ptr() == 0 )
		return push_back( object );

	Iterator<T> it;
	for( it = begin(); it != end(); ++it )
    {
    	if( it == position )
    		break;
    }

	if( it == end() )
    	return push_back( object );

    ListElement<T>* new_element = _memory.allocate();
	crap::control::copyObject( &object, &new_element->object );

    ListElement<T>* prev = it.ptr()->previous;
    if( prev != 0 )
    	prev->next = new_element;
	else
		_first = new_element;

    new_element->next = it.ptr();
    new_element->previous = prev;

    it.ptr()->previous = new_element;

    ++_size;
}

template<typename T, u64 S, class A>
void Deque<T,S,A>::erase( const Iterator<T>& position )
{
//	SCOPE_MUTEX( _mutex );

	Iterator<T> it;
	for( it = begin(); it != end(); ++it )
    {
//    	std::cout << it.ptr() << std::endl;
    	if( it == position )
    		break;
    }

    ASSERT_DEBUG( it != end(), "Could not erase" );

    ListElement<T>* nxt = it.ptr()->next;
    ListElement<T>* prv = it.ptr()->previous;

    if( nxt != 0 )
    	nxt->previous = prv;
	else if( prv != 0 )
		_last = prv;

    if( prv != 0 )
    	prv->next = nxt;
	else if( nxt != 0 )
		_first = nxt;

	_memory.deallocate( it.ptr() );
	--_size;
}

template<typename T, u64 S, class A>
Iterator<T> Deque<T,S,A>::search( const T& object )
{
//    SCOPE_MUTEX( _mutex );

	for( Iterator<T>  it = begin(); it != end(); ++it )
    {
    	if( *it == object )
    		return it;
	}
    return end();
}

template<typename T, u64 S, class A>
void Deque<T,S,A>::clear( void )
{
	while(_size > 0)
	{
		pop_back();
	}
	_size = 0;
	_first = 0;
	_last = 0;
}

template<typename U>
std::ostream& operator<<( std::ostream& out, const Deque<U>& other )
{
	out << "first:" << other._first << " last:" << other._last << std::endl;
	for( Iterator<U> it = other.begin(); it != other.end(); ++it )
	{
		out << "element" << it.ptr() << " obj:" << it.ptr()->object << " nxt:" << it.ptr()->next << " prv:" << it.ptr()->previous << std::endl;
	}
	return out;
}

//Special allocators
template<typename T, u64 S>
class StaticDeque : public Deque< T, S, crap::memory::PoolAllocator< ListElement<T> , S> >
{

};

template<typename U, u64 V>
std::ostream& operator<<( std::ostream& out, const StaticDeque<U,V>& other )
{
	out << "first:" << other.begin().ptr() << " last:" << other.end().ptr() << std::endl;
	for( Iterator<U> it = other.begin(); it != other.end(); ++it )
	{
		out << "element" << it.ptr() << " obj:" << it.ptr()->object << " nxt:" << it.ptr()->next << " prv:" << it.ptr()->previous << std::endl;
	}
	return out;
}


}
}

#endif // CRAP_CONTAINER_DEQUE_H
