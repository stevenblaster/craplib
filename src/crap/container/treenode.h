////////////////////////////////////////////////////////
//  CRAP Library
//		@file treenode.h
//
//	Creator:
//		Steffen Kopany <steffen@kopany.at>
//
//	Author(s):
// 		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright (c) 2012 Steffen Kopany
//
//	Description:
//		@brief Basic tree node for trees
//		supports yet some recursive and some iterative 
//		methods, will not delete or allocate, just link 
//		and unlink
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_TREENODE_H
#define CRAP_CONTAINER_TREENODE_H

#include "control/compare.h"

//lib namespace
namespace crap
{
	
/*
 * @brief struct holding data for trees
 */
template <class T, class C = crap::less<T> >
struct tree_node 
{
	
	//typedefs
	typedef T& 								reference;
	typedef const T& 						const_reference;
	typedef size_t32		 				size_type;			//i guess int32 is enough
	typedef std::ptrdiff_t					difference_type;	//do we need this? look up local types!
	typedef T 								value_type;
	typedef T*								pointer;
	typedef const T*						const_pointer;
	typedef tree_node<T,C>*					node_pointer;
	typedef tree_node<T,C>&					node_reference;
	typedef const tree_node<T,C>& 			const_node_reference;
	
	enum node_type
	{
		parent =0,
		left,
		right
	};
	
	C is_less;				// compare
	tree_node* sub_node[3];	// seperated by enum: parent, left, right
	T data;					// data

	// @brief default constructor - note that as in stl T needs a default constructor too
	explicit tree_node(void) : data(T())
	{
		sub_node[parent] = 0;
		sub_node[left] = 0;
		sub_node[right] = 0;
	}
	
	// @brief copy constructor
	tree_node(const tree_node& node) : data(node.data)
	{
		sub_node[parent] = node.sub_node[parent];
		sub_node[left] = node.sub_node[left];
		sub_node[right] = node.sub_node[right];
	}

	// @brief value constructor
	tree_node(const T& d) : data(d)
	{
		sub_node[parent] = 0;
		sub_node[left] = 0;
		sub_node[right] = 0;
	}
	
	// @brief constructor using values
	tree_node(tree_node* p, const T& d, tree_node* l, tree_node* r) : data(d)
	{
		sub_node[parent] = p;
		sub_node[left] = l;
		sub_node[right] = r;
	}

	// @brief copy constructor - template
	template <class U, class V> // <U,V>??
	tree_node (const tree_node& t) : data(t.data)
	{
		sub_node[parent] = t.sub_node[parent];
		sub_node[left] = t.sub_node[right];
		sub_node[right] = t.sub_node[right];
	}
	
	/*
	 * Operator overloading
	 */
	 
	// @brief assignment operator
	tree_node& operator=(const tree_node& other)
	{
		sub_node[parent] = other.sub_node[parent];
		sub_node[left] = other.sub_node[right];
		sub_node[right] = other.sub_node[right];
		data = other.data;
		return *this;
	}
		
	/*
	 * Member methods - general
	 */
	
	// @brief zeros all pointer of node
	inline void zero_node(node_pointer node) const;

	// @brief unlink subtree from tree and return root node
	inline node_pointer unlink_subtree(node_pointer node);
	
	// @brief rotate tree to left, using node as rotation point
	inline node_pointer rotate_left(node_pointer node);

	// @brief rotate tree to right, using node as rotation point
	inline node_pointer rotate_right(node_pointer node);
	
	// @brief unlink selected node and reconnect tree, returns unlinked node
	inline node_pointer unlink(node_pointer delete_node);
	
	/*
	 * Member methods - recursive
	 */
	
	// @brief search key starting from node recursively
	node_pointer search_recursive(node_pointer node, value_type key) const;
	
	// @brief minimal value starting from node recursively
	node_pointer min_recursive(node_pointer node) const;
	
	// @brief maximum value starting from node recursively
	node_pointer max_recursive(node_pointer node) const;
	
	// @brief minimum depht starting from node recusively
	size_type min_depth_recursive(node_pointer node) const;

	// @brief maximum depht starting from node recursively
	size_type max_depth_recursive(node_pointer node) const;
	
	// @brief adding new node with data starting from node recursively, returns 0 if failed
	node_pointer insert_recursive(node_pointer new_node, node_pointer parse_node);
	
	// @brief get number of nodes of specific height vom subnode
	size_type depth_elements_recursive(node_pointer node, int depth, int current_depth=0, int element_counter=0);
	
	/*
	 * Member methods - iterative
	 */
	
	// @brief minimal value starting from node iterativley
	inline node_pointer min_iterative(node_pointer node) const;
	
	// @brief maximum value starting from node iterativley
	inline node_pointer max_iterative(node_pointer node) const;
	
	// @brief next lower value starting from node 
	inline node_pointer successor_iterative(node_pointer node) const;

	// @brief next higher value starting from node
	inline node_pointer predecessor_iterative(node_pointer node) const;
	
