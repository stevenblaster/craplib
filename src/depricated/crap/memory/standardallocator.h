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

#ifndef CRAP_MEMORY_STANDARDALLOCATOR_H
#define CRAP_MEMORY_STANDARDALLOCATOR_H

#include "control/limits.h"
#include "threading/scopelock.h"
#include "memory/memorymanager.h"

namespace crap
{
namespace memory
{

template<typename T>
class StandardAllocator
{
public :
    //    typedefs
	typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public :
    //    convert an allocator<T> to allocator<U>
    template<typename U>
    struct rebind
    {
        typedef StandardAllocator<U> other;
    };

public :
    inline explicit StandardAllocator() {}
    inline ~StandardAllocator() {}
    inline explicit StandardAllocator(StandardAllocator const&) {}

    template<typename U>
    inline explicit StandardAllocator(StandardAllocator<U> const&) {}

    //    address
    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) { return &r; }

    //    memory allocation
    inline pointer allocate(size_type cnt=1, typename std::allocator<void>::const_pointer = 0)
    {
      return reinterpret_cast<pointer>(crap::memory::MemoryManager::instance().allocate(cnt * sizeof(T)));
    }

    inline void deallocate(pointer p, size_type size=1)
    {
    	crap::memory::MemoryManager::instance().deallocate(p);
    }

    //    size
    inline size_type max_size() const
    {
        return crap::control::Limits<size_type>::MAX / sizeof(T);
 	}

    //    construction/destruction
    inline void construct(pointer p, const T& t) { new(p) T(t); }
    inline void destroy(pointer p) { p->~T(); }

    inline bool operator==(StandardAllocator const&) { return true; }
    inline bool operator!=(StandardAllocator const& a) { return !operator==(a); }
};    //    end of class Allocator

}
}


#endif // CRAP_MEMORY_STANDARDALLOCATOR_H
