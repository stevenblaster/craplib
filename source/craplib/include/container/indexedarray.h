////////////////////////////////////////////////////////
//	CRAP Library
//!		@file indexedarray.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief indexed "look-up table"-like array
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTAINER_INDEXEDARRAY_H
#define CRAP_CONTAINER_INDEXEDARRAY_H

#include "crap.h"

//lib namespace
namespace crap
{

template<typename T, size_t32 S>
class indexed_array
{
private:
	struct index
	{
		i32			array_index;
		size_t32	index_generation;
		size_t32	next;

		index( void ) : array_index(-1), index_generation(0), next(0) {}
	};

	pointer_t<T> _pointer_handle;

public:

	//typedefs
	typedef T& 								reference;
	typedef const T& 						const_reference;
	typedef size_t32		 				size_type;
	typedef std::ptrdiff_t					difference_type;
	typedef T 								value_type;
	typedef T*								pointer;
	typedef const T*						const_pointer;
	typedef size_type						index_key;

	friend struct _iterator;

	struct _iterator
	{
	private:
		pointer _pointer;

	public:
		_iterator( void ) : _pointer(0) { }

		explicit _iterator( pointer element ) : _pointer(element) { }

		_iterator( const _iterator& other ) : _pointer( other._pointer ) {}

		CRAP_INLINE
		_iterator& operator=( const _iterator& other )
		{
			_pointer = other._pointer;
			return *this;
		}

		CRAP_INLINE
		void operator++( void )
		{
			if( _pointer != 0 )
				++_pointer;
		}

		CRAP_INLINE
		void operator--( void )
		{
			if( _pointer != 0 )
				--_pointer;
		}

		CRAP_INLINE
		bool operator==( const _iterator& other ) const
		{
			return _pointer == other._pointer;
		}

		CRAP_INLINE
		bool operator!=( const _iterator& other ) const
		{
			return _pointer != other._pointer;
		}

		CRAP_INLINE
		pointer operator->( void )
		{
			return _pointer;
		}

		CRAP_INLINE
		T& operator*( void )
		{
			return *(_pointer);
		}

		CRAP_INLINE
		const T& operator*( void ) const
		{
			return *(_pointer);
		}

		CRAP_INLINE
		pointer ptr( void ) const
		{
			return _pointer;
		}
	};	// end intrusive_iterator


	/*
	 * Iterator handling
	 */

	typedef _iterator 				iterator;							//iterator
	typedef const _iterator			const_iterator;						//const iterator

	CRAP_INLINE
	iterator begin(void) { return iterator( _pointer_handle.as_type ); }

	CRAP_INLINE
	iterator end(void) { return iterator( _pointer_handle.as_type + S ); }

	//same as above, just const
	CRAP_INLINE
	const_iterator begin(void) const { return const_iterator( _pointer_handle.as_type ); }

	CRAP_INLINE
	const_iterator end(void) const { return const_iterator( _pointer_handle.as_type + S ); }

	indexed_array( void );
	~indexed_array( void );

	index_key push_back( const T& object );

	void remove( index_key key );

	void clear( void );

	pointer find( index_key key );
	const_pointer find( index_key key ) const;

private:
	indexed_array( const indexed_array& other ) {}
	indexed_array& operator=( const indexed_array& other ) { return *this; }

	size_t32 _array_count;
	size_t32 _freelist;

	index _indices[S];
	size_t32 _data_to_index[S];
	u8 _data[(S+1) * sizeof(T)];
};

template<typename T, size_t32 S>
indexed_array<T,S>::indexed_array( void )
{
	_pointer_handle.as_u8 = _data;
	_freelist = 0;

	for( size_t32 i=0; i<S; ++i )
		_indices[i].next = i+1;

	memset( _data_to_index, 0, S*sizeof(size_t32) );
}

template<typename T, size_t32 S>
indexed_array<T,S>::~indexed_array( void )
{

}

template<typename T, size_t32 S>
typename indexed_array<T,S>::index_key indexed_array<T,S>::push_back( const T& object )
{
	CRAP_ASSERT_DEBUG( _array_count != S, "Indexed array is full");

	const size_t32 indices_index	= _freelist;
	const size_t32 data_index		= _array_count;
	const T*	   data_pointer		= _pointer_handle.as_type + _array_count;

	*data_pointer = object;

	_data_to_index[ data_index ] = indices_index;

	_indices[ indices_index ].array_index = _array_count;
	++_indices[ indices_index ].index_generation;
	_indices[ indices_indexes ].next = ++_freelist;

	++_array_count;
	return indices_index + ( S * _indices[ indices_index ].index_generation );

	return 0;
}

template<typename T, size_t32 S>
void indexed_array<T,S>::remove( index_key key )
{
	const size_t32 generation = key / S;
	const size_t32 indices_index = key % S;
	const size_t32 last_data_index = _array_count - 1;

	CRAP_ASSERT_DEBUG( _indices[ indices_index ].generation == generation, "Index generation not correct" );

	const i32& array_index = &(_indices[ indices_index ].array_index);
	_indices[ indices_index ].array_index = -1;
	_indices[ indices_index ].next = _freelist;
	_freelist = indices_index;

	const size_t32 last_indices_index = _data_to_index[ last_data_index ];
	_data_to_index[ last_data_index ] = 0;
	_data_to_index[ array_index ] = last_indices_index;
	_indices[ last_indices_index ].array_index = array_index;

	T* object = _pointer_handle.as_type + array_index;
	T->~T();
	*(_pointer_handle.as_type + array_index) = *(_pointer_handle.as_type + last_data_index);

	--_array_count;
}

template<typename T, size_t32 S>
void indexed_array<T,S>::clear( void )
{
	for( size_t32 i = 0; i<S; ++i )
	{
		if( _indices[i].array_index != -1 )
		{
			i32 deletion_index = _indices[ indices_index ].array_index;
			_indices[ indices_index ].array_index = -1;

			T* object = _pointer_handle.as_type + deletion_index;
			T->~T();
		}
	}
}

template<typename T, size_t32 S>
typename indexed_array<T,S>::pointer indexed_array<T,S>::find( index_key key )
{
	size_t32 generation = key / S;
	size_t32 indices_index = key % S;

	CRAP_ASSERT_DEBUG( _indices[ indices_index ].generation == generation, "Index generation not correct" );

	i32 find_index = _indices[ indices_index ].array_index;

	return _pointer_handle.as_type + find_index;
}

template<typename T, size_t32 S>
typename indexed_array<T,S>::const_pointer indexed_array<T,S>::find( index_key key ) const
{

	size_t32 generation = key / S;
	size_t32 indices_index = key % S;

	CRAP_ASSERT_DEBUG( _indices[ indices_index ].generation == generation, "Index generation not correct" );

	i32 find_index = _indices[ indices_index ].array_index;

	return _pointer_handle.as_type + find_index;
}

} //lib namespace

#endif // CRAP_CONTAINER_INDEXEDARRAY_H