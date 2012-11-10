////////////////////////////////////////////////////////
//  CRAP Library
//!		@file binarytree.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Binary search tree with the possibility
//		to realign / balance
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_BINARYTREE_H
#define CRAP_CONTAINER_BINARYTREE_H

#include "memory/allocatordefault.h"
#include "control/compare.h"
#include "container/treenode.h"

//lib namespace
namespace crap
{

/*
 *! @brief Binary search tree class
 */

template <class T, class C = crap::less<T>, class A = crap::allocator_default<tree_node<T,C> > >
class binary_tree
{
public:

	//typedefs
	typedef T& 								reference;
	typedef const T& 						const_reference;
	typedef size_t32		 				size_type;			//i guess int32 is enough
	typedef std::ptrdiff_t					difference_type;	//do we need this? look up local types!
	typedef T 								value_type;
	typedef A 								allocator_type;
	typedef T*								pointer;
	typedef const T*						const_pointer;
	typedef tree_node<T,C>					node_type;
	typedef tree_node<T,C>*					node_pointer;
	typedef tree_node<T,C>&					node_reference;
	typedef const tree_node<T,C>& 			const_node_reference;

protected:

	/*
	 * Class members
	 */

	A _allocator;
	node_pointer _root;
	size_type _size;

	/*
	 * Protected Methods
	 */

	void delete_recursive( node_pointer );

public:

	friend struct tree_iterator;

	struct tree_iterator
	{
	private:
		node_pointer _pointer;

	public:
		tree_iterator( void ) : _pointer(0) { }
		tree_iterator( node_pointer element ) : _pointer(element) { }
		tree_iterator( const tree_iterator& other ) : _pointer( other._pointer ) {}
		tree_iterator& operator=( const tree_iterator& other )
		{
			_pointer = other._pointer;
			return *this;
		}
		void operator++( void )
		{
			_pointer = _pointer->successor_iterative( _pointer );
		}
		void operator--( void )
		{
			_pointer = _pointer->predecessor_iterative( _pointer );
		}
		bool operator==( const tree_iterator& other ) const
		{
			return _pointer == other._pointer;
		}
		bool operator!=( const tree_iterator& other ) const
		{
			return _pointer != other._pointer;
		}
		node_pointer operator->( void )
		{
			return _pointer;
		}
		T& operator*( void )
		{
			return _pointer->data;
		}
		const T& operator*( void ) const
		{
			return _pointer->data;
		}
		node_pointer ptr( void ) const
		{
			return _pointer;
		}
	};	// end tree_iterator


	/*
	 * Iterator handling
	 */

	typedef tree_iterator 			iterator;							//iterator
	typedef const tree_iterator		const_iterator;						//const iterator

	iterator top(void) { return iterator( _root ); }
	iterator begin(void) { return iterator( min_node() ); }
	iterator end(void) { return iterator(0); }

	//same as above, just const
	const_iterator top(void) const { return const_iterator( _root ); }
	const_iterator begin(void) const { return const_iterator( min_node() ); }
	const_iterator end(void) const { return const_iterator(0); }

	/*
	 * public members
	 */

	//! @brief Default constructor
	inline binary_tree( void );

	//! @brief Copy constructor
	inline binary_tree( const binary_tree& other );

	//! @brief Destructor
	inline ~binary_tree( void );

	//! @brief Finds key and returns iterator ( end() if failed )
	iterator find(const_reference key);

	//! @brief Finds key and returns constant iterator ( end() if failed )
	const_iterator find(const_reference key) const;

	//! @brief Inserting key if unique and returns iterator ( end() if failed )
	iterator insert(const_reference key);

	//! @brief Find key and remove element
	bool remove( const_reference key );

	//! @brief Rotate tree at root to left
	bool rotate_left( void );

	//! @brief Rotate tree at root to right
	bool rotate_right( void );

	//! @brief Finds the smalles element and returns iterator
	iterator min_node( void );

	//! @brief Finds the smalles element and returns constant iterator
	const_iterator min_node( void ) const;

	//! @brief Finds the biggest element and returns iterator
	iterator max_node( void );

	//! @brief Finds the biggest element and returns constant iterator
	const_iterator max_node( void ) const;

	//! @brief Clears tree from root
	void clear( void );

	//! @brief Realigns all element by attemting to balance content
	void realign( void );

	//! @brief Gets width of specific height
	size_type depth_elements(int level) const;

	//! @brief Gets maximum width of tree
	size_type width( void ) const;

	//! @brief Left depth of nodes
	size_type depth_left(void) const;

	//! @brief Right depth of nodes
	size_type depth_right(void) const;

	//! @brief Tree depth of nodes
	size_type depth(void) const;

