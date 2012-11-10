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
#ifndef CRAP_CONTAINER_TREE_H
#define CRAP_CONTAINER_TREE_H

#include "control/copyobject.h"

#include "memory/standardallocator.h"
#include "memory/poolallocator.h"

namespace crap
{
namespace container
{
template< typename T, typename U>
struct TreeElement
{
	TreeElement* parent;
	T key;
	U value;
	TreeElement* left;
	TreeElement* right;

	explicit TreeElement( void ) : parent(0), left(0), right(0) {}
	TreeElement( TreeElement* p, const T& k, const U& v, TreeElement* l, TreeElement* r ) : parent(p), key(k), value(v), left(l), right(r) {}
	TreeElement( const TreeElement& other ) : parent(other.parent), key(other.key), value(other.value), left(other.left), right(other.right) {}

	static CRAP_INLINE TreeElement* last( TreeElement* element )
	{
		if( element->right != 0)
			return last( element->right);
		else
			return element;
	}

	static CRAP_INLINE TreeElement* first( TreeElement* element )
	{
		if( element->left != 0)
			return first( element->left);
		else
			return element;
	}

	static CRAP_INLINE TreeElement* next( TreeElement* element, T prev_key )
	{
		T left_key;
		T right_key;

		if( element->left != 0 )
		{
			left_key = element->left->key;
		}

		if( element->right != 0 )
		{
			right_key = element->right->key;
		}

		if( element->left!= 0 && left_key > prev_key && (left_key < element->key || prev_key >= element->key) )
			return next( element->left, prev_key );

		if( element->right != 0 && right_key > prev_key && (right_key < element->key || prev_key >= element->key) )
			return next( element->right, prev_key );

		if( element->key > prev_key )
			return element;

		if( element->parent != 0 )
			return next( element->parent, prev_key );

		return 0;
	}

	CRAP_INLINE bool operator==( const T& other ) const { return other == key; }
	CRAP_INLINE bool operator>( const T& other ) const { return other < key; }
	CRAP_INLINE bool operator<( const T& other ) const { return other > key; }
	CRAP_INLINE bool operator>=( const T& other ) const { return ( other < key || other == key ); }
	CRAP_INLINE bool operator<=( const T& other ) const { return ( other > key || other == key ); }

	CRAP_INLINE bool operator==( const TreeElement& other ) const { return other.key == key; }
	CRAP_INLINE bool operator>( const TreeElement& other ) const { return other.key < key; }
	CRAP_INLINE bool operator<( const TreeElement& other ) const { return other.key > key; }
	CRAP_INLINE bool operator>=( const TreeElement& other ) const { return ( other.key < key || other.key == key ); }
	CRAP_INLINE bool operator<=( const TreeElement& other ) const { return ( other.key > key || other.key == key ); }

	CRAP_INLINE TreeElement* operator++( void ) { return TreeElement::next(this, key); }
};

template<typename T, typename U, class A = memory::StandardAllocator< TreeElement<T,U> > >
class Tree
{
public:
	typedef TreeElement<T,U> Node;

private:
	A _memory;
	u64 _size;
	crap::threading::Mutex _mutex;
	Node* _startNode;

public:

	struct  Iterator
	{
	private:
		Node* _pointer;

	public:
		Iterator( void ) : _pointer(0) { }
		Iterator( Node* element ) : _pointer(element) { }
		Iterator( const Iterator& other ) : _pointer( other._pointer ) {}
		Iterator& operator=( const Iterator& other )
		{
			_pointer = other._pointer;
			return *this;
		}
		void operator++( void )
		{
			_pointer = Node::next( _pointer, _pointer->key );
		}
		bool operator==( const Iterator& other ) const
		{
			return _pointer == other._pointer;
		}
		bool operator!=( const Iterator& other ) const
		{
			return _pointer != other._pointer;
		}
		Node* operator->( void )
		{
			return _pointer;
		}
		Node& operator*( void )
		{
			return *_pointer;
		}
		const T& operator*( void ) const
		{
			return *_pointer;
		}

		const Node* ptr( void ) const
		{
			return _pointer;
		}
	};	// end iterator

	typedef Iterator iterator;
	typedef const Iterator const_iterator;

	CRAP_INLINE Node* last( void ) const
	{
		if( _startNode == 0 )
			return 0;
		else
			return Node::last(_startNode);
	}

	CRAP_INLINE Node* first( void ) const
	{
		if( _startNode == 0 )
			return 0;
		else
			return Node::first(_startNode);
	}

	CRAP_INLINE Node* root( void ) const
	{
		return _startNode;
	}
		//schätz die mitte ab dreh den baum entsprechend! (zb min und max wert hernhemen ;)


private:

	Node* recursiveInsert( const T& key )
	{
	//	if()
	}
};

}
}


#endif // CRAP_CONTAINER_TREE_H
