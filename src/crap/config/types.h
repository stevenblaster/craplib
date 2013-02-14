////////////////////////////////////////////////////////
//	CRAP Library
//!		@file types.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Types predefines
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_TYPES_H
#define CRAP_CONFIG_TYPES_H

#include "config/platforms.h"
#include "config/processors.h"
#include "config/compilers.h"
#include "config/simd.h"

//standard defs if available
#if ( defined(CRAP_COMPILER_GCC) || defined(CRAP_COMPILER_VC) )
	#include <stddef.h>
	#include <cstring> //for memset (vs12 complains)
#endif

//load simd include for 128bit type
#if CRAP_SIMD_VERSION != CRAP_SIMD_NONE
	#include CRAP_SIMD_INCLUDE
#endif

//null pointer
#if defined(NULL)
	#undef NULL
#endif
#if defined(__cplusplus)
	#define NULL 0
#else
	#define NULL ((void*)0)
#endif

//getting sizetypes print & scan
#ifndef __STDC_FORMAT_MACROS // for inttypes.h
	#define __STDC_FORMAT_MACROS
#endif

//visual studio is NOT using c99
#if defined(CRAP_COMPILER_VC)
	#define PRIi8 "i"
	#define PRIi16 "hi"
	#define PRIi32 "I32i"
	#define PRIi64 "I64i"
	#define PRIu8 "u"
	#define PRIx8 "x"
	#define PRIu16 "hu"
	#define PRIx16 "hx"
	#define PRIu32 "I32u"
	#define PRIx32 "I32x"
	#define PRIu64 "I64u"
	#define PRIx64 "I64x"
	#define SCNi8 "i"
	#define SCNi16 "hi"
	#define SCNi32 "li"
	#define SCNi64 "I64i"
	#define SCNu8 "u"
	#define SCNx8 "x"
	#define SCNu16 "hu"
	#define SCNx16 "hx"
	#define SCNu32 "lu"
	#define SCNu64 "I64u"
	#define SCNx64 "I64x"
#else
	#include <inttypes.h>
#endif

#include <stdint.h>
#include <math.h>
#include <float.h>

//shortcut typedefs
typedef bool b8;
typedef char c8;
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;

typedef intptr_t iptr;
typedef uintptr_t uptr;
typedef const char string_t;

//windows overrides
#if !defined(CRAP_PLATFORM_WIN)

typedef int64_t i64;
typedef uint64_t u64;
typedef float_t f32;
typedef double_t f64;

#else

typedef signed long long i64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

//windows threats scan macro hh as h
#undef SCNi8
#undef SCNu8
#define SCNi8 "ci"
#define SCNu8 "cu"

#endif

typedef u32 size_t32;
typedef u64 size_t64;

#if defined(CRAP_COMPILER_GCC)

typedef __int128_t i128;
typedef __uint128_t u128;

#else

typedef
struct type_128_bit
{
	union
	{
		u8  part_8[16];
		u16 part_16[8];
		u32 part_32[4];
		u64 part_64[2];
	};

	type_128_bit( void ) { memset(part_8, 0, 128); }
	type_128_bit( const u8& num ) { part_8[0] = num; }
	type_128_bit( const u16& num ) { part_16[0] = num; }
	type_128_bit( const u32& num ) { part_32[0] = num; }
	type_128_bit( const u64& num ) { part_64[0] = num; }
}
i128;

typedef i128 u128;

#endif


//min and max values
#ifndef B8_MAX
	#define B8_MAX 		1
#endif
#ifndef C8_MAX
	#define C8_MAX 		127
#endif
#ifndef I8_MAX
	#define I8_MAX 		127
#endif
#ifndef U8_MAX
	#define U8_MAX		255
#endif
#ifndef I16_MAX
	#define I16_MAX		32767
#endif
#ifndef U16_MAX
	#define U16_MAX	65535
#endif
#ifndef I32_MAX
	#define I32_MAX		2147483647
#endif
#ifndef U32_MAX
	#define U32_MAX	4294967295
#endif
#ifndef I64_MAX
	#define I64_MAX		9223372036854775807##LL
#endif
#ifndef U64_MAX
	#define U64_MAX	18446744073709551615##ULL
#endif
#ifndef F32_MAX
	#define F32_MAX	FLT_MAX
#endif
#ifndef F64_MAX
	#define F64_MAX	DBL_MAX
#endif

#ifndef B8_MIN
	#define B8_MIN 		0
#endif
#ifndef C8_MIN
	#define C8_MIN		( -C8_MAX -1 )
#endif
#ifndef I8_MIN
	#define I8_MIN		( -I8_MAX -1 )
#endif
#ifndef U8_MIN
	#define U8_MIN		0
#endif
#ifndef I16_MIN
	#define I16_MIN		( -I16_MAX -1 )
#endif
#ifndef U16_MIN
	#define U16_MIN		0
#endif
#ifndef I32_MIN
	#define I32_MIN		( -I32_MAX -1 )
#endif
#ifndef U32_MIN
	#define U32_MIN		0
#endif
#ifndef I64_MIN
	#define I64_MIN		( -I64_MAX -1 )
#endif
#ifndef U64_MIN
	#define U64_MIN		0
#endif
#ifndef F32_MIN
	#define F32_MIN		( -F32_MAX -1 )
#endif
#ifndef F64_MIN
	#define F64_MIN		( -F64_MAX -1 )
#endif


#endif // CRAP_CONFIG_TYPES_H
