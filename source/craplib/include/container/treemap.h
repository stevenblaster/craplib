////////////////////////////////////////////////////////
//	CRAP Library
//!		@file treemap.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Binary search tree with the possibility
//		to realign / balance. Particially specialized
//		for easy use as map
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_TREEMAP_H
#define CRAP_CONTAINER_TREEMAP_H

#include "memory/stlallocatordefault.h"
#include "control/compare.h"
#include "container/treenode.h"
#include "container/pair.h"
#include "container/binarytree.h"

//lib namespace
namespace crap
{

/*
 * Special less for pair
 *! @todo Special less into compare.h? Gotta check
 */

//! @brief less for first (key) value
template <class T1, class T2>
struct less_first : binary_function<T1, T1, bool>
{
	bool operator()(const crap::pair<T1, T2>& x, const crap::pair<T1, T2>& y) const
	{
		return x.first < y.first;
	}
};

//! @brief less for first (key) value
template <class T1, class T2>
struct less_second : binary_function<T2, T2, bool>
{
	bool operator()(const crap::pair<T1, T2>& x, const crap::pair<T1, T2>& y) const
	{
		return x.second < y.second;
	}
};

/*
 *! @brief using eastl map
 */

//template<typename T1, typename T2, typename Allocator = crap::allocator_default<T> >
//class map : public eastl::map<T1, T2, Allocator>
//{
//};

/*
 *! @brief using binary tree with pair<>
 */

//! @brief using binary tree with pair<>
template<class T1, class T2, class C = crap::less_first<T1, T2>,
		class A = crap::stl_allocator_default<tree_node< pair<T1, T2> ,C> > >
class tree_map : public binary_tree< crap::pair<T1, T2> , C, A>
{

};

}	// namespace crap

#endif // CRAP_CONTAINER_TREEMAP_H
