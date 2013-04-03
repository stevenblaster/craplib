////////////////////////////////////////////////////////
//	CRAP Library
//!		@file fixedstring.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Fixed size string class
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTAINER_FIXEDSTRING_H
#define CRAP_CONTAINER_FIXEDSTRING_H

#include <cstdarg>

#include "control/asserts.h"
#include "container/vector.h"

//lib namespace
namespace crap
{

template<size_t32 S>
class fixed_string
{

private:
	c8 _memory[S];

public:
	explicit fixed_string( void );
	fixed_string( const fixed_string& other );
	fixed_string( string_t* format, ... );

	fixed_string& operator=( const fixed_string& other );
	fixed_string& operator=( string_t* cstr );

	fixed_string& operator+=( const fixed_string& other );
	fixed_string& operator+=( string_t* cstr );

	fixed_string operator+( const fixed_string& other );
	fixed_string operator+( string_t* cstr );

	bool operator==( const fixed_string& other ) const;
	bool operator==( string_t* cstr ) const;

	bool operator!=( const fixed_string& other ) const;
	bool operator!=( string_t* cstr ) const;

	c8& operator[]( size_t32 index );
	const c8& operator[]( size_t32 index ) const;

	template<size_t32 U>
	friend std::ostream& operator<<( std::ostream& theStream, const fixed_string<U>& theString );

	void concat( const fixed_string& other );
	void concat( string_t* cstr );

	bool compare( const fixed_string& other ) const;
	bool compare( string_t* cstr ) const;

	bool contains( const fixed_string& other );
	bool contains( string_t* cstr );
	bool contains( const c8& other );

	i32 search( const fixed_string<S>& other );
	i32 search( string_t* cstr );
	i32 search( const c8& other );

	fixed_string substr( size_t32 start, size_t32 length );

	crap::vector<fixed_string<S> > split( c8 seperator ) const;

	void merge( const crap::vector<fixed_string<S> >&, c8 glue );

	void cut( size_t32 length );
	void trim( void );