	//! @brief Tree number of stored nodes
	size_type size(void) const;
};

/*
 * Protected Methods
 */

template <class T, class C, class A>
void binary_tree<T,C,A>::delete_recursive( node_pointer node )
{
	if(node == 0)
		return;

	delete_recursive( node->sub_node[node_type::left] );
	delete_recursive( node->sub_node[node_type::right] );

	_allocator.deallocate(node);
}

/*
 * Public methods
 */

template <class T, class C, class A>
binary_tree<T,C,A>::binary_tree( void ) : _root(0), _size(0) {}

template <class T, class C, class A>
binary_tree<T,C,A>::binary_tree( const binary_tree& other ): _root(0), _size(other._size)
{
	for(binary_tree::const_iterator it = other.begin(); it != other.end(); ++it)
	{
		node_pointer new_node = _allocator.allocate();
		new_node = *it;
		CRAP_ASSERT_DEBUG(add_node(new_node, _root) != 0, "Copy constructor: Node insertion failed");
	}
}

template <class T, class C, class A>
binary_tree<T,C,A>::~binary_tree( void )
{
	clear();
}


template <class T, class C, class A>
typename binary_tree<T,C,A>::iterator binary_tree<T,C,A>::find(const_reference key)
{
	return iterator( _root->search_recursive(_root, key) );
}

template <class T, class C, class A>
typename CRAP_TEMPLATE_CONST_FIX binary_tree<T,C,A>::const_iterator binary_tree<T,C,A>::find(const_reference key) const
{
	return const_iterator( _root->search_recursive(_root, key) );
}

template <class T, class C, class A>
typename binary_tree<T,C,A>::iterator binary_tree<T,C,A>::insert(const_reference key)
{
	node_pointer new_node = _allocator.allocate();
	_allocator.construct(new_node, key);
	new_node = _root->insert_recursive(new_node, _root);

	CRAP_ASSERT_DEBUG( new_node != 0, "Insert: Node insertion failed" );

	if(_size == 0)
		_root = new_node;

	++_size;

	return iterator( new_node );
}

template <class T, class C, class A>
bool binary_tree<T,C,A>::remove( const_reference key )
{
	node_pointer searched_node = _root->search_recursive(_root, key);
	if( searched_node != 0 )
	{
		if(searched_node == _root)
		{
			node_pointer root_left = _root->sub_node[node_type::left];
			node_pointer root_right = _root->sub_node[node_type::right];

			node_pointer root_predecessor = _root->predecessor_iterative(_root);
			node_pointer root_successor = _root->successor_iterative(_root);

			searched_node = _root->unlink(searched_node);
			if( searched_node == 0 )
				return false;

			if(root_left->sub_node[node_type::right] == root_right)
			{
				_root = root_left;
			}
			else if(root_right->sub_node[node_type::left] == root_left)
			{
				_root = root_left;
			}
			else if(_root == searched_node)
				return false;

		}
		else
		{
			searched_node = _root->unlink(searched_node);
			if( searched_node == 0 )
				return false;
		}
		_allocator.deallocate(searched_node);
		--_size;
		return true;
	}
	return false;
}

template <class T, class C, class A>
bool binary_tree<T,C,A>::rotate_left( void )
{
	node_pointer check_node = _root->rotate_left(_root);

	if(check_node == 0)
		return false;

	_root = check_node;
	return true;
}

template <class T, class C, class A>
bool binary_tree<T,C,A>::rotate_right( void )
{
	node_pointer check_node = _root->rotate_right(_root);

	if(check_node == 0)
		return false;

	_root = check_node;
	return true;
}

template <class T, class C, class A>
typename binary_tree<T,C,A>::iterator binary_tree<T,C,A>::min_node( void )
{
	return iterator( _root->min_recursive(_root) );
}

template <class T, class C, class A>
typename CRAP_TEMPLATE_CONST_FIX binary_tree<T,C,A>::const_iterator binary_tree<T,C,A>::min_node( void ) const
{
	return const_iterator( _root->min_recursive(_root) );
}

template <class T, class C, class A>
typename binary_tree<T,C,A>::iterator binary_tree<T,C,A>::max_node( void )
{
	return iterator( _root->max_recursive(_root)  );
}

template <class T, class C, class A>
typename CRAP_TEMPLATE_CONST_FIX binary_tree<T,C,A>::const_iterator binary_tree<T,C,A>::max_node( void ) const
{
	return const_iterator( _root->max_recursive(_root)  );
}

template <class T, class C, class A>
void binary_tree<T,C,A>::clear( void )
{
	delete_recursive( _root );
	_root = 0;
	_size = 0;
}

template <class T, class C, class A>
void binary_tree<T,C,A>::realign( void )
{
//	node_pointer new_root = build_tree( median(
//	                                        min_value(_root),
//	                                        max_value(_root), 0), 0,
//	                                    min_value(_root),
//	                                    max_value(_root));
//	clear();
//	_root = new_root;
}

template <class T, class C, class A>
size_t32 binary_tree<T,C,A>::depth_elements(int level) const
{
	return _root->depth_elements_recursive(_root, level, 0, 0);
}

template <class T, class C, class A>
size_t32 binary_tree<T,C,A>::width( void ) const
{
	int max_depth = depth();
	int max_width = 0;
	for(int i=0; i<max_depth; ++i)
	{
		int width = depth_elements(i);
		max_width = (max_width < width) ? width : max_width;
	}
	return max_width;
}

template <class T, class C, class A>
size_t32 binary_tree<T,C,A>::depth_left(void) const
{
	if(_root != 0)
		return _root->max_depth_recursive(_root->sub_node[node_type::left]);

	return 0;
}

template <class T, class C, class A>
size_t32 binary_tree<T,C,A>::depth_right(void) const
{
	if(_root != 0)
		return _root->max_depth_recursive(_root->sub_node[node_type::right]);

	return 0;
}

template <class T, class C, class A>
size_t32 binary_tree<T,C,A>::depth(void) const
{
	return _root->max_depth_recursive(_root) - 1;
}

template <class T, class C, class A>
size_t32 binary_tree<T,C,A>::size(void) const
{
	return _size;
}

}	// namespace crap

#endif // CRAP_CONTAINER_BINARYTREE_H
