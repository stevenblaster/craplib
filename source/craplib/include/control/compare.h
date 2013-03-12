////////////////////////////////////////////////////////
//	CRAP Library
//!		@file compare.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Clones of STL's less, greater,...
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_COMPARE_H
#define CRAP_CONTROL_COMPARE_H

//lib namespace
namespace crap
{

/*
 *! @brief help structs like STL..
 */

//! @brief basic binary template
template <class Arg1, class Arg2, class Result>
struct binary_function
{
	typedef Arg1 	first_argument_type;
	typedef Arg2 	second_argument_type;
	typedef Result 	result_type;
};

//! @brief check if first argument is less then second
template <class T>
struct less : binary_function <T,T,bool>
{
	bool operator()(const T& x, const T& y) const
	{
		return x<y;
	}
};

//! @brief check if first argument is greater then second
template <class T>
struct greater : binary_function <T,T,bool>
{
	bool operator()(const T& x, const T& y) const
	{
		return x>y;
	}
};

//! @brief check if first argument is equal to second
template <class T>
struct equal_to : binary_function <T,T,bool>
{
	bool operator() (const T& x, const T& y) const
	{
		return x==y;
	}
};

//! @brief check if first argument is not equal to second
template <class T>
struct not_equal_to : binary_function <T,T,bool>
{
	bool operator() (const T& x, const T& y) const
	{
		return x!=y;
	}
};

//! @brief check if first argument is greater equal then second
template <class T>
struct greater_equal : binary_function <T,T,bool>
{
	bool operator() (const T& x, const T& y) const
	{
		return x>=y;
	}
};

//! @brief check if first argument is less equal then second
template <class T>
struct less_equal : binary_function <T,T,bool>
{
	bool operator() (const T& x, const T& y) const
	{
		return x<=y;
	}
};

}	// namespace crap

#endif // CRAP_CONTROL_COMPARE_H
