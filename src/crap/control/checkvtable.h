////////////////////////////////////////////////////////
//	CRAP Library
//!		@file checkvtable.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Checking if class contains virtual pointer
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_CHECKVTABLE_H
#define CRAP_CONTROL_CHECKVTABLE_H

//lib namespace
namespace crap
{

/*
 *! @brief Class template checking vtable
 */

template<class T>
struct has_vtable
{
	struct test_class : T
	{
		test_class() {}
		virtual ~test_class();
	};

	static const bool RESULT = (sizeof(test_class) == sizeof(T));
};

/*
 *! @brief Template specialization
 */

template<>
struct has_vtable<b8>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<i32>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<u32>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<i16>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<u16>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<c8>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<i8>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<u8>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<f32>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<i64>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<u64>
{
	static const bool RESULT = false;
};

template<>
struct has_vtable<f64>
{
	static const bool RESULT = false;
};


}	// namespace crap

#endif // CRAP_CONTROL_CHECKVTABLE_H
