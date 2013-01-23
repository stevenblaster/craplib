////////////////////////////////////////////////////////
// CRAP Library
//	allocator.h
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

#ifndef CRAP_MEMORY_ALLOCATOR_H
#define CRAP_MEMORY_ALLOCATOR_H

namespace crap
{
namespace memory
{

template<class T>
class Allocator
{
	public:

	template<typename U>
    struct rebind
    {
        typedef Allocator<U> other;
    };

	inline explicit Allocator( void ) {}
	virtual ~Allocator( void ) {}
//	inline explicit Allocator( const Allocator& other ) {}

	virtual T* address( T& r ) = 0;
    virtual const T* address( const T& r ) = 0;

	virtual T* allocate( u64 number = 1 ) = 0;
	virtual void deallocate( T* pointer, u64 number = 1 ) = 0;

	virtual void construct( T* pointer , const T& value ) = 0;
	virtual void destruct( T* pointer ) = 0;
};

template<class T>
T* Allocator<T>::allocate( u64 number /*= 1*/ )
{
	return  new T[number] ;
}

template<class T>
void Allocator<T>::deallocate( T* pointer, u64 number /*= 1*/ )
{
	delete[] pointer;
}

template<class T>
void Allocator<T>::construct( T* pointer, const T& value )
{
	new((void*)pointer)T(value);
}

template<class T>
void Allocator<T>::destruct( T* pointer )
{
	pointer->~T();
}

}	// namespace memory
}	// namespace crap

#endif // CRAP_MEMORY_ALLOCATOR_H
