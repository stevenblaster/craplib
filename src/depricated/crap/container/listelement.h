////////////////////////////////////////////////////////
// CRAP Library
//	listelement.h
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
#ifndef CRAP_CONTAINER_LISTELEMENT_H
#define CRAP_CONTAINER_LISTELEMENT_H

template<typename T>
struct ListElement
{
    T object;
    ListElement* next;
    ListElement* previous;

    explicit ListElement( void ) : next(0), previous(0) {}
    ListElement( const T& o, ListElement* n, ListElement* p) : object(o), next(n), previous(p) {}
    ListElement( const ListElement& other ) : object( other.object ), next(other.next), previous(other.previous){}

    CRAP_INLINE ListElement* operator++( void )
    {
        return next;
    }
    CRAP_INLINE ListElement* operator--( void )
    {
        return previous;
    }
    CRAP_INLINE ListElement& operator=( const ListElement& other )
    {
        ASSERT_DEBUG( this != &other, "Assignment operator on same object" );
        object = other.object;
        next = other.next;
        previous = other.previous;
        return *this;
    }
};

#endif // CRAP_CONTAINER_LISTELEMENT_H