	// @brief looking for median value and returns pointer
	inline node_pointer median_iterative(node_pointer low_node, node_pointer high_node) const;
};

/*
 * General methods - definition
 */

template <class T, class C>
void tree_node<T,C>::zero_node(node_pointer node) const
{
	if(node != 0)
	{
		sub_node[parent] = 0;
		sub_node[left] = 0;
		sub_node[right] = 0;
	}
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::unlink_subtree(node_pointer node)
{
	if(node != 0)
	{
		if(node->sub_node[parent] != 0)
		{
			if(node->sub_node[parent]->subnode[right] == node)
				node->sub_node[parent]->subnode[right] = 0;
			else if(node->sub_node[parent]->subnode[left] == node)
				node->sub_node[parent]->subnode[left] = 0;
			else
				return 0;
		}
			
		return node;
	}
	return 0;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::rotate_left(node_pointer node)
{
	if(node == 0 || node->sub_node[right] == 0)
		return 0;

	node_pointer right_node = node->sub_node[right];
	
	node->sub_node[right] = right_node->sub_node[left];
	right_node->sub_node[left] = node;
	
	right_node->sub_node[parent] = node->sub_node[parent];
	node->sub_node[parent] = right_node;

	if(node->sub_node[right] != 0)
		node->sub_node[right]->sub_node[parent] = node;

	return right_node;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::rotate_right(node_pointer node)
{
	if(node == 0 || node->sub_node[left] == 0)
		return 0;

	node_pointer left_node = node->sub_node[left];
	
	node->sub_node[left] = left_node->sub_node[right];
	left_node->sub_node[right] = node;
	
	left_node->sub_node[parent] = node->sub_node[parent];
	node->sub_node[parent] = left_node;

	if(node->sub_node[left] != 0)
		node->sub_node[left]->sub_node[parent] = node;

	return left_node;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::unlink(node_pointer delete_node)
{
	if( delete_node == 0 )
		return 0;
	
	if( delete_node->sub_node[parent] != 0 ) 
	{
		// leaf
		if( delete_node->sub_node[left] == 0 && delete_node->sub_node[right] == 0 ) 
		{
			if( delete_node == delete_node->sub_node[parent]->sub_node[right] )
				delete_node->sub_node[parent]->sub_node[right] = 0;
			else if( delete_node == delete_node->sub_node[parent]->sub_node[left] )
				delete_node->sub_node[parent]->sub_node[left] = 0;
			else
				return 0;

			return delete_node;
		}
		// node on the right
		else if( delete_node->sub_node[left] == 0 && delete_node->sub_node[right] != 0 ) 
		{
			if( delete_node == delete_node->sub_node[parent]->sub_node[right] )
			{
				delete_node->sub_node[parent]->sub_node[right] = delete_node->sub_node[right];
				delete_node->sub_node[right]->sub_node[parent] = delete_node->sub_node[parent];
			}
			else if( delete_node == delete_node->sub_node[parent]->sub_node[left] )
			{
				delete_node->sub_node[parent]->sub_node[left] = delete_node->sub_node[right];
				delete_node->sub_node[right]->sub_node[parent] = delete_node->sub_node[parent];
			}
			else
				return 0;

			return delete_node;
		}
		// node on the left
		else if( delete_node->sub_node[left] != 0 && delete_node->sub_node[right] == 0 ) 
		{
			if( delete_node == delete_node->sub_node[parent]->sub_node[right] )
			{
				delete_node->sub_node[parent]->sub_node[right] = delete_node->sub_node[left];
				delete_node->sub_node[left]->sub_node[parent] = delete_node->sub_node[parent];
			}
			else if( delete_node == delete_node->sub_node[parent]->sub_node[left] )
			{
				delete_node->sub_node[parent]->sub_node[left] = delete_node->sub_node[left];
				delete_node->sub_node[left]->sub_node[parent] = delete_node->sub_node[parent];
			}
			else
				return 0;

			return delete_node;
		}
	}
	
	// node on both sides or no parent (must be root then)
	if( delete_node->sub_node[left] != 0 )
	{
		node_pointer previous_node = predecessor_iterative(delete_node);

		if( previous_node->sub_node[parent] != 0 ) 
		{
			if( previous_node->sub_node[parent]->sub_node[right] == previous_node )
				previous_node->sub_node[parent]->sub_node[right] = previous_node->sub_node[left];
			else if( previous_node->sub_node[parent]->sub_node[left] == previous_node )
				previous_node->sub_node[parent]->sub_node[left] = previous_node->sub_node[left];
			else
				return 0;
		}
		else
			return 0;

		delete_node->data = previous_node->data;
		return previous_node;
	}
	else if( delete_node->sub_node[right] != 0 )
	{
		node_pointer previous_node = successor_iterative(delete_node);

		if( previous_node->sub_node[parent] != 0 ) 
		{
			if( previous_node->sub_node[parent]->sub_node[right] == previous_node )
				previous_node->sub_node[parent]->sub_node[right] = previous_node->sub_node[right];
			else if( previous_node->sub_node[parent]->sub_node[left] == previous_node )
				previous_node->sub_node[parent]->sub_node[left] = previous_node->sub_node[right];
			else
				return 0;
		}
		else
			return 0;

		delete_node->data = previous_node->data;
		return previous_node;
	}
	return 0;
}


/*
 * Recursive methods - definition
 */

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::search_recursive(node_pointer node, T key) const
{
	if(node != 0)
	{
		if(node->data < key)
		{
			return search_recursive(node->sub_node[right], key);
		}
		else if(node->data > key)
		{
			return search_recursive(node->sub_node[left], key);
		}
	}
	return node;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::min_recursive(node_pointer node) const
{
	if(node != 0)
	{
		if(node->sub_node[left] != 0)
			return min_recursive(node->sub_node[left]);
	}
	return node;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::max_recursive(node_pointer node) const
{
	if(node != 0)
	{
		if(node->sub_node[right] != 0)
			return max_recursive(node->sub_node[right]);
	}
	return node;
}

template <class T, class C>
size_t32 tree_node<T,C>::min_depth_recursive(node_pointer node) const
{
	if(node != 0)
	{
		size_t32 left_depth = min_depth_recursive(node->sub_node[left]);
		size_t32 right_depth = min_depth_recursive(node->sub_node[right]);

		return (left_depth < right_depth) ? left_depth + 1 : right_depth + 1;
	}
	return 0;
}

template <class T, class C>
size_t32 tree_node<T,C>::max_depth_recursive(node_pointer node) const
{
	if(node != 0)
	{
		size_t32 left_depth = max_depth_recursive(node->sub_node[left]);
		size_t32 right_depth = max_depth_recursive(node->sub_node[right]);

		return (left_depth > right_depth) ? left_depth + 1 : right_depth + 1;
	}
	return 0;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::insert_recursive(node_pointer new_node, node_pointer parse_node)
{
	if( parse_node == 0 ) 
	{
		return new_node;
	}
	else if( is_less(new_node->data, parse_node->data) ) 
	{
		if( parse_node->sub_node[left] == 0 )
		{
			parse_node->sub_node[left] = new_node;
			new_node->sub_node[parent] = parse_node;
			return new_node;
		}
		else
			return insert_recursive(new_node, parse_node->sub_node[left]);
	} 
	else if( !is_less(new_node->data, parse_node->data) ) 
	{
		if( parse_node->sub_node[right] == 0 )
		{
			parse_node->sub_node[right] = new_node;
			new_node->sub_node[parent] = parse_node;
			return new_node;
		}
		else
			return insert_recursive(new_node, parse_node->sub_node[right]);
	}
	else
		return 0;
}

template <class T, class C>
size_t32 tree_node<T,C>::depth_elements_recursive(node_pointer node, int depth, int current_depth/*=0*/, int element_counter/*=0*/)
{
	if(node == 0)
		return element_counter;

	if( current_depth == depth )
		++element_counter;
		
	if( current_depth < depth ) {
		if(node->sub_node[left] != 0)
			element_counter = depth_elements_recursive(node->sub_node[left], depth, current_depth+1, element_counter);
		if(node->sub_node[right] != 0)
			element_counter = depth_elements_recursive(node->sub_node[right], depth, current_depth+1, element_counter);
	}
	return element_counter;
}

/*
 * Iterative methods - definition
 */

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::min_iterative(node_pointer node) const
{
	if(node != 0)
	{
		while(node->sub_node[left] != 0)
			node = node->sub_node[left];
	}
	return node;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::max_iterative(node_pointer node) const
{
	if(node != 0)
	{
		while(node->sub_node[right] != 0)
			node = node->sub_node[right];
	}
	return node;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::successor_iterative(node_pointer node) const
{
	if(node != 0)
	{
		if(node->sub_node[right] != 0)
			return min_iterative(node->sub_node[right]);

		node_pointer node_parent = node->sub_node[parent];
		while(node_parent != 0 && node == node_parent->sub_node[right]) 
		{
			node = node_parent;
			node_parent = node_parent->sub_node[parent];
		}
		node = node_parent;
	}
	return node;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::predecessor_iterative(node_pointer node) const
{
	if(node != 0)
	{
		if(node->sub_node[left] != 0)
			return min_iterative(node->sub_node[left]);

		node_pointer node_parent = node->sub_node[parent];
		while(node_parent != 0 && node == node_parent->sub_node[left]) 
		{
			node = node_parent;
			node_parent = node_parent->sub_node[parent];
		}
		node = node_parent;
	}
	return node;
}

template <class T, class C>
tree_node<T,C>* tree_node<T,C>::median_iterative(node_pointer low_node, node_pointer high_node) const
{
	if( low_node == 0 || high_node == 0 )
		return 0;

	if( low_node == high_node )
		return low_node;

	while(is_less(low_node->data, high_node->data))
	{
		low_node = successor_iterative(low_node); // to right
		if( low_node == high_node )
			return low_node;
		high_node = predecessor_iterative(high_node);	// to left
		if( low_node == high_node )
			return high_node;
	}

	return low_node;
}

	
}	// namespace crap

#endif	// CRAP_CONTAINER_TREENODE_H