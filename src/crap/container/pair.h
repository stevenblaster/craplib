////////////////////////////////////////////////////////
//	CRAP Library
//!		@file pair.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Pair container for map
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_PAIR_H
#define CRAP_CONTAINER_PAIR_H

//lib namespace
namespace crap
{

/*
 *! @brief Pair - data holding
 */

template <class T1, class T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	pair( void ) : first( T1() ), second( T2() ) {}
	pair( const T1& x, const T2& y) : first(x), second(y) {}

	template <class U, class V>
	pair (const pair<U,V> &p) : first(p.first), second(p.second) {}
};

template <class T1, class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( pair<T1,T2>(x,y) );
}


}	// namespace crap

#endif // CRAP_CONTAINER_PAIR_H
