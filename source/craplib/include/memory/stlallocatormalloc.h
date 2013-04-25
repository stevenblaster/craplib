////////////////////////////////////////////////////////
//	CRAP Library
//!		@file stlallocatormalloc.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Allocator using malloc and free for
//		passing by global overloading of new/delete
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_MEMORY_ALLOCATORMALLOC_H
#define CRAP_MEMORY_ALLOCATORMALLOC_H

#include "control/limits.h"

//lib namespace
namespace crap
{

template<typename T>
class stl_allocator_malloc
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
		typedef stl_allocator_malloc<U> other;
	};

	inline explicit stl_allocator_malloc() {}
	inline ~stl_allocator_malloc() {}
	inline explicit stl_allocator_malloc(stl_allocator_malloc const&) {}

	template<typename U>
	inline explicit stl_allocator_malloc(stl_allocator_malloc<U> const&) {}

	inline pointer address(reference r)
	{
		return &r;
	}
	inline const_pointer address(const_reference r)
	{
		return &r;
	}

	inline pointer allocate(size_type cnt = 1, typename stl_allocator_malloc<T>::const_pointer = 0)
	{
		return reinterpret_cast<pointer>(malloc(cnt * sizeof (T)));
	}

	inline void deallocate(pointer p, size_type s=1)
	{
		free(p);
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

	inline bool operator==(stl_allocator_malloc const&)
	{
		return true;
	}

	inline bool operator!=(stl_allocator_malloc const& a)
	{
		return !operator==(a);
	}
};


}	//namespace crap

#endif	// CRAP_MEMORY_ALLOCATORMALLOC_H
