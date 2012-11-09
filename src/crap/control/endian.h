////////////////////////////////////////////////////////
//	CRAP Library
//		@file endian.h
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
//		@brief Contains the Endian class which cares about 
//		Ednian checking (in case the Macrocheck in 
//		endianness.h didn't identify the right endian 
//		case), and several methods of byte swapping and
//		endian conversions.
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_ENDIAN_H
#define CRAP_CONTROL_ENDIAN_H

#include "config/endianness.h"

//lib namespace
namespace crap
{

class Endian
{
	public:

		//enum as endian type
		enum ByteOrder
		{
			littleEndian = 0,
			bigEndian
		};

		//checking byte order, ignores macro settings
		static ByteOrder checkByteOrder( void );

		//returns either macro settings or, if unknown runs checByteOrder()
		inline static b8 isBigEndian( void );

		//returns either macro settings or, if unknown runs checByteOrder()
		inline static b8 isLittleEndian( void );

		//swaps any size of bytes
		//TODO: is a template necessary?
		template<u64 S>
		static void* swapBytes( void* swapMe );

		//uses compiler implemented swaps or the swapBytes() method
		//see spezialization a few lines below
		template<typename T>
		static T& swap( T& swapMe );

		//swaps bytes is system is little endian or simply returns value
		template<typename T>
		static T& toBigEndian( T& swapMe );

		//swaps bytes is system is big endian or simply returns value
		template<typename T>
		static T& toLittleEndian( T& swapMe );

		//swaps bytes is system is little endian or simply returns value
		template<typename T>
		static T& bigToLocalEndian( T& swapMe );

		//swaps bytes is system is big endian or simply returns value
		template<typename T>
		static T& littleToLocalEndian( T& swapMe );
};

//common method of checking byte order
 Endian::ByteOrder Endian::checkByteOrder( void )
{
	union
    {
    	u16 value;
    	u8 test[2];
    } data;

	data.test[0] = 1;
	data.test[1] = 0;

    return ( data.value == 1 ) ? littleEndian : bigEndian;
}

b8 Endian::isBigEndian( void )
{
#if defined(CRAP_ENDIAN_LITTLE)
	return false;
#elif defined(CRAP_ENDIAN_BIG)
	return true;
#else
	return Endian::checkByteOrder() == bigEndian;
#endif
}

b8 Endian::isLittleEndian( void )
{
#if defined(CRAP_ENDIAN_LITTLE)
	return true;
#elif defined(CRAP_ENDIAN_BIG)
	return false;
#else
	return Endian::checkByteOrder() == littleEndian;
#endif
}

template<u64 S>
void* Endian::swapBytes( void* swapMe )
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
T& Endian::swap( T& swapMe )
{
	return *((T*)swapBytes<sizeof(swapMe)>(&swapMe));
}

template<>
void* Endian::swapBytes<1>( void* swapMe )
{
	return swapMe;
}

template<>
void* Endian::swapBytes<2>( void* swapMe )
{
//#if defined(CRAP_COMPILER_VC)
//	return &_byteswap_ushort(*( ( u16* )swapMe ));
//#else // other platform
	u8* bytes = (u8*)swapMe;
	u8 tmp = bytes[0];
	bytes[0] = bytes[1];
	bytes[1] = tmp;
	return swapMe;
//#endif
}

template<>
void* Endian::swapBytes<4>( void* swapMe )
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
void* Endian::swapBytes<8>( void* swapMe )
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
T& Endian::toBigEndian( T& swapMe )
{
	if( Endian::isLittleEndian() )
		return swap<T>( swapMe );
	else
		return swapMe;
}

template<typename T>
T& Endian::toLittleEndian( T& swapMe )
{
	if( Endian::isBigEndian() )
		return swap<T>( swapMe );
	else
		return swapMe;
}

template<typename T>
T& Endian::bigToLocalEndian( T& swapMe )
{
	if( Endian::isLittleEndian() )
		return swap<T>( swapMe );
	else
		return swapMe;
}

template<typename T>
T& Endian::littleToLocalEndian( T& swapMe )
{
	if( Endian::isBigEndian() )
		return swap<T>( swapMe );
	else
		return swapMe;
}

}	// namespace crap

#endif // CRAP_CONTROL_ENDIAN_H
