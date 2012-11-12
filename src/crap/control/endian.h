////////////////////////////////////////////////////////
//	CRAP Library
//!		@file endian.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Contains the Endian class which cares about
//		Ednian checking (in case the Macrocheck in
//		endianness.h didn't identify the right endian
//		case), and several methods of byte swapping and
//		endian conversions.
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_ENDIAN_H
#define CRAP_CONTROL_ENDIAN_H

#include "config/endianness.h"

//lib namespace
namespace crap
{

class endian
{
	public:

		//enum as endian type
		enum byte_order
		{
			little_endian = 0,
			big_endian
		};

		//checking byte order, ignores macro settings
		static byte_order check_endian( void );

		//returns either macro settings or, if unknown runs checByteOrder()
		inline static b8 is_big( void );

		//returns either macro settings or, if unknown runs checByteOrder()
		inline static b8 is_little( void );

		//swaps any size of bytes
		//TODO: is a template necessary?
		template<size_t32 S>
		static void* swap_bytes( void* swapMe );

		//uses compiler implemented swaps or the swapBytes() method
		//see spezialization a few lines below
		template<typename T>
		static T& swap( T& swapMe );

		//swaps bytes is system is little endian or simply returns value
		template<typename T>
		static T& to_big( T& swapMe );

		//swaps bytes is system is big endian or simply returns value
		template<typename T>
		static T& to_little( T& swapMe );

		//swaps bytes is system is little endian or simply returns value
		template<typename T>
		static T& big_to_local( T& swapMe );

		//swaps bytes is system is big endian or simply returns value
		template<typename T>
		static T& little_to_local( T& swapMe );
};

//common method of checking byte order
endian::byte_order endian::check_endian( void )
{
	union
	{
		u16 value;
		u8 test[2];
	} data;

	data.test[0] = 1;
	data.test[1] = 0;

	return ( data.value == 1 ) ? little_endian : big_endian;
}

bool endian::is_big( void )
{
#if defined(CRAP_ENDIAN_LITTLE)
	return false;
#elif defined(CRAP_ENDIAN_BIG)
	return true;
#else
	return endian::check_endian() == big_endian;
#endif
}

b8 endian::is_little( void )
{
#if defined(CRAP_ENDIAN_LITTLE)
	return true;
#elif defined(CRAP_ENDIAN_BIG)
	return false;
#else
	return endian::check_endian() == little_endian;
#endif
}

template<size_t32 S>
void* endian::swap_bytes( void* swapMe )
{
	u64 indexLow = 0;
	u64 indexHigh = S-1;
	u8* bytes = static_cast<u8*>( swapMe );

	while( indexLow < indexHigh )
	{
		u8 tmp = bytes[indexLow];
		bytes[indexLow] = bytes[indexHigh];
		bytes[indexHigh] = tmp;
		++indexLow;
		--indexHigh;
	}
	return swapMe;
}

template<typename T>
T& endian::swap( T& swapMe )
{
	return *((T*)swap_bytes<sizeof(swapMe)>((void*)&swapMe));
}

template<>
void* endian::swap_bytes<1>( void* swapMe )
{
	return swapMe;
}

template<>
void* endian::swap_bytes<2>( void* swapMe )
{
#if defined(CRAP_COMPILER_VC)
	u16& ref = *( ( u16* )swapMe );
	ref = _byteswap_ushort( ref );
	return &ref;
#else // other platform
	u8* bytes = (u8*)swapMe;
	u8 tmp = bytes[0];
	bytes[0] = bytes[1];
	bytes[1] = tmp;
	return swapMe;
#endif
}

template<>
void* endian::swap_bytes<4>( void* swapMe )
{
	u32& ref = *( ( u32* )swapMe );
#if defined(CRAP_COMPILER_VC)
	ref = _byteswap_ulong( ref );
#elif defined(CRAP_COMPILER_GCC)
	ref =  __builtin_bswap32( ref );
#else
	ref = swap<4>( ref );
#endif
	return &ref;
}

template<>
void* endian::swap_bytes<8>( void* swapMe )
{
	u64& ref = *( ( u64* )swapMe );
#if defined(CRAP_COMPILER_VC)
	ref = _byteswap_uint64( ref );
#elif defined(CRAP_COMPILER_GCC)
	ref = __builtin_bswap64 ( ref );
#else
	ref = swap<8>( ref );
#endif
	return &ref;
}

template<typename T>
T& endian::to_big( T& swapMe )
{
	if( endian::is_little() )
		return swap<T>( swapMe );
	else
		return swapMe;
}

template<typename T>
T& endian::to_little( T& swapMe )
{
	if( endian::is_big() )
		return swap<T>( swapMe );
	else
		return swapMe;
}

template<typename T>
T& endian::big_to_local( T& swapMe )
{
	if( endian::is_little() )
		return swap<T>( swapMe );
	else
		return swapMe;
}

template<typename T>
T& endian::little_to_local( T& swapMe )
{
	if( endian::is_big() )
		return swap<T>( swapMe );
	else
		return swapMe;
}

}	// namespace crap

#endif // CRAP_CONTROL_ENDIAN_H
