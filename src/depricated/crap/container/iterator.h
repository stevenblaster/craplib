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
#ifndef CRAP_CONTAINER_ITERATOR_H
#define CRAP_CONTAINER_ITERATOR_H

#include "container/listelement.h"

template<typename T>
class  Iterator
{
private:
    ListElement<T>* _list;

public:
    Iterator( void ) : _list(0) {}
    Iterator( ListElement<T>* element ) : _list(element) {}
    Iterator( const Iterator& other ) : _list( other._list ) {}
    Iterator& operator=( const Iterator& other )
    {
    	ASSERT_DEBUG( this != &other, "Assingment operator on same object" );
    	_list = other._list;
    	return *this;
	}
    void operator++( void )
    {
        _list = _list->next;
    }
    void operator--( void )
    {
        _list = _list->previous;
    }
    bool operator==( const Iterator& other ) const
    {
        return _list == other._list;
    }
    bool operator!=( const Iterator& other ) const
    {
        return _list != other._list;
    }
    T* operator->( void )
    {
        return &(_list->object);
    }
    T& operator*( void )
    {
        return _list->object;
    }
    const T& operator*( void ) const
    {
        return _list->object;
    }
    ListElement<T>* ptr( void )
    {
    	return _list;
    }
};

#endif // CRAP_CONTAINER_ITERATOR_H
