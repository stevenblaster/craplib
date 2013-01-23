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

#ifndef CRAP_MEMORY_DYNAMICALLOCATOR_H
#define CRAP_MEMORY_DYNAMICALLOCATOR_H

#include "control/limits.h"
#include "control/checkvtable.h"
#include "threading/scopelock.h"
#include "memory/memorymanager.h"


namespace crap
{
namespace memory
{

template<typename T>
class DynamicAllocator
{
private:

	struct alloc_element
	{
		T* object;
		alloc_element* next;
		alloc_element* previous;

		alloc_element( void ) : object(0), next(0), previous(0) {}
		alloc_element( T* o, alloc_element* n, alloc_element* p) : object(o), next(n), previous(p) {}
		alloc_element( const alloc_element& other ) : object( new T(other.object) ), next(other.next), previous(other.previous) {}
		alloc_element* operator++( void ) { return next; }
		alloc_element& operator=( const alloc_element& other )
		{
			CRAP_ASSERT_DEBUG( this != &other, "Assignment operator on same object" );
			object = reinterpret_cast<T*>( crap::memory::MemoryManager::instance().allocate( sizeof(T) ) );
			*object = *other.object;
			next = other.next;
			previous = other.previous;
			return *this;
		}
	};

	typedef alloc_element Allocations;

	Allocations* _start;
	Allocations* _last;
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
    template<typename U>
    struct rebind
    {
        typedef DynamicAllocator<U> other;
    };

    inline explicit DynamicAllocator( void ) : _start(0), _last(0), _size(0)
	{
	}

    inline ~DynamicAllocator( void )
    {
    	Allocations* element = _start;
    	while( element != 0 )
    	{
    		Allocations* nxt = element->next;
    		crap::memory::MemoryManager::instance().deallocate(element->object);
			crap::memory::MemoryManager::instance().deallocate(element);
			element = nxt;
    	}
    }

    inline explicit DynamicAllocator( const DynamicAllocator& other ) : _start(0), _last(0), _size(0)
	{
		//CHECK!!!
		Allocations* element = other._start;
    	while( element != 0 )
    	{
			pointer* new_object = allocate();
			*new_object = *element->object;
			element = element->next;
    	}
	}

    template<typename U>
    inline explicit DynamicAllocator( const DynamicAllocator<U>& ) {}

	DynamicAllocator& operator=( const DynamicAllocator& other )
	{
		CRAP_ASSERT_STOP( this != &other, "Using Assignment operator on same object" );

		//TODO!!!
		Allocations* element = _start;
    	while( element != 0 )
    	{
    		Allocations* nxt = element->next;
    		crap::memory::MemoryManager::instance().deallocate(element->object);
			crap::memory::MemoryManager::instance().deallocate(element);
			element = nxt;
    	}

		_start = 0;
		_last = 0;
		_size = 0;

		element = other._start;
    	while( element != 0 )
    	{
			pointer new_object = allocate();
			*new_object = *element->object;
			element = element->next;
    	}

		return *this;
	}

    inline T& operator[]( u64 index )
	{
		CRAP_ASSERT_DEBUG( index < _size, "Index operator - index higher then size");

		u64 counter = 0;
		T* temp_pointer = 0;
		for( Allocations* element = _start; element != 0; ++element )
		{
			if( counter == index )
			{
				temp_pointer = element->object;
				break;
			}

			++counter;
		}
		CRAP_ASSERT_DEBUG( temp_pointer != 0, "Index not found.");
		return *temp_pointer;
	}

    inline const T& operator[]( u64 index ) const
	{
		CRAP_ASSERT_DEBUG( index < _size, "Index operator - index higher then size");

		u64 counter = 0;
		pointer temp_pointer = 0;
		for( Allocations* element = _start; element != 0; ++element )
		{
			if( counter == index )
			{
				temp_pointer = element->object;
				break;
			}

			++counter;
		}
		CRAP_ASSERT_DEBUG( temp_pointer != 0, "Index not found.");
		return *temp_pointer;
	}

    inline pointer address( reference r ) { return &r; }

    inline const_pointer address( const_reference r ) { return &r; }

