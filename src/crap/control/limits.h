////////////////////////////////////////////////////////
//	CRAP Library
//!		@file limits.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Provides info about Type limits
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_LIMITS_H
#define CRAP_CONTROL_LIMITS_H

#include "config/types.h"

//lib namespace
namespace crap
{

template<typename T>
struct limits
{
public:
	static const T MIN = 0;
	static const T MAX = 0;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = false;
};

template<>
struct limits<b8>
{
public:
	static const b8 MIN = false;
	static const b8 MAX = true;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = false;
};

template<>
struct limits<c8>
{
public:
	static const c8 MIN = C8_MIN;
	static const c8 MAX = C8_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = true;
};

template<>
struct limits<i8>
{
public:
	static const i8 MIN = I8_MIN;
	static const i8 MAX = I8_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = true;
};

template<>
struct limits<u8>
{
public:
	static const u8 MIN = U8_MIN;
	static const u8 MAX = U8_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = false;
};

template<>
struct limits<i16>
{
public:
	static const i16 MIN = I16_MIN;
	static const i16 MAX = I16_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = true;
};

template<>
struct limits<u16>
{
public:
	static const u16 MIN = U16_MIN;
	static const u16 MAX = U16_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = false;
};

template<>
struct limits<i32>
{
public:
	static const i32 MIN = I32_MIN;
	static const i32 MAX = I32_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = true;
};

template<>
struct limits<u32>
{
public:
	static const u32 MIN = U32_MIN;
	static const u32 MAX = U32_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = false;
};

template<>
struct limits<i64>
{
public:
	static const i64 MIN = I64_MIN;
	static const i64 MAX = I64_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = true;
};

template<>
struct limits<u64>
{
public:
	static const u64 MIN = U64_MIN;
	static const u64 MAX = U64_MAX;
	static const bool  IS_INT = true;
	static const bool  IS_SIGNED = false;
};

template<>
struct limits<f32>
{
public:
	static const f32 MIN;
	static const f32 MAX;
	static const bool  IS_INT = false;
	static const bool  IS_SIGNED = true;
};

//const f32 limits<f32>::MIN = F32_MIN;
//const f32 limits<f32>::MAX = F32_MAX;

template<>
struct limits<f64>
{
public:
	static const f64 MIN;
	static const f64 MAX;
	static const bool  IS_INT = false;
	static const bool  IS_SIGNED = true;
};

//const f64 limits<f64>::MIN = F64_MIN;
//const f64 limits<f64>::MAX = F64_MAX;

}	// namespace crap

#endif // CRAP_CONTROL_LIMITS_H