	string_t* cstring( void ) const;
	size_t32 size( void ) const;
};


template<size_t32 S>
fixed_string<S>::fixed_string()
{
	memset( _memory, 0, S);
}

template<size_t32 S>
fixed_string<S>::fixed_string( const fixed_string<S>& other )
{
	memcpy( _memory, other._memory, S);
}

template<size_t32 S>
fixed_string<S>::fixed_string( string_t* format, ... )
{
	CRAP_ASSERT_DEBUG( strlen(format)<S, "string_t is too long" );
	memset( _memory, 0, S);

	va_list args;
	va_start( args, format );
	vsprintf( _memory, format, args );
	va_end( args );
}

template<size_t32 S>
fixed_string<S>& fixed_string<S>::operator=( const fixed_string<S>& other )
{
	memcpy( _memory, other._memory, S );
	return *this;
}

template<size_t32 S>
fixed_string<S>& fixed_string<S>::operator=( string_t* cstr )
{
	CRAP_ASSERT_DEBUG(strlen(cstr)<S, "string_t is too long");

	memset( _memory, 0, S);
	memcpy( _memory, cstr, strlen(cstr) );
	return *this;
}

template<size_t32 S>
fixed_string<S>& fixed_string<S>::operator+=( const fixed_string<S>& other )
{
	concat(other);
	return *this;
}

template<size_t32 S>
fixed_string<S>& fixed_string<S>::operator+=( string_t* cstr )
{
	concat(cstr);
	return *this;
}

template<size_t32 S>
fixed_string<S> fixed_string<S>::operator+( const fixed_string& other )
{
	fixed_string<S> tmp = *this;
	tmp += other;
	return tmp;
}

template<size_t32 S>
fixed_string<S> fixed_string<S>::operator+( string_t* cstr )
{
	fixed_string<S> tmp = *this;
	tmp += cstr;
	return tmp;
}


template<size_t32 S>
bool fixed_string<S>::operator==( const fixed_string<S>& other ) const
{
	return compare(other);
}

template<size_t32 S>
bool fixed_string<S>::operator==( string_t* cstr) const
{
	return compare(cstr);
}

template<size_t32 S>
bool fixed_string<S>::operator!=( const fixed_string<S>& other ) const
{
	return !compare(other);
}

template<size_t32 S>
bool fixed_string<S>::operator!=( string_t* cstr) const
{
	return !compare(cstr);
}

template<size_t32 S>
c8& fixed_string<S>::operator[](size_t32 index)
{
	CRAP_ASSERT_DEBUG(index<S, "Index is bigger than size");
	return _memory[index];
}

template<size_t32 S>
const c8& fixed_string<S>::operator[](size_t32 index) const
{
	CRAP_ASSERT_DEBUG(index<S, "Index is bigger than size");
	return _memory[index];
}

template<size_t32 U>
std::ostream& operator<<(std::ostream& theStream, const crap::fixed_string<U>& theStaticString)
{
	theStream << &theStaticString[0];
	return theStream;
}

template<size_t32 S>
void fixed_string<S>::concat( const fixed_string<S>& other )
{
	size_t32 otherLength = strlen( reinterpret_cast<string_t*>(other._memory) );
	size_t32 myLength = strlen( reinterpret_cast<string_t*>(_memory) );

	CRAP_ASSERT_DEBUG(otherLength+myLength < S, "Concating would overflow fixed_string size");

	memcpy(_memory + myLength, other._memory, otherLength);
}

template<size_t32 S>
void fixed_string<S>::concat( string_t* cstr )
{
	size_t32 otherLength = (size_t32) strlen( cstr );
	size_t32 myLength = (size_t32) strlen( reinterpret_cast<string_t*>(_memory) );

	CRAP_ASSERT_DEBUG(otherLength+myLength < S, "Concating would overflow fixed_string size");

	memcpy( _memory + myLength, cstr, otherLength );
}

template<size_t32 S>
bool fixed_string<S>::compare( const fixed_string<S>& other ) const
{
	if( strlen( reinterpret_cast<string_t*>(_memory)) != strlen( reinterpret_cast<string_t*>(other._memory) ))
		return false;

	return memcmp( _memory, other._memory, strlen( reinterpret_cast<string_t*>(_memory) ) ) == 0;
}

template<size_t32 S>
bool fixed_string<S>::compare( string_t* cstr ) const
{
	if( strlen( _memory ) != strlen( cstr ) )
		return false;

	return memcmp( _memory, cstr, strlen( _memory ) ) == 0;
}

template<size_t32 S>
bool fixed_string<S>::contains( const fixed_string<S>& other )
{
	return search(other) != -1;
}

template<size_t32 S>
bool fixed_string<S>::contains( string_t* cstr )
{
	return search(cstr) != -1;
}

template<size_t32 S>
bool fixed_string<S>::contains( const c8& other )
{
	return search(other) != -1;
}

template<size_t32 S>
i32 fixed_string<S>::search( const fixed_string<S>& other )
{
	size_t32 otherSize = strlen(reinterpret_cast<string_t*>(other._memory));
	size_t32 mySize = strlen(reinterpret_cast<string_t*>(_memory));

	if(mySize < otherSize)
		return -1;

	for( size_t32 i=0; i <= (mySize - otherSize); ++i )
	{
		if( memcmp( &_memory[i], other._memory, otherSize ) == 0 )
			return i;
	}
	return -1;
}

template<size_t32 S>
i32 fixed_string<S>::search( string_t* cstr )
{
	size_t32 otherSize = (size_t32) strlen( cstr );
	size_t32 mySize = (size_t32) strlen( reinterpret_cast<string_t*>(_memory) );

	if( mySize < otherSize )
		return -1;

	for( size_t32 i=0; i <= (mySize - otherSize); ++i )
	{
		if(memcmp(&_memory[i], cstr, otherSize) == 0)
			return i;
	}
	return -1;
}

template<size_t32 S>
i32 fixed_string<S>::search( const c8& other )
{
	for( size_t32 i=0; i < S; ++i )
	{
		if(_memory[i] == other)
			return i;
	}
	return -1;
}

template<size_t32 S>
fixed_string<S> fixed_string<S>::substr( size_t32 start, size_t32 length )
{
	CRAP_ASSERT_DEBUG(start+length < S, "Substring is bigger than parent string");

	fixed_string<S> buffer;
	memcpy(&buffer._memory[0], &_memory[start], length);
	return buffer;
}

template<size_t32 S>
crap::vector<fixed_string<S> > fixed_string<S>::split( c8 seperator ) const
{
	crap::vector<fixed_string<S> > tmp_list;
	fixed_string<S> buffer;
	size_t32 buffer_size = 0;

	for( size_t32 i=0; i<S; ++i)
	{
		if( _memory[i] == seperator && buffer_size != 0)
		{
//        	std::cout << buffer << std::endl;
			tmp_list.push_back( buffer );
			memset( buffer._memory, 0, S);
			buffer_size = 0;
		}
		else
		{
			buffer[ buffer_size++ ] = _memory[i];
		}
	}

	if( buffer_size != 0 )
		tmp_list.push_back(buffer);

	return tmp_list;
}

template<size_t32 S>
void fixed_string<S>::merge( const crap::vector<fixed_string>& list, c8 glue )
{
	size_t32 current_pos = 0;

	for(size_t32 i=0; i<list.size(); ++i)
	{
		if(current_pos != 0)
			_memory[current_pos++] = glue;

		memcpy(&_memory[current_pos], &(list[i])[0], strlen( &(list[i])[0] ));
		current_pos += strlen(&(list[i])[0]);
	}
}

template<size_t32 S>
void fixed_string<S>::cut(size_t32 length)
{
	CRAP_ASSERT_DEBUG(length < S, "Cut length is bigger than size");
	memset(&_memory[length], 0, S-length);
}

template<size_t32 S>
void fixed_string<S>::trim()
{
	size_t32 startPos = 0;
	size_t32 endPos = strlen(reinterpret_cast<string_t*>( &_memory[0] ));

	for(size_t32 i=0; i<endPos; ++i)
	{
		startPos = i;
		if( _memory[i] != ' ')
		{
			break;
		}
	}

	for(size_t32 i=endPos; i>0; --i)
	{
		endPos = i;
		if( _memory[i] != ' ' && _memory[i] != 0)
		{
			break;
		}
	}

	size_t32 stringSize = endPos-startPos;

	if(startPos != 0)
	{
		memmove(&_memory[0], &_memory[startPos], stringSize);
	}

	if(endPos != S)
	{
		memset(&_memory[stringSize], 0, S-endPos);
	}
}

template<size_t32 S>
string_t* fixed_string<S>::cstring( void ) const
{
	return reinterpret_cast<string_t*>(&_memory[0]);
}

template<size_t32 S>
size_t32 fixed_string<S>::size() const
{
	return strlen(reinterpret_cast<string_t*>(&_memory[0]));
}

//typedefs
typedef fixed_string<8> string8;
typedef fixed_string<16> string16;
typedef fixed_string<32> string32;
typedef fixed_string<64> string64;
typedef fixed_string<128> string128;
typedef fixed_string<256> string256;
typedef fixed_string<512> string512;
typedef fixed_string<1024> string1024;

}	// namespace crap

#endif // CRAP_CONTAINER_STATICSTRING_H
