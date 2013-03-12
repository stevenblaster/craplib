////////////////////////////////////////////////////////
// CRAP Library
//!		@file bitmask.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief The container receives a certain
//		memory address and allows bit manipulation
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "container/bitmask.h"

//lib namespace
namespace crap
{


/*
 * definitions
 */

//constructor
bit_mask::bit_mask( void ) : _pointer( 0 ), _bits( 0 ), _bytes( 0 )
{

}

//constructor using parameters
bit_mask::bit_mask( void* pointer , size_t32 size) : _pointer( pointer ), _bits( size ), _bytes( size/8 )
{
	_bytes += ( size % 8 != 0 ) ? 1 : 0;
}

//copy constructor
bit_mask::bit_mask( const bit_mask& other )
{
	_pointer = other._pointer;
	_bits = other._bits;
	_bytes = other._bytes;
}

//destructor
bit_mask::~bit_mask()
{
}

//init bitmask
void bit_mask::init( void* pointer , size_t32 size)
{
	_pointer = pointer;
	_bits = size;
	_bytes = size/8;
	_bytes += ( size % 8 != 0 ) ? 1 : 0;
}

//assigment operator
bit_mask& bit_mask::operator=( const bit_mask& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");

	size_t32 bytes = ( _bytes < other._bytes ) ? _bytes : other._bytes;
	memcpy( _pointer, other._pointer, bytes );
	return *this;
}

//assigment operator
bit_mask& bit_mask::operator=( void* other )
{
	CRAP_ASSERT_DEBUG(this != other, "Assignment operator on same object");

	memcpy( _pointer, other, _bytes );
	return *this;
}

//plus-equal operator
bit_mask& bit_mask::operator+=( const bit_mask& other )
{
	size_t32 bytes = ( _bytes < other._bytes ) ? _bytes : other._bytes;

	for( size_t32 i=0; i<bytes; ++i )
	{
		static_cast<u8*>(_pointer)[i] |= static_cast<u8*>(other._pointer)[i];
	}
	return *this;
}

//plus-equal operator
bit_mask& bit_mask::operator+=( void* other )
{
	for( size_t32 i=0; i<_bytes; ++i )
	{
		static_cast<u8*>(_pointer)[i] |= static_cast<u8*>(other)[i];
	}
	return *this;
}

//minus-equal operator
bit_mask& bit_mask::operator-=( const bit_mask& other )
{
	size_t32 bytes = ( _bytes < other._bytes ) ? _bytes : other._bytes;

	for( size_t32 i=0; i<bytes; ++i )
	{
		static_cast<u8*>(_pointer)[i] &= ~(static_cast<u8*>(other._pointer)[i]);
	}
	return *this;
}

//minus-equal operator
bit_mask& bit_mask::operator-=( void* other )
{
	for( size_t32 i=0; i<_bytes; ++i )
	{
		static_cast<u8*>(_pointer)[i] &= ~(static_cast<u8*>(other)[i]);
	}
	return *this;
}

//comparision operator
bool bit_mask::operator==( const bit_mask& other ) const
{
	if( _bits != other._bits )
		return false;

	return memcmp(_pointer, other._pointer, _bytes) == 0;
}

//comparision operator
bool bit_mask::operator==( void* other ) const
{
	return memcmp(_pointer, other, _bytes) == 0;
}

//index operator
bool bit_mask::operator[]( size_t32 position ) const
{
	return test( position );
}

//test
bool bit_mask::test( void ) const
{
	for( size_t32 i=0; i<_bits; ++i )
	{
		if( !test(i) )
			return false;
	}
	return true;
}

//test
bool bit_mask::test( size_t32 position ) const
{
	CRAP_ASSERT_DEBUG( position<_bits, "Position higher then size" );
	return static_cast<u8*>(_pointer)[ position / 8 ] & (1 << (position % 8));
}

bool bit_mask::test( size_t32 position, size_t32 lenght ) const
{
	CRAP_ASSERT_DEBUG( position+lenght <= _bits, "Position higher then size" );
	for( size_t32 i=position; i<position+lenght; ++i )
	{
		if( !test(i) )
			return false;
	}
	return true;
}

//set
void bit_mask::set( void )
{
	for( size_t32 i=0; i<_bits; ++i )
	{
		set(i);
	}
}

//set
void bit_mask::set( size_t32 position )
{
	CRAP_ASSERT_DEBUG( position<_bits, "Position higher then size" );
	static_cast<u8*>(_pointer)[ position/8 ] |= (1 << (position % 8));
}

//set
void bit_mask::set( size_t32 position, size_t32 lenght )
{
	CRAP_ASSERT_DEBUG( position+lenght <= _bits, "Position higher then size" );
	for( size_t32 i=position; i<position+lenght; ++i )
	{
		set(i);
	}
}

//reset
void bit_mask::reset( void )
{
	for( size_t32 i=0; i<_bits; ++i )
	{
		reset(i);
	}
}

//reset
void bit_mask::reset( size_t32 position )
{
	CRAP_ASSERT_DEBUG( position<_bits, "Position higher then size" );
	static_cast<u8*>(_pointer)[ position/8 ] &= ~(1 << (position % 8));
}

//reset
void bit_mask::reset( size_t32 position, size_t32 lenght )
{
	CRAP_ASSERT_DEBUG( position+lenght <= _bits, "Position higher then size" );
	for( size_t32 i=position; i<position+lenght; ++i )
	{
		reset(i);
	}
}

//flip
void bit_mask::flip( void )
{
	for( size_t32 i=0; i<_bits; ++i )
	{
		flip(i);
	}
}

//flip
void bit_mask::flip( size_t32 position )
{
	CRAP_ASSERT_DEBUG( position<_bits, "Position higher then size" );
	static_cast<u8*>(_pointer)[ position/8 ] ^= (1 << (position % 8));
}

//flip
void bit_mask::flip( size_t32 position, size_t32 lenght )
{
	CRAP_ASSERT_DEBUG( position+lenght <= _bits, "Position higher then size" );
	for( size_t32 i=position; i<position+lenght; ++i )
	{
		flip(i);
	}
}

//find_set
i32 bit_mask::find_set( size_t32 position /*=0*/ ) const
{
	for( size_t32 i=position; i<_bits; ++i )
	{
		if( test(i) )
			return i;
	}
	return -1;
}

//find_set
i32 bit_mask::find_set( size_t32 position, size_t32 lenght ) const
{
	CRAP_ASSERT_DEBUG( position+lenght <= _bits, "Position higher then size" );
	for( size_t32 i=position; i<position+lenght; ++i )
	{
		if( test(i) )
			return i;
	}
	return -1;
}

//find_unset
i32 bit_mask::find_unset( size_t32 position /*=0*/ ) const
{
	for( size_t32 i=position; i<_bits; ++i )
	{
		if( !test(i) )
			return i;
	}
	return -1;
}

//find_unset
i32 bit_mask::find_unset( size_t32 position, size_t32 lenght ) const
{
	CRAP_ASSERT_DEBUG( position+lenght <= _bits, "Position higher then size" );
	for( size_t32 i=position; i<position+lenght; ++i )
	{
		if( !test(i) )
			return i;
	}
	return -1;
}

//pointer
void* bit_mask::pointer( void ) const
{
	return _pointer;
}

//size
size_t32 bit_mask::size( void ) const
{
	return _bits;
}

//used_bytes
size_t32 bit_mask::used_bytes( void ) const
{
	return _bytes;
}

//operator<<
std::ostream& operator<<( std::ostream& out, const bit_mask& bitmask )
{
	for( size_t32 i=0; i<bitmask._bits; ++i )
	{
		out << bitmask.test(i);
	}
	return out;
}

}
