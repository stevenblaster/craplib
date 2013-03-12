////////////////////////////////////////////////////////
//	CRAP Library
//!		@file converter.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Convertig integer/float types without
//		over- or underflow
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_CONVERTER_H
#define CRAP_CONTROL_CONVERTER_H

#include <limits>

#include "control/zero.h"
#include "container/staticstring.h"


//lib namespace
namespace crap
{

template<typename FROM, typename TO>
TO convert( const FROM& variable )
{
	return (TO) variable;
}

//damn VC compiler!!!!
//alrigth we just do every f*cking type

//TO BOOL 8 BIT
template<>
inline b8 convert<c8, b8>( const c8& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<i8, b8>( const i8& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<u8, b8>( const u8& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<i16, b8>( const i16& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<u16, b8>( const u16& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<i32, b8>( const i32& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<u32, b8>( const u32& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<i64, b8>( const i64& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<u64, b8>( const u64& variable )
{
	return (variable > 0) ? true : false;
}

template<>
inline b8 convert<f32, b8>( const f32& variable )
{
	return (variable > 0.f) ? true : false;
}

template<>
inline b8 convert<f64, b8>( const f64& variable )
{
	return (variable > 0.0) ? true : false;
}


//TO STANDARD CHAR
template<>
inline c8 convert<b8, c8>( const b8& variable )
{
	return (variable) ? 1 : 0;
}

template<>
inline c8 convert<i8, c8>( const i8& variable )
{
	//usually signed
	//TODO: check if char is always signed!
	return (c8) variable;
}

template<>
inline c8 convert<u8, c8>( const u8& variable )
{
	if( variable > 0 && variable > C8_MAX )
		return C8_MAX;

	return (c8) variable;
}

template<>
inline c8 convert<i16, c8>( const i16& variable )
{
	if( variable < 0 && variable < C8_MIN )
		return C8_MIN;
	else if( variable > 0 && variable > C8_MAX )
		return C8_MAX;

	return (c8) variable;
}

template<>
inline c8 convert<u16, c8>( const u16& variable )
{
	if( variable > 0 && variable > C8_MAX )
		return C8_MAX;

	return (c8) variable;
}

template<>
inline c8 convert<i32, c8>( const i32& variable )
{
	if( variable < 0 && variable < C8_MIN )
		return C8_MIN;
	else if( variable > 0 && variable > C8_MAX )
		return C8_MAX;

	return (c8) variable;
}

template<>
inline c8 convert<u32, c8>( const u32& variable )
{
	if( variable > 0 && variable > C8_MAX )
		return C8_MAX;

	return (c8) variable;
}

template<>
inline c8 convert<i64, c8>( const i64& variable )
{
	if( variable < 0 && variable < C8_MIN )
		return C8_MIN;
	else if( variable > 0 && variable > C8_MAX )
		return C8_MAX;

	return (c8) variable;
}

template<>
inline c8 convert<u64, c8>( const u64& variable )
{
	if( variable > 0 && variable > C8_MAX )
		return C8_MAX;

	return (c8) variable;
}

template<>
inline c8 convert<f32, c8>( const f32& variable )
{
	if( variable < 0.f && variable < C8_MIN * 1.f )
		return C8_MIN;
	else if( variable > 0.f && variable > C8_MAX * 1.f )
		return C8_MAX;

	return (c8) variable;
}

template<>
inline c8 convert<f64, c8>( const f64& variable )
{
	if( variable < 0.0 && variable < C8_MIN * 1.0 )
		return C8_MIN;
	else if( variable > 0.0 && variable > C8_MAX * 1.0 )
		return C8_MAX;

	return (c8) variable;
}

//SIGNED CHAR
template<>
inline i8 convert<b8, i8>( const b8& variable )
{
	return (variable) ? 1 : 0;
}

template<>
inline i8 convert<c8, i8>( const c8& variable )
{
	//usually signed
	//TODO: check if char is always signed!
	return (i8) variable;
}

template<>
inline i8 convert<u8, i8>( const u8& variable )
{
	if( variable > 0 && variable > I8_MAX )
		return I8_MAX;

	return (i8) variable;
}

template<>
inline i8 convert<i16, i8>( const i16& variable )
{
	if( variable < 0 && variable < I8_MIN )
		return I8_MIN;
	else if( variable > 0 && variable > I8_MAX )
		return I8_MAX;

	return (i8) variable;
}

template<>
inline i8 convert<u16, i8>( const u16& variable )
{
	if( variable > 0 && variable > I8_MAX )
		return I8_MAX;

	return (i8) variable;
}

template<>
inline i8 convert<i32, i8>( const i32& variable )
{
	if( variable < 0 && variable < I8_MIN )
		return I8_MIN;
	else if( variable > 0 && variable > I8_MAX )
		return I8_MAX;

	return (i8) variable;
}

template<>
inline i8 convert<u32, i8>( const u32& variable )
{
	if( variable > 0 && variable > I8_MAX )
		return I8_MAX;

	return (i8) variable;
}

template<>
inline i8 convert<i64, i8>( const i64& variable )
{
	if( variable < 0 && variable < I8_MIN )
		return I8_MIN;
	else if( variable > 0 && variable > I8_MAX )
		return I8_MAX;

	return (i8) variable;
}

template<>
inline i8 convert<u64, i8>( const u64& variable )
{
	if( variable > 0 && variable > I8_MAX )
		return I8_MAX;

	return (i8) variable;
}

template<>
inline i8 convert<f32, i8>( const f32& variable )
{
	if( variable < 0.f && variable < I8_MIN * 1.f )
		return I8_MIN;
	else if( variable > 0.f && variable > I8_MAX * 1.f )
		return I8_MAX;

	return (i8) variable;
}

template<>
inline i8 convert<f64, i8>( const f64& variable )
{
	if( variable < 0.0 && variable < I8_MIN * 1.0 )
		return I8_MIN;
	else if( variable > 0.0 && variable > I8_MAX * 1.0 )
		return I8_MAX;

	return (i8) variable;
}


//UNSIGNED CHAR
template<>
inline u8 convert<b8, u8>( const b8& variable )
{
	return (variable) ? 1 : 0;
}

template<>
inline u8 convert<c8, u8>( const c8& variable )
{
	if( variable < 0 )
		return 0;

	return (u8) variable;
}

template<>
inline u8 convert<i8, u8>( const i8& variable )
{
	if( variable < 0 )
		return 0;

	return (u8) variable;
}

template<>
inline u8 convert<i16, u8>( const i16& variable )
{
	if( variable < 0 )
		return 0;
	else if( variable > U8_MAX )
		return U8_MAX;

	return (u8) variable;
}

template<>
inline u8 convert<u16, u8>( const u16& variable )
{
	if( variable > U8_MAX )
		return U8_MAX;

	return (u8) variable;
}

template<>
inline u8 convert<i32, u8>( const i32& variable )
{
	if( variable < 0 )
		return 0;
	else if( variable > U8_MAX )
		return U8_MAX;

	return (u8) variable;
}

template<>
inline u8 convert<u32, u8>( const u32& variable )
{
	if( variable > U8_MAX )
		return U8_MAX;

	return (u8) variable;
}

template<>
inline u8 convert<i64, u8>( const i64& variable )
{
	if( variable < 0 )
		return 0;
	else if( variable > U8_MAX )
		return U8_MAX;

	return (u8) variable;
}

template<>
inline u8 convert<u64, u8>( const u64& variable )
{
	if( variable > U8_MAX )
		return U8_MAX;

	return (u8) variable;
}

template<>
inline u8 convert<f32, u8>( const f32& variable )
{
	if( variable < 0.f )
		return 0;
	else if( variable > U8_MAX * 1.f )
		return U8_MAX;

	return (u8) variable;
}

template<>
inline u8 convert<f64, u8>( const f64& variable )
{
	if( variable < 0.0 )
		return 0;
	else if( variable > U8_MAX * 1.0 )
		return U8_MAX;

	return (u8) variable;
}


// SIGNED SHORT
template<>
inline i16 convert<b8, i16>( const b8& variable )
{
	return (variable) ? 1 : 0;
}

template<>
inline i16 convert<c8, i16>( const c8& variable )
{
	return (i16) variable;
}

template<>
inline i16 convert<i8, i16>( const i8& variable )
{
	return (i16) variable;
}

template<>
inline i16 convert<u8, i16>( const u8& variable )
{
	return (i16) variable;
}

template<>
inline i16 convert<u16, i16>( const u16& variable )
{
	if( variable > I16_MAX )
		return I16_MAX;

	return (i16) variable;
}

template<>
inline i16 convert<i32, i16>( const i32& variable )
{
	if( variable < 0 && variable < I16_MIN )
		return I16_MIN;
	else if( variable > 0 && variable > I16_MAX )
		return I16_MAX;

	return (i16) variable;
}

template<>
inline i16 convert<u32, i16>( const u32& variable )
{
	if( variable > 0 && variable > I16_MAX )
		return I16_MAX;

	return (i16) variable;
}

template<>
inline i16 convert<i64, i16>( const i64& variable )
{
	if( variable < 0 && variable < I16_MIN )
		return I16_MIN;
	else if( variable > 0 && variable > I16_MAX )
		return I16_MAX;

	return (i16) variable;
}

template<>
inline i16 convert<u64, i16>( const u64& variable )
{
	if( variable > 0 && variable > I16_MAX )
		return I16_MAX;

	return (i16) variable;
}

template<>
inline i16 convert<f32, i16>( const f32& variable )
{
	if( variable < 0.f && variable < I16_MIN * 1.f )
		return I16_MIN;
	else if( variable > 0.f && variable > I16_MAX * 1.f )
		return I16_MAX;

	return (i16) variable;
}

template<>
inline i16 convert<f64, i16>( const f64& variable )
{
	if( variable < 0.0 && variable < I16_MIN * 1.0 )
		return I16_MIN;
	else if( variable > 0.0 && variable > I16_MAX * 1.0 )
		return I16_MAX;

	return (i16) variable;
}

//UNSIGNED SHORT
template<>
inline u16 convert<b8, u16>( const b8& variable )
{
	return (variable) ? 1 : 0;
}

template<>
inline u16 convert<c8, u16>( const c8& variable )
{
	if( variable < 0 )
		return 0;

	return (u16) variable;
}

template<>
inline u16 convert<i8, u16>( const i8& variable )
{
	if( variable < 0 )
		return 0;

	return (u16) variable;
}

template<>
inline u16 convert<u8, u16>( const u8& variable )
{
	return (u16) variable;
}

template<>
inline u16 convert<i16, u16>( const i16& variable )
{
	if( variable < 0 )
		return 0;

	return (u16) variable;
}

template<>
inline u16 convert<i32, u16>( const i32& variable )
{
	if( variable < 0 )
		return 0;
	else if( variable > 0 && variable > U16_MAX )
		return U16_MAX;

	return (u16) variable;
}

template<>
inline u16 convert<u32, u16>( const u32& variable )
{
	if( variable > 0 && variable > U16_MAX )
		return U16_MAX;

	return (u16) variable;
}

template<>
inline u16 convert<i64, u16>( const i64& variable )
{
	if( variable < 0 )
		return 0;
	else if( variable > 0 && variable > U16_MAX )
		return U16_MAX;

	return (u16) variable;
}

template<>
inline u16 convert<u64, u16>( const u64& variable )
{
	if( variable > 0 && variable > U16_MAX )
		return U16_MAX;

	return (u16) variable;
}

template<>
inline u16 convert<f32, u16>( const f32& variable )
{
	if( variable < 0.f )
		return 0;
	else if( variable > 0 && variable > U16_MAX * 1.f )
		return U16_MAX;

	return (u16) variable;
}

template<>
inline u16 convert<f64, u16>( const f64& variable )
{
	if( variable < 0.0 )
		return 0;
	else if( variable > 0 && variable > U16_MAX * 1.0 )
		return U16_MAX;

	return (u16) variable;
}


//SIGNED INTEGER
template<>
inline i32 convert<b8, i32>( const b8& variable )
{
	return (variable) ? 1 : 0;
}

template<>
inline i32 convert<c8, i32>( const c8& variable )
{
	return (i32) variable;
}

template<>
inline i32 convert<i8, i32>( const i8& variable )
{
	return (i32) variable;
}

template<>
inline i32 convert<u8, i32>( const u8& variable )
{
	return (i32) variable;
}

template<>
inline i32 convert<i16, i32>( const i16& variable )
{
	return (i32) variable;
}

template<>
inline i32 convert<u16, i32>( const u16& variable )
{
	return (i32) variable;
}

template<>
inline i32 convert<u32, i32>( const u32& variable )
{
	if( variable > I32_MAX )
		return I32_MAX;
	return (i32) variable;
}

template<>
inline i32 convert<i64, i32>( const i64& variable )
{
	if( variable < 0 && variable < I32_MIN )
		return I32_MIN;
	else if( variable > 0 && variable > I32_MAX )
		return I32_MAX;

	return (i32) variable;
}

template<>
inline i32 convert<u64, i32>( const u64& variable )
{
	if( variable > I32_MAX )
		return I32_MAX;

	return (i32) variable;
}

template<>
inline i32 convert<f32, i32>( const f32& variable )
{
	if( variable < 0.f && variable < I32_MIN * 1.f )
		return I32_MIN;
	else if( variable > 0.f && variable > I32_MAX * 1.f )
		return I32_MAX;

	return (i32) variable;
}

template<>
inline i32 convert<f64, i32>( const f64& variable )
{
	if( variable < 0.0 && variable < I32_MIN * 1.0 )
		return I32_MIN;
	else if( variable > 0.0 && variable > I32_MAX * 1.0 )
		return I32_MAX;

	return (i32) variable;
}


//UNSIGNED INTEGER
template<>
inline u32 convert<b8, u32>( const b8& variable )
{
	return (variable) ? 1 : 0;
}

template<>
inline u32 convert<c8, u32>( const c8& variable )
{
	if( variable < 0 )
		return 0;

	return (u32) variable;
}

template<>
inline u32 convert<i8, u32>( const i8& variable )
{
	if( variable < 0 )
		return 0;

	return (u32) variable;
}

template<>
inline u32 convert<u8, u32>( const u8& variable )
{
	return (u32) variable;
}

template<>
inline u32 convert<i16, u32>( const i16& variable )
{
	if( variable < 0 )
		return 0;

	return (u32) variable;
}

template<>
inline u32 convert<u16, u32>( const u16& variable )
{
	return (u32) variable;
}

template<>
inline u32 convert<i32, u32>( const i32& variable )
{
	if( variable < 0 )
		return 0;

	return (u32) variable;
}

template<>
inline u32 convert<i64, u32>( const i64& variable )
{
	if( variable < 0 )
		return 0;
	else if( variable > 0 && variable > U32_MAX )
		return U32_MAX;

	return (u32) variable;
}

template<>
inline u32 convert<u64, u32>( const u64& variable )
{
	if( variable > 0 && variable > U32_MAX )
		return U32_MAX;

	return (u32) variable;
}

template<>
inline u32 convert<f32, u32>( const f32& variable )
{
	if( variable < 0.f )
		return 0;
	else if( variable > 0.f && variable > U32_MAX * 1.f )
		return U32_MAX;

	return (u32) variable;
}

template<>
inline u32 convert<f64, u32>( const f64& variable )
{
	if( variable < 0.0 )
		return 0;
	else if( variable > 0.0 && variable > U32_MAX * 1.0 )
		return U32_MAX;

	return (u32) variable;
}


//SINGED LONG (LONG)
template<>
inline i64 convert<b8, i64>( const b8& variable )
{
	return (variable) ? 1 : 0;
}


template<>
inline i64 convert<c8, i64>( const c8& variable )
{
	return (i64) variable;
}

template<>
inline i64 convert<i8, i64>( const i8& variable )
{
	return (i64) variable;
}

template<>
inline i64 convert<u8, i64>( const u8& variable )
{
	return (i64) variable;
}

template<>
inline i64 convert<i16, i64>( const i16& variable )
{
	return (i64) variable;
}

template<>
inline i64 convert<u16, i64>( const u16& variable )
{
	return (i64) variable;
}

template<>
inline i64 convert<i32, i64>( const i32& variable )
{
	return (i64) variable;
}

template<>
inline i64 convert<u32, i64>( const u32& variable )
{
	return (i64) variable;
}

template<>
inline i64 convert<u64, i64>( const u64& variable )
{
	if( variable > I64_MAX )
		return I64_MAX;

	return (i64) variable;
}

template<>
inline i64 convert<f32, i64>( const f32& variable )
{
	if( variable < 0.f && variable < I64_MIN * 1.f )
		return I64_MIN;
	else if( variable > 0.f && variable > I64_MAX * 1.f )
		return I64_MAX;

	return static_cast<i64>(variable);
}

template<>
inline i64 convert<f64, i64>( const f64& variable )
{
	if( variable < 0.0 && variable < I64_MIN * 1.0 )
		return I64_MIN;
	else if( variable > 0.0 && variable > I64_MAX * 1.0 )
		return I64_MAX;

	return (i64) variable;
}


//UNSIGNED LONG (LONG)
template<>
inline u64 convert<b8, u64>( const b8& variable )
{
	return (variable) ? 1 : 0;
}

template<>
inline u64 convert<c8, u64>( const c8& variable )
{
	if( variable < 0 )
		return 0;

	return (u64) variable;
}

template<>
inline u64 convert<i8, u64>( const i8& variable )
{
	if( variable < 0 )
		return 0;

	return (u64) variable;
}

template<>
inline u64 convert<u8, u64>( const u8& variable )
{
	return (u64) variable;
}

template<>
inline u64 convert<i16, u64>( const i16& variable )
{
	if( variable < 0 )
		return 0;

	return (u64) variable;
}

template<>
inline u64 convert<u16, u64>( const u16& variable )
{
	return (u64) variable;
}

template<>
inline u64 convert<i32, u64>( const i32& variable )
{
	if( variable < 0 )
		return 0;

	return (u64) variable;
}

template<>
inline u64 convert<u32, u64>( const u32& variable )
{
	return (u64) variable;
}

template<>
inline u64 convert<i64, u64>( const i64& variable )
{
	if( variable < 0 )
		return 0;

	return (u64) variable;
}

template<>
inline u64 convert<f32, u64>( const f32& variable )
{
	if( variable < 0.f )
		return 0;
	else if( variable > 0.f && variable > U64_MAX * 1.f )
		return U64_MAX;

	return (u64) variable;
}

template<>
inline u64 convert<f64, u64>( const f64& variable )
{
	if( variable < 0.0 )
		return 0;
	else if( variable > 0.0 && variable > U64_MAX * 1.0 )
		return U64_MAX;

	return (u64) variable;
}


//FLOAT
template<>
inline f32 convert<b8, f32>( const b8& variable )
{
	return (variable) ? 1.f : 0.f;
}

template<>
inline f32 convert<c8, f32>( const c8& variable )
{
	return (f32) variable;
}

template<>
inline f32 convert<i8, f32>( const i8& variable )
{
	return (f32) variable;
}

template<>
inline f32 convert<u8, f32>( const u8& variable )
{
	return (f32) variable;
}

template<>
inline f32 convert<i16, f32>( const i16& variable )
{
	return (f32) variable;
}

template<>
inline f32 convert<u16, f32>( const u16& variable )
{
	return (f32) variable;
}

template<>
inline f32 convert<i32, f32>( const i32& variable )
{
	return (f32) variable;
}

template<>
inline f32 convert<u32, f32>( const u32& variable )
{
	return (f32) variable;
}

template<>
inline f32 convert<i64, f32>( const i64& variable )
{
	if( variable < 0 && variable * 1.f < F32_MIN )
		return F32_MIN;
	else if( variable > 0 && variable * 1.f > F32_MAX )
		return F32_MAX;

	return (f32) variable;
}

template<>
inline f32 convert<u64, f32>( const u64& variable )
{
	if( variable == 0 )
		return 0.f;
	else if( variable > 0 && variable * 1.f > F32_MAX )
		return F32_MAX;

	return (f32) variable;
}

template<>
inline f32 convert<f64, f32>( const f64& variable )
{
	if( variable < 0.0 && variable < F32_MIN )
		return F32_MIN;
	else if( variable > 0.0 && variable > F32_MAX * 1.0 )
		return F32_MAX;

	return static_cast<f32>(variable);
}


// DOUBLE
template<>
inline f64 convert<b8, f64>( const b8& variable )
{
	return (variable) ? 1.0 : 0.0;
}

template<>
inline f64 convert<c8, f64>( const c8& variable )
{
	return (f64) variable;
}

template<>
inline f64 convert<i8, f64>( const i8& variable )
{
	return (f64) variable;
}

template<>
inline f64 convert<u8, f64>( const u8& variable )
{
	return (f64) variable;
}

template<>
inline f64 convert<i16, f64>( const i16& variable )
{
	return (f64) variable;
}

template<>
inline f64 convert<i64, f64>( const i64& variable )
{
	return static_cast<f64>( variable );
}

template<>
inline f64 convert<u64, f64>( const u64& variable )
{
	return static_cast<f64>( variable );
}

template<>
inline crap::static_string<64> convert<i8, crap::static_string<64> >( const i8& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%" PRIi8, variable);
	return crap::static_string<64>( buffer );
}

template<>
inline crap::static_string<64> convert<u8, crap::static_string<64> >( const u8& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%" PRIu8, variable);
	return crap::static_string<64>( buffer);
}

template<>
inline crap::static_string<64> convert<i16, crap::static_string<64> >( const i16& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%" PRIi16, variable);
	return crap::static_string<64>( buffer);
}

template<>
inline crap::static_string<64> convert<u16, crap::static_string<64> >( const u16& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%" PRIu16, variable);
	return crap::static_string<64>( buffer);
}

template<>
inline crap::static_string<64> convert<i32, crap::static_string<64> >( const i32& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%" PRIi32, variable);
	return crap::static_string<64>( buffer);
}

template<>
inline crap::static_string<64> convert<u32, crap::static_string<64> >( const u32& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%" PRIu32, variable);
	return crap::static_string<64>( buffer);
}

template<>
inline crap::static_string<64> convert<f32, crap::static_string<64> >( const f32& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%f", variable);
	return crap::static_string<64>( buffer);
}

template<>
inline crap::static_string<64> convert<i64, crap::static_string<64> >( const i64& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%" PRIi64, variable);
	return crap::static_string<64>( buffer);
}

template<>
inline crap::static_string<64> convert<u64, crap::static_string<64> >( const u64& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%" PRIu64, variable);
	return crap::static_string<64>( buffer );
}

template<>
inline crap::static_string<64> convert<f64, crap::static_string<64> >( const f64& variable )
{
	c8 buffer[64];
	sprintf(buffer, "%lf", variable);
	return crap::static_string<64>( buffer);
}

template<>
inline i8 convert< crap::static_string<64>, i8 >( const crap::static_string<64>& variable )
{
	i8 buffer;
	sscanf(&variable[0], "%" SCNi8, &buffer);
	return buffer;
}

template<>
inline u8 convert< crap::static_string<64>, u8 >( const crap::static_string<64>& variable )
{
	u8 buffer;
	sscanf(&variable[0], "%"SCNu8, &buffer);
	return buffer;
}

template<>
inline i16 convert< crap::static_string<64>, i16 >( const crap::static_string<64>& variable )
{
	i16 buffer;
	sscanf(&variable[0], "%" SCNi16, &buffer);
	return buffer;
}

template<>
inline u16 convert< crap::static_string<64>, u16 >( const crap::static_string<64>& variable )
{
	u16 buffer;
	sscanf(&variable[0], "%" SCNu16, &buffer);
	return buffer;
}

template<>
inline i32 convert< crap::static_string<64>, i32 >( const crap::static_string<64>& variable )
{
	i32 buffer;
	sscanf(&variable[0], "%" SCNi32, &buffer);
	return buffer;
}

template<>
inline u32 convert< crap::static_string<64>, u32 >( const crap::static_string<64>& variable )
{
	u32 buffer;
	sscanf(&variable[0], "%" SCNu32, &buffer);
	return buffer;
}

template<>
inline f32 convert< crap::static_string<64>, f32 >( const crap::static_string<64>& variable )
{
	f32 buffer;
	sscanf(&variable[0], "%f", &buffer);
	return buffer;
}

template<>
inline i64 convert< crap::static_string<64>, i64 >( const crap::static_string<64>& variable )
{
	i64 buffer;
	sscanf(&variable[0], "%" SCNi64, &buffer);
	return buffer;
}

template<>
inline u64 convert< crap::static_string<64>, u64 >( const crap::static_string<64>& variable )
{
	u64 buffer;
	sscanf(&variable[0], "%" SCNu64, &buffer);
	return buffer;
}

template<>
inline f64 convert< crap::static_string<64>, f64 >( const crap::static_string<64>& variable )
{
	f64 buffer;
	sscanf(&variable[0], "%lf", &buffer);
	return buffer;
}


}	// namespace crap

#endif // CRAP_CONTROL_CONVERTER_H
