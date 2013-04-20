////////////////////////////////////////////////////////
//	CRAP Library
//!		@file intrusivelist.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Intrusive List
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTAINER_INTRUSIVELIST_H
#define CRAP_CONTAINER_INTRUSIVELIST_H

#include "crap.h"

//lib namespace
namespace crap
{

template<typename T>
class intrusive_list;

template<typename T>
class intrusive_list_node
{
public:
	explicit intrusive_list_node( T* parent, intrusive_list<T>* container, bool push_back = true );
	~intrusive_list_node( void );

	CRAP_INLINE
	T* parent( void );

	CRAP_INLINE
	intrusive_list<T>* container( void );

private:
	friend class intrusive_list<T>;
	friend struct intrusive_list<T>::intrusive_iterator;

	intrusive_list_node* _previous;
	intrusive_list_node* _next;
	T* _parent;
	intrusive_list<T>* _container;
};

template<typename T>
class intrusive_list
{
public:

	//typedefs
	typedef T& 								reference;
	typedef const T& 						const_reference;
	typedef size_t32		 				size_type;			//i guess int32 is enough
	typedef std::ptrdiff_t					difference_type;	//do we need this? look up local types!
	typedef T 								value_type;
	typedef T*								pointer;
	typedef const T*						const_pointer;
	typedef intrusive_list_node<T>			node_type;
	typedef intrusive_list_node<T>*			node_pointer;
	typedef const intrusive_list_node<T>*	const_node_pointer;
	typedef intrusive_list_node<T>&			node_reference;
	typedef const intrusive_list_node<T>& 	const_node_reference;

	friend struct intrusive_iterator;

	struct intrusive_iterator
	{
	private:
		node_pointer _pointer;

	public:
		intrusive_iterator( void ) : _pointer(0) { }

		explicit intrusive_iterator( node_pointer element ) : _pointer(element) { }

		intrusive_iterator( const intrusive_iterator& other ) : _pointer( other._pointer ) {}

		CRAP_INLINE
		intrusive_iterator& operator=( const intrusive_iterator& other )
		{
			_pointer = other._pointer;
			return *this;
		}

		CRAP_INLINE
		void operator++( void )
		{
			if( _pointer != 0 )
				_pointer = _pointer->_next;
		}

		CRAP_INLINE
		void operator--( void )
		{
			if( _pointer != 0 )
				_pointer = _pointer->_previous;
		}

		CRAP_INLINE
		bool operator==( const intrusive_iterator& other ) const
		{
			return _pointer == other._pointer;
		}

		CRAP_INLINE
		bool operator!=( const intrusive_iterator& other ) const
		{
			return _pointer != other._pointer;
		}

		CRAP_INLINE
		pointer operator->( void )
		{
			return _pointer->parent();
		}

		CRAP_INLINE
		T& operator*( void )
		{
			return *(_pointer->parent());
		}

		CRAP_INLINE
		const T& operator*( void ) const
		{
			return *(_pointer->parent());
		}

		CRAP_INLINE
		node_pointer ptr( void ) const
		{
			return _pointer;
		}
	};	// end intrusive_iterator


	/*
	 * Iterator handling
	 */

	typedef intrusive_iterator 			iterator;							//iterator
	typedef const intrusive_iterator	const_iterator;						//const iterator

	CRAP_INLINE
	iterator top(void) { return iterator( _end ); }

	CRAP_INLINE
	iterator begin(void) { return iterator( _begin ); }

	CRAP_INLINE
	iterator end(void) { return iterator( 0 ); }

	//same as above, just const
	CRAP_INLINE
	const_iterator top(void) const { return const_iterator( _end ); }

	CRAP_INLINE
	const_iterator begin(void) const { return const_iterator( _begin ); }

	CRAP_INLINE
	const_iterator end(void) const { return const_iterator( _end->_next ); }

	explicit intrusive_list( void );

	~intrusive_list( void );

	CRAP_INLINE
	size_t32 size( void ) const;

	CRAP_INLINE
	void push_back( intrusive_list_node<T>* node );

	CRAP_INLINE
	void push_front( intrusive_list_node<T>* node );

	CRAP_INLINE
	void pop_back( void );

	CRAP_INLINE
	void pop_front( void );

	CRAP_INLINE
	void remove( intrusive_list_node<T>* node );

private:
	intrusive_list_node<T>* _begin;
	intrusive_list_node<T>* _end;

	size_t32 _size;
};

/*
 * INTRUSIVE LIST 
 */
template<typename T>
intrusive_list<T>::intrusive_list( void ) :
	_begin(0), _end(0), _size(0)
{

}

template<typename T>
intrusive_list<T>::~intrusive_list( void )
{

}

template<typename T>
size_t32 intrusive_list<T>::size( void ) const
{
	return _size;
}

template<typename T>
void intrusive_list<T>::push_back( intrusive_list_node<T>* node )
{
	node->_next = 0;
	node->_previous = _end;
	if( _end != 0 )
		_end->_next = node;
	_end = node;
	if( _begin == 0 )
		_begin = node;

	++_size;
}

template<typename T>
void intrusive_list<T>::push_front( intrusive_list_node<T>* node )
{
	node->_next = _begin;
	node->_previous = 0;
	if( _begin != 0 )
		_begin->_previous = node;
	_begin = node;
	if( _end == 0 )
		_end = node;

	++_size;
}

template<typename T>
void intrusive_list<T>::pop_back( void )
{
	if( _size == 1 )
	{
		_begin = 0;
		_end = 0;
		_size = 0;
		return;
	}

	if( _size != 0 )
	{
		intrusive_list_node del_node = _end;
		del_node->_previous->_next = 0;
		_end = del_node->_previous;
		del_node->_previous = 0;
		--_size;
		return;
	}
}

template<typename T>
void intrusive_list<T>::pop_front( void )
{
	if( _size == 1 )
	{
		_begin = 0;
		_end = 0;
		_size = 0;
		return;
	}

	if( _size != 0 )
	{
		intrusive_list_node del_node = _begin;
		del_node->_next->_previous = 0;
		_begin = del_node->_next;
		del_node->_next = 0;
		--_size;
		return;
	}
}

template<typename T>
void intrusive_list<T>::remove( intrusive_list_node<T>* node )
{
	if( _size == 1 )
	{
		_begin = 0;
		_end = 0;
		_size = 0;
		return;
	}

	if( _size != 0 )
	{
		if( node->_next != 0 )
			node->_next->_previous = 0;

		if( node->_previous != 0 )
			node->_previous->_next = 0;

		--_size;
		return;
	}
}

/*
 * INTRUSIVE LIST NODE
 */
template<typename T>
intrusive_list_node<T>::intrusive_list_node( T* parent, intrusive_list<T>* container, bool push_back /* = true */ ) :
	_previous(0), _next(0), _parent( parent ), _container( container )
{
	if( push_back )
	{
		container->push_back( this );
	}
}

template<typename T>
intrusive_list_node<T>::~intrusive_list_node( void )
{
	_container->remove( this );

	_next = 0;
	_previous = 0;
}

template<typename T>
inline T* intrusive_list_node<T>::parent( void )
{
	return _parent;
}

template<typename T>
intrusive_list<T>* intrusive_list_node<T>::container( void )
{
	return _container;
}

} //namespace crap

#endif // CRAP_CONTAINER_INTRUSIVELIST_H