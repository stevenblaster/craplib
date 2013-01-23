////////////////////////////////////////////////////////
// CRAP Library
//	staticallocator.h
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

#ifndef CRAP_MEMORY_STATICALLOCATOR_H
#define CRAP_MEMORY_STATICALLOCATOR_H

#include "control/checkvtable.h"
#include "container/bitmask.h"
#include "threading/scopelock.h"
#include "memory/memorymanager.h"

namespace crap
{
namespace memory
{

template<typename T, u64 S>
class StaticAllocator
{
private:
	crap::container::BitMask _index;
	u8 _memory[ (S / 8 + S % 8) + sizeof(T)*S ];
	void* _memStart;
	mutex _mutex;

public:
    StaticAllocator( void );
    ~StaticAllocator( void );
    StaticAllocator( const StaticAllocator& other );

    StaticAllocator& operator=( const StaticAllocator& other );

    T& operator[]( u64 index );
    const T& operator[]( u64 index ) const;

    T* allocate( void );
    void deallocate( void* pointer );
    bool isUsed( u64 index ) const;

	mutex* mutex( void );
	void* pointer( void );
    void clear( void );

	template<typename U, u64 V>
    friend std::ostream& operator<<( std::ostream& out, const StaticAllocator<U,V>& memBlock );

    void* operator new (std::size_t size) throw (std::bad_alloc);
	void* operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
	void* operator new[] (std::size_t size) throw (std::bad_alloc);
	void* operator new[] (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
	void operator delete (void* pointer) throw ();
	void operator delete (void* pointer, const std::nothrow_t& nothrow_constant) throw();
	void operator delete[] (void* pointer) throw ();
	void operator delete[] (void* pointer, const std::nothrow_t& nothrow_constant) throw();
};

template<typename T, u64 S>
StaticAllocator<T,S>::StaticAllocator( void ) : _memStart( _memory + (S / 8 + S % 8) )
{
	_index.init( _memory, (S / 8 + S % 8) );
}

template<typename T, u64 S>
StaticAllocator<T,S>::~StaticAllocator( void )
{

}

template<typename T, u64 S>
StaticAllocator<T,S>::StaticAllocator( const StaticAllocator<T,S>& other ) : _memStart( _memory + (S / 8 + S % 8) )
{
	_index.init( _memory, (S / 8 + S % 8) );
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

template<typename T, u64 S>
StaticAllocator<T,S>& StaticAllocator<T,S>::operator=( const StaticAllocator<T,S>& other )
{
	CRAP_ASSERT_STOP( this != &other, "Using Assignment operator on same object" );

	_index.init( _memory, (S / 8 + S % 8) );
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

    return *this;
}

template<typename T, u64 S>
T& StaticAllocator<T,S>::operator[]( u64 index )
{
	return *(static_cast<T*>( _memStart ) + index);
}

template<typename T, u64 S>
const T& StaticAllocator<T,S>::operator[]( u64 index ) const
{
	return *(static_cast<T*>( _memStart ) + index);
}

template<typename T, u64 S>
T* StaticAllocator<T,S>::allocate( void )
{
	SCOPE_MUTEX( &_mutex );
	i64 position = _index.firstUnset();
	CRAP_ASSERT_DEBUG( position != -1, "Memoryarray is full" );
	_index.set( position );
	return static_cast<T*>(_memStart) + position;
}

template<typename T, u64 S>
void StaticAllocator<T,S>::deallocate( void* pointer )
{
	SCOPE_MUTEX( &_mutex );
	for( u64 i=0; i<S; ++i )
	{
		if( static_cast<T*>(_memStart) + i == pointer )
		{
			_index.reset( i );
			return;
		}
	}
	CRAP_ASSERT_ERROR( "Pointer not found in MemoryArray" );
}

template<typename T, u64 S>
bool StaticAllocator<T,S>::isUsed( u64 index ) const
{
	return _index.test( index );
}

template<typename T, u64 S>
mutex* StaticAllocator<T,S>::mutex( void )
{
	return &_mutex;
}

template<typename T, u64 S>
void* StaticAllocator<T,S>::pointer( void )
{
	return _memStart;
}

template<typename T, u64 S>
void StaticAllocator<T,S>::clear( void )
{
	_index.reset();
	memset( _memStart, 0, sizeof(T)*S );
}

template<typename U, u64 V>
std::ostream& operator<<( std::ostream& out, const StaticAllocator<U,V>& memBlock )
{
	out << memBlock._index;
	return out;
}

/*
	Following: operator new/delete
*/
template<typename T, u64 S>
inline void* StaticAllocator<T,S>::operator new (std::size_t size) throw (std::bad_alloc)
{
	return MemoryManager::instance().allocate( size );
}

template<typename T, u64 S>
inline void* StaticAllocator<T,S>::operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw()
{
	return MemoryManager::instance().allocate( size );
}

template<typename T, u64 S>
inline void* StaticAllocator<T,S>::operator new[] (std::size_t size) throw (std::bad_alloc)
{
	return MemoryManager::instance().allocate( size );
}

template<typename T, u64 S>
inline void* StaticAllocator<T,S>::operator new[] (std::size_t size, const std::nothrow_t& nothrow_constant) throw()
{
	return MemoryManager::instance().allocate( size );
}

template<typename T, u64 S>
inline void StaticAllocator<T,S>::operator delete (void* pointer) throw ()
{
	MemoryManager::instance().deallocate( pointer );
}

template<typename T, u64 S>
inline void StaticAllocator<T,S>::operator delete (void* pointer, const std::nothrow_t& nothrow_constant) throw()
{
	MemoryManager::instance().deallocate( pointer );
}

template<typename T, u64 S>
inline void StaticAllocator<T,S>::operator delete[] (void* pointer) throw ()
{
	MemoryManager::instance().deallocate( pointer );
}

template<typename T, u64 S>
inline void StaticAllocator<T,S>::operator delete[] (void* pointer, const std::nothrow_t& nothrow_constant) throw()
{
	MemoryManager::instance().deallocate( pointer );
}

}	// namespace memory
}	// namespace crap


#endif // CRAP_MEMORY_STATICALLOCATOR_H
