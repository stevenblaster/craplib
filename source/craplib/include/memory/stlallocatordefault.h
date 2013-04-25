////////////////////////////////////////////////////////
//	CRAP Library
//!		@file stlallocatordefault.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Default allocator using global operator new
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_MEMORY_ALLOCATORDEFAULT_H
#define CRAP_MEMORY_ALLOCATORDEFAULT_H

#include "control/limits.h"

//lib namespace
namespace crap
{

template<typename T>
class stl_allocator_default
{
public:

	typedef T 					value_type;
	typedef value_type* 		pointer;
	typedef const value_type* 	const_pointer;
	typedef value_type& 		reference;
	typedef const value_type& 	const_reference;
	typedef std::size_t 		size_type;			//TODO
	typedef	std::ptrdiff_t		difference_type;	//TODO

	template<typename U>
	struct rebind
	{
		typedef stl_allocator_default<U> other;
	};

	inline explicit stl_allocator_default() {}
	inline ~stl_allocator_default() {}
	inline explicit stl_allocator_default(stl_allocator_default const&) {}

	template<typename U>
	inline stl_allocator_default(stl_allocator_default<U> const&) {}

	inline pointer address(reference r)
	{
		return &r;
	}
	inline const_pointer address(const_reference r)
	{
		return &r;
	}

	inline pointer allocate(size_type cnt = 1, typename stl_allocator_default<T>::const_pointer = 0)
	{
		return reinterpret_cast<pointer>(::operator new(cnt * sizeof (T)));
	}

	inline void deallocate(pointer p, size_type s=1)
	{
		if(s>1)
			::operator delete[](p);
		else
			::operator delete(p);
	}

	inline size_type max_size() const
	{
		return crap::limits<size_type>::MAX / sizeof(T);
	}

	inline void construct(pointer p, const T& t)
	{
		new(p) T(t);
	}

	inline void destroy(pointer p)
	{
		p->~T();
	}

	inline bool operator==(stl_allocator_default const&)
	{
		return true;
	}

	inline bool operator!=(stl_allocator_default const& a)
	{
		return !operator==(a);
	}
};


}	//namespace crap

#endif // CRAP_MEMORY_ALLOCATORDEFAULT_H
