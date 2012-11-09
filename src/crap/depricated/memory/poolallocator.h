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

#ifndef CRAP_MEMORY_POOLALLOCATOR_H
#define CRAP_MEMORY_POOLALLOCATOR_H

#include "control/limits.h"
#include "control/checkvtable.h"
#include "container/bitmask.h"
#include "threading/scopelock.h"
#include "memory/memorymanager.h"

namespace crap
{
namespace memory
{

template<typename T, u64 S>
class PoolAllocator
{
private:

	template<u64 U>
	struct rest
	{
		static const i32 VAL = ( U % 8 == 0 ) ? 0 : 1;
	};

	crap::container::bit_mask _index;
	u8 _memory[ ( S / 8 + rest<S>::VAL ) + sizeof(T)*S ];
	void* _memStart;
	u64 _size;
	threading::Mutex _mutex;

public :

    //Typedefs
	typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef u64 size_type;
    typedef std::ptrdiff_t difference_type;
    //typedef __PTRDIFF_TYPE__ difference_type;

    //    convert an allocator<T> to allocator<U>
    template<typename U, u64 V>
    struct rebind
    {
        typedef PoolAllocator<U, V> other;
    };

    inline explicit PoolAllocator( void ) : _memStart( _memory + (S / 8 + rest<S>::VAL) ), _size(0)
	{
		_index.init( _memory, ( S / 8 + rest<S>::VAL ) );
		_index.reset();
	}

    inline ~PoolAllocator( void ) {}

    inline explicit PoolAllocator( const PoolAllocator& other ) : _memStart( _memory + (S / 8 + rest<S>::VAL) ), _size(0)
	{
		_index.init( _memory, ( S / 8 + rest<S>::VAL ) );
		_index = other._index;
		if( control::HasVTable<T>::RESULT == false )
		{
			memcpy( _memStart, other._memStart, sizeof(T) * S );
		}
		else
		{
			T* _array = static_cast<T*>(_memStart);
			T* _otherArray = static_cast<T*>(other._memStart);
			for( u64 i=0; i<S; ++i )
			{
				_array[i] = _otherArray[i];
			}
		}
	}

    template<typename U, u64 V>
    inline explicit PoolAllocator( const PoolAllocator<U, V>& ) {}

	PoolAllocator& operator=( const PoolAllocator& other )
	{
		CRAP_ASSERT_STOP( this != &other, "Using Assignment operator on same object" );

		_index.init( _memory, (S / 8 + rest<S>::VAL) );
		_index = other._index;
		_size = other._size;
		if( control::HasVTable<T>::RESULT == false )
		{
			memcpy( _memStart, other._memStart, sizeof(T) * S );
		}
		else
		{
			T* _array = static_cast<T*>(_memStart);
			T* _otherArray = static_cast<T*>(other._memStart);
			for( u64 i=0; i<S; ++i )
			{
				_array[i] = _otherArray[i];
			}
		}
		return *this;
	}

    inline T& operator[]( u64 index )
	{
		CRAP_ASSERT_DEBUG( index < S, "Index operator - index higher then size");
//		return *(static_cast<T*>( _memStart ) + index);

		u64 used_index = 0;
		T* rtn = 0;
		for( u64 i=0; i<S; ++i )
		{
			if( _index.test( i ) )
			{
				if( used_index++ == index )
				{
					rtn = (static_cast<T*>( _memStart ) + i);
					break;
				}
					//return *(static_cast<T*>( _memStart ) + i);
			}
		}
		//CRAP_ASSERT_ERROR( "Index not found" );
		CRAP_ASSERT_DEBUG( rtn != 0, "Index not found");
		return *rtn;
	}

    inline const T& operator[]( u64 index ) const
	{
		CRAP_ASSERT_DEBUG( index < S, "Index operator - index higher then size");
		//		return *(static_cast<T*>( _memStart ) + index);

		u64 used_index = 0;
		T* rtn = 0;
		for( u64 i=0; i<S; ++i )
		{
			if( _index.test( i ) )
			{
				if( used_index++ == index )
				{
					rtn = (static_cast<T*>( _memStart ) + i);
					break;
				}
					//return *(static_cast<T*>( _memStart ) + i);
			}
		}
		//CRAP_ASSERT_ERROR( "Index not found" );
		CRAP_ASSERT_DEBUG( rtn != 0, "Index not found");
		return *rtn;
	}

    inline pointer address( reference r ) { return &r; }

    inline const_pointer address( const_reference r ) { return &r; }

    inline pointer allocate( size_type count = 1, typename PoolAllocator<T,S>::const_pointer = 0 )
	{
		SCOPE_MUTEX( &_mutex );
		i64 position = _index.find_unset();
		CRAP_ASSERT_DEBUG( _size + count <= S, "Allocating would exceed static size");

		while( position != -1 )
		{
			if( _index.find_set( position, count ) != -1 )
				position = _index.find_unset( position + _index.find_set( position, count ) );
			else
				break;
		}

		CRAP_ASSERT_DEBUG( position != -1, "Could not allocate sufficiant block" );
		_index.set( position, count );
		_size += count;
		return static_cast<T*>(_memStart) + position;
	}

    inline void deallocate(pointer ptr, size_type count = 1)
	{
		SCOPE_MUTEX( &_mutex );
		for( u64 i=0; i<S; ++i )
		{
			if( static_cast<T*>(_memStart) + i == ptr )
			{
				_index.reset( i, count );
				_size -= count;
				return;
			}
		}
		CRAP_ASSERT_ERROR( "Pointer not found in MemoryArray" );
	}

    inline u64 size( void ) const { return _size; }

    inline size_type max_size() const
	{
		return crap::control::Limits<size_type>::MAX / sizeof(T);
	}

    inline void construct(pointer p, const T& t)
	{
		new(p) T(t);
	}

    inline void destroy(pointer p)
	{
		p->~T();
	}

	inline crap::threading::Mutex* mutex( void )
	{
		return &_mutex;
	}

    inline bool operator==(PoolAllocator const&)
	{
		return true;
	}

    inline bool operator!=(PoolAllocator const& a)
	{
		return !operator==(a);
	}

    template<typename U, u64 V>
    friend std::ostream& operator<<( std::ostream& out, const PoolAllocator<U,V>& memBlock );
};

template<typename U, u64 V>
std::ostream& operator<<( std::ostream& out, const PoolAllocator<U,V>& memBlock )
{
	for( u64 i=0; i<V; ++i )
		out << memBlock._index[i];
		//out << memBlock._index;
	return out;
}

}
}


#endif // CRAP_MEMORY_POOLALLOCATOR_H