    inline pointer allocate( size_type count = 1, typename DynamicAllocator<T>::const_pointer = 0 )
	{
		SCOPE_MUTEX( &_mutex );
		Allocations* temp_allocation = reinterpret_cast<Allocations*>( crap::memory::MemoryManager::instance().allocate( sizeof(Allocations) ) );
		temp_allocation->object = reinterpret_cast<pointer>(crap::memory::MemoryManager::instance().allocate(count * sizeof(T)));
//		std::cout << "object is " << temp_allocation->object << std::endl;
		temp_allocation->next = 0;
		temp_allocation->previous = 0;

		if( _size == 0 )
		{
			_start = temp_allocation;
			_last = temp_allocation;
		}
		else
		{
			_last->next = temp_allocation;
			temp_allocation->previous = _last;
			_last = temp_allocation;
		}
		_size += count;
		return temp_allocation->object;
	}

    inline void deallocate(pointer ptr, size_type count = 1)
	{
		SCOPE_MUTEX( &_mutex );

		Allocations* element = _start;
		for( u64 i=0; i<_size; ++i )
		{
//		for( Allocations* element = _start; element != 0; ++element )
//		{
//			std::cout << element << "->" << element->object << " vs " << ptr << std::endl;
			if( element->object == ptr )
			{
				//COUNTINUE
				if( element->previous != 0 ) //its not start
					element->previous->next = element->next;
				else
				{
					_start = element->next;
				}


				if( element->next != 0)	//its not last
					element->next->previous = element->previous;

				if( _size == count )
				{
					_start = 0;
					_last = 0;
				}

				crap::memory::MemoryManager::instance().deallocate(ptr);
				crap::memory::MemoryManager::instance().deallocate(element);
				_size -= count;
				return;
			}
			element = element->next;
		}

		CRAP_ASSERT_ERROR( "Pointer not found in MemoryList" );
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

    inline bool operator==(DynamicAllocator const&)
	{
		return true;
	}

    inline bool operator!=(DynamicAllocator const& a)
	{
		return !operator==(a);
	}

    template<typename U>
    friend std::ostream& operator<<( std::ostream& out, const DynamicAllocator<U>& memBlock );
};

template<typename U>
std::ostream& operator<<( std::ostream& out, const DynamicAllocator<U>& memBlock )
{
	out << "size: " << memBlock._size << std::endl;

	out << "start: " << memBlock._start;
	if(memBlock._start != 0)
		out << " points at " << memBlock._start->object << " prev: " << memBlock._start->previous << " next: " << memBlock._start->next;
	out << std::endl;

	out << "last: " << memBlock._last;
	if(memBlock._last != 0)
		out << " points at " << memBlock._last->object << " prev: " << memBlock._last->previous << " next: " << memBlock._last->next;
	out << std::endl;

	out << "Collected pointers:" << std::endl;
	typename DynamicAllocator<U>::Allocations* element = memBlock._start;
	for( u64 i=0; i<memBlock.size(); ++i )
	{
		out << element << " points at " << element->object << " prev: " << element->previous << " next: " << element->next << std::endl;
		element = element->next;
	}
	return out;
}


//template<typename T>
//class DynamicAllocator
//{
//private:
//	container::BitMask _index;
//	u8* _memory;
//	void* _memStart;
//	u64 _size;
//	u64 _usedSize;
//	threading::Mutex _mutex;
//
//public:
//    DynamicAllocator( u64 size = 8 );
//    ~DynamicAllocator( void );
//    DynamicAllocator( const DynamicAllocator& other );
//
//    DynamicAllocator& operator=( const DynamicAllocator& other );
//
//    T& operator[]( u64 index );
//    const T& operator[]( u64 index ) const;
//
//    T* allocate( void );
//    void deallocate( void* pointer );
//    bool isUsed( u64 index ) const;
//
//	threading::Mutex* mutex( void );
//	void* pointer( void );
//    void clear( void );
//    void extend( void );
//    void reduce( void );
//
//    u64 size( void ) const;
//    u64 freeSize( void ) const;
//    u64 usedSize( void ) const;
//
//	template<typename U>
//    friend std::ostream& operator<<( std::ostream& out, const DynamicAllocator<U>& memBlock );
//
//    void* operator new (std::size_t size) throw (std::bad_alloc);
//	void* operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
//	void* operator new[] (std::size_t size) throw (std::bad_alloc);
//	void* operator new[] (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
//	void operator delete (void* pointer) throw ();
//	void operator delete (void* pointer, const std::nothrow_t& nothrow_constant) throw();
//	void operator delete[] (void* pointer) throw ();
//	void operator delete[] (void* pointer, const std::nothrow_t& nothrow_constant) throw();
//};
//
//
//template<typename T>
//DynamicAllocator<T>::DynamicAllocator( u64 size /*=8*/ ) : _memory( static_cast<u8*>( MemoryManager::instance().allocate( size + (size  / 8 + size % 8) ) ) ) ,
//																						_memStart( _memory + (size  / 8 + size % 8) ),
//																						_size( size ),
//																						_usedSize(0)
//{
//	CRAP_ASSERT_DEBUG( size % 8 == 0, "DynamicAllocatoer needs to be a multiple of 8");
//	_index.init( _memory, (size / 8 + size % 8) );
//}
//
//template<typename T>
//DynamicAllocator<T>::~DynamicAllocator( void )
//{
//	MemoryManager::instance().deallocate( _memory );
//}
//
//template<typename T>
//DynamicAllocator<T>::DynamicAllocator( const DynamicAllocator<T>& other ) : _memory( MemoryManager::instance().allocate( other._size + (size  / 8 + size % 8)) ),
//																						_memStart( _memory + (other._size / 8 + other._size % 8) ),
//																						_size( other._size ),
//																						_usedSize( other._usedSize )
//{
//	_index.init( _memory, (other._size / 8 + other._size % 8) );
//	_index = other._index;
//	if( control::HasVTable<T>::RESULT == false )
//    {
//        memcpy( _memStart, other._memStart, sizeof(T) * other._size );
//    }
//    else
//    {
//    	T* _array = static_cast<T*>(_memStart);
//    	T* _otherArray = static_cast<T*>(other._memStart);
//        for( u64 i=0; i<other._size; ++i )
//        {
//            _array[i] = _otherArray[i];
//        }
//    }
//}
//
//template<typename T>
//DynamicAllocator<T>& DynamicAllocator<T>::operator=( const DynamicAllocator<T>& other )
//{
//	CRAP_ASSERT_STOP( this != &other, "Using Assignment operator on same object" );
//
//	_index.init( _memory, (other._size / 8 + other._size % 8) );
//	_index = other._index;
//	_usedSize = other._usedSize;
//	_memStart = _memory + (other._size / 8 + other._size % 8);
//	if( control::HasVTable<T>::RESULT == false )
//    {
//        memcpy( _memStart, other._memStart, sizeof(T) * other._size );
//    }
//    else
//    {
//    	T* _array = static_cast<T*>(_memStart);
//    	T* _otherArray = static_cast<T*>(other._memStart);
//        for( u64 i=0; i<other._size; ++i )
//        {
//            _array[i] = _otherArray[i];
//        }
//    }
//
//    return *this;
//}
//
//template<typename T>
//T& DynamicAllocator<T>::operator[]( u64 index )
//{
//	return *(static_cast<T*>( _memStart ) + index);
//}
//
//template<typename T>
//const T& DynamicAllocator<T>::operator[]( u64 index ) const
//{
//	return *(static_cast<T*>( _memStart ) + index);
//}
//
//template<typename T>
//T* DynamicAllocator<T>::allocate( void )
//{
//	SCOPE_MUTEX( &_mutex );
//	i64 position = _index.firstUnset();
//
//	if( position == -1 )
//	{
//		extend();
//		position = _index.firstUnset();
//	}
//
//	CRAP_ASSERT_DEBUG( position != -1, "Memoryarray is full" );
//	_index.set( position );
//	++_usedSize;
//	return static_cast<T*>(_memStart) + position;
//}
//
//template<typename T>
//void DynamicAllocator<T>::deallocate( void* pointer )
//{
//	SCOPE_MUTEX( & _mutex );
//
//	for( u64 i=0; i<_size; ++i )
//	{
//		if( static_cast<T*>(_memStart) + i == pointer )
//		{
//			_index.reset( i );
//			--_usedSize;
//			if( _usedSize <= _size/2 && _size > 8 )
//				reduce();
//			return;
//		}
//	}
//	CRAP_ASSERT_ERROR( "Pointer not found in MemoryArray" );
//}
//
//template<typename T>
//bool DynamicAllocator<T>::isUsed( u64 index ) const
//{
//	return _index.test( index );
//}
//
//template<typename T>
//threading::Mutex* DynamicAllocator<T>::mutex( void )
//{
//	return &_mutex;
//}
//
//template<typename T>
//void* DynamicAllocator<T>::pointer( void )
//{
//	return _memStart;
//}
//
//template<typename T>
//void DynamicAllocator<T>::clear( void )
//{
//	_index.reset();
//	memset( _memStart, 0, sizeof(T)*_size );
//}
//
//template<typename T>
//void DynamicAllocator<T>::extend( void )
//{
//	u64 newsize = _size*2;
//	u8* ptr = static_cast<u8*>( MemoryManager::instance().allocate( newsize + (newsize  / 8 + newsize % 8) ) );
////	std::cout << newsize + (newsize  / 8 + newsize % 8) << " = " << newsize << " + " << newsize/8 << " + " << newsize % 8 << std::endl;
//	void* start = ptr + ( newsize / 8 + newsize % 8);
//
//	container::BitMask newmask( ptr, ( newsize / 8 + newsize % 8) );
//	newmask = _index;
//
//	if( control::HasVTable<T>::RESULT == false )
//	{
//		memcpy( start, _memStart, sizeof(T) * _size );
//	}
//	else
//	{
//		T* _array = static_cast<T*>(start);
//		T* _otherArray = static_cast<T*>(_memStart);
//		for( u64 i=0; i<_size; ++i )
//		{
//			_array[i] = _otherArray[i];
//		}
//	}
//
//	MemoryManager::instance().deallocate( _memory );
//	_index.init( ptr, ( newsize / 8 + newsize % 8) );
//	_memory = ptr;
//	_memStart = start;
//	_size = newsize;
//}
//
//template<typename T>
//void DynamicAllocator<T>::reduce( void )
//{
//	u64 newsize = _size/2;
//	u8* ptr = static_cast<u8*>( MemoryManager::instance().allocate( newsize ) );
//	void* start = ptr + ( newsize / 8 + newsize % 8);
//
//	container::BitMask newmask( ptr, ( newsize / 8 + newsize % 8) );
//	newmask.reset();
//
//	u64 newindex = 0;
//	T* _array = static_cast<T*>(start);
//	T* _otherArray = static_cast<T*>(_memStart);
//	for(u64 i=0; i<_index.size(); ++i)
//	{
//		if( _index.test(i) )
//		{
//			newmask.set(newindex);
//			_array[newindex++] = _otherArray[i];
//		}
//	}
//
//	MemoryManager::instance().deallocate( _memory );
//	_index.init( ptr, ( newsize / 8 + newsize % 8) );
//	_memory = ptr;
//	_memStart = start;
//	_size = newsize;
//}
//
//template<typename T>
//u64 DynamicAllocator<T>::size( void ) const
//{
//	return _size;
//}
//
//template<typename T>
//u64 DynamicAllocator<T>::freeSize( void ) const
//{
//	return _size - _usedSize;
//}
//
//template<typename T>
//u64 DynamicAllocator<T>::usedSize( void ) const
//{
//	return _usedSize;
//}
//
//template<typename U>
//std::ostream& operator<<( std::ostream& out, const DynamicAllocator<U>& memBlock )
//{
//	out << memBlock._index;
//	return out;
//}
//
///*
//	Following: operator new/delete
//*/
//template<typename T>
//inline void* DynamicAllocator<T>::operator new (std::size_t size) throw (std::bad_alloc)
//{
//	return MemoryManager::instance().allocate( size );
//}
//
//template<typename T>
//inline void* DynamicAllocator<T>::operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw()
//{
//	return MemoryManager::instance().allocate( size );
//}
//
//template<typename T>
//inline void* DynamicAllocator<T>::operator new[] (std::size_t size) throw (std::bad_alloc)
//{
//	return MemoryManager::instance().allocate( size );
//}
//
//template<typename T>
//inline void* DynamicAllocator<T>::operator new[] (std::size_t size, const std::nothrow_t& nothrow_constant) throw()
//{
//	return MemoryManager::instance().allocate( size );
//}
//
//template<typename T>
//inline void DynamicAllocator<T>::operator delete (void* pointer) throw ()
//{
//	MemoryManager::instance().deallocate( pointer );
//}
//
//template<typename T>
//inline void DynamicAllocator<T>::operator delete (void* pointer, const std::nothrow_t& nothrow_constant) throw()
//{
//	MemoryManager::instance().deallocate( pointer );
//}
//
//template<typename T>
//inline void DynamicAllocator<T>::operator delete[] (void* pointer) throw ()
//{
//	MemoryManager::instance().deallocate( pointer );
//}
//
//template<typename T>
//inline void DynamicAllocator<T>::operator delete[] (void* pointer, const std::nothrow_t& nothrow_constant) throw()
//{
//	MemoryManager::instance().deallocate( pointer );
//}

}	// namespace memory
}	// namespace crap

#endif // CRAP_MEMORY_DYNAMICALLOCATOR_H
