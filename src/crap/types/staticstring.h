////////////////////////////////////////////////////////
//	CRAP Library
//		@file staticrap::cstring.h
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
//		@brief Static string class
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_TYPES_STATICSTRING_H
#define CRAP_TYPES_STATICSTRING_H

#include <cstdarg>

#include "control/asserts.h"
#include "container/list.h"

//lib namespace
namespace crap
{

template<size_t32 S>
class static_string
{

private:
    c8 _memory[S];

public:
    explicit static_string( void );
    static_string( const static_string& other );
    static_string( crap::cstring* format, ... );

    static_string& operator=( const static_string& other );
    static_string& operator=( crap::cstring* cstr );

    static_string& operator+=( const static_string& other );
    static_string& operator+=( crap::cstring* cstr );

    bool operator==( const static_string& other ) const;
    bool operator==( crap::cstring* cstr ) const;

    bool operator!=( const static_string& other ) const;
    bool operator!=( crap::cstring* cstr ) const;

    c8& operator[]( size_t32 index );
    const c8& operator[]( size_t32 index ) const;

    template<size_t32 U>
    friend std::ostream& operator<<( std::ostream& theStream, const static_string<U>& theString );

    void concat( const static_string& other );
    void concat( crap::cstring* cstr );

    bool compare( const static_string& other ) const;
    bool compare( crap::cstring* cstr ) const;

    bool contains( const static_string& other );
    bool contains( crap::cstring* cstr );
    bool contains( const c8& other );

    i32 search( const static_string<S>& other );
    i32 search( crap::cstring* cstr );
    i32 search( const c8& other );

    static_string substr( size_t32 start, size_t32 length );

    crap::list<static_string<S> > split( c8 seperator ) const;

    void merge( const crap::list<static_string<S> >&, c8 glue );

    void cut( size_t32 length );
    void trim( void );

    size_t32 size( void ) const;
};


template<size_t32 S>
static_string<S>::static_string()
{
    memset( _memory, 0, S);
}

template<size_t32 S>
static_string<S>::static_string( const static_string<S>& other )
{
    memcpy( _memory, other._memory, S);
}

template<size_t32 S>
static_string<S>::static_string( crap::cstring* format, ... )
{
	CRAP_ASSERT_DEBUG( strlen(format)<S, "Cstring is too long" );
	memset( _memory, 0, S);

  	va_list args;
	va_start( args, format );
	vsprintf( _memory, format, args );
//	perror( _memory );
	va_end( args );
}

template<size_t32 S>
static_string<S>& static_string<S>::operator=( const static_string<S>& other )
{
    memcpy( _memory, other._memory, S );
    return *this;
}

template<size_t32 S>
static_string<S>& static_string<S>::operator=( crap::cstring* cstr )
{
    CRAP_ASSERT_DEBUG(strlen(cstr)<S, "Cstring is too long");

    memset( _memory, 0, S);
    memcpy( _memory, cstr, strlen(cstr) );
    return *this;
}

template<size_t32 S>
static_string<S>& static_string<S>::operator+=( const static_string<S>& other )
{
    concat(other);
    return *this;
}

template<size_t32 S>
static_string<S>& static_string<S>::operator+=( crap::cstring* cstr )
{
    concat(cstr);
    return *this;
}

template<size_t32 S>
bool static_string<S>::operator==( const static_string<S>& other ) const
{
    return compare(other);
}

template<size_t32 S>
bool static_string<S>::operator==( crap::cstring* cstr) const
{
    return compare(cstr);
}

template<size_t32 S>
bool static_string<S>::operator!=( const static_string<S>& other ) const
{
    return !compare(other);
}

template<size_t32 S>
bool static_string<S>::operator!=( crap::cstring* cstr) const
{
    return !compare(cstr);
}

template<size_t32 S>
c8& static_string<S>::operator[](size_t32 index)
{
    CRAP_ASSERT_DEBUG(index<S, "Index is bigger than size");
    return _memory[index];
}

template<size_t32 S>
const c8& static_string<S>::operator[](size_t32 index) const
{
    CRAP_ASSERT_DEBUG(index<S, "Index is bigger than size");
    return _memory[index];
}

template<size_t32 U>
std::ostream& operator<<(std::ostream& theStream, const crap::static_string<U>& theStaticString)
{
    theStream << &theStaticString[0];
    return theStream;
}

template<size_t32 S>
void static_string<S>::concat( const static_string<S>& other )
{
    size_t32 otherLength = strlen( reinterpret_cast<crap::cstring*>(other._memory) );
    size_t32 myLength = strlen( reinterpret_cast<crap::cstring*>(_memory) );

    CRAP_ASSERT_DEBUG(otherLength+myLength < S, "Concating would overflow static_string size");

    memcpy(_memory + myLength, other._memory, otherLength);
}

template<size_t32 S>
void static_string<S>::concat( crap::cstring* cstr )
{
    size_t32 otherLength = strlen( cstr );
    size_t32 myLength = strlen( reinterpret_cast<crap::cstring*>(_memory) );

    CRAP_ASSERT_DEBUG(otherLength+myLength < S, "Concating would overflow static_string size");

    memcpy( _memory + myLength, cstr, otherLength );
}

template<size_t32 S>
bool static_string<S>::compare( const static_string<S>& other ) const
{
    if( strlen( reinterpret_cast<crap::cstring*>(_memory)) != strlen( reinterpret_cast<crap::cstring*>(other._memory) ))
        return false;

	return memcmp( _memory, other._memory, strlen( reinterpret_cast<crap::cstring*>(_memory) ) ) == 0;
}

template<size_t32 S>
bool static_string<S>::compare( crap::cstring* cstr ) const
{
    if( strlen( _memory ) != strlen( cstr ) )
        return false;

	return memcmp( _memory, cstr, strlen( _memory ) ) == 0;
}

template<size_t32 S>
bool static_string<S>::contains( const static_string<S>& other )
{
    return search(other) != -1;
}

template<size_t32 S>
bool static_string<S>::contains( crap::cstring* cstr )
{
    return search(cstr) != -1;
}

template<size_t32 S>
bool static_string<S>::contains( const c8& other )
{
    return search(other) != -1;
}

template<size_t32 S>
i32 static_string<S>::search( const static_string<S>& other )
{
    size_t32 otherSize = strlen(reinterpret_cast<crap::cstring*>(other._memory));
    size_t32 mySize = strlen(reinterpret_cast<crap::cstring*>(_memory));

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
i32 static_string<S>::search( crap::cstring* cstr )
{
    size_t32 otherSize = strlen( cstr );
    size_t32 mySize = strlen( reinterpret_cast<crap::cstring*>(_memory) );

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
i32 static_string<S>::search( const c8& other )
{
    for( size_t32 i=0; i < S; ++i )
    {
        if(_memory[i] == other)
            return i;
    }
    return -1;
}

template<size_t32 S>
static_string<S> static_string<S>::substr( size_t32 start, size_t32 length )
{
    CRAP_ASSERT_DEBUG(start+length < S, "Substring is bigger than parent string");

    static_string<S> buffer;
    memcpy(&buffer._memory[0], &_memory[start], length);
    return buffer;
}

template<size_t32 S>
crap::list<static_string<S> > static_string<S>::split( c8 seperator ) const
{
    crap::list<static_string<S> > tmp_list;
    static_string<S> buffer;
    size_t32 buffer_size = 0;

    for( size_t32 i=0; i<S; ++i)
    {
        if( _memory[i] == seperator && buffer_size != 0)
        {
//        	std::cout << buffer << std::endl;
            tmp_list.insert( buffer );
            memset( buffer._memory, 0, S);
            buffer_size = 0;
        }
        else
        {
            buffer[ buffer_size++ ] = _memory[i];
        }
    }

    if( buffer_size != 0 )
        tmp_list.insert(buffer);

    return tmp_list;
}

template<size_t32 S>
void static_string<S>::merge( const crap::list<static_string>& list, c8 glue )
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
void static_string<S>::cut(size_t32 length)
{
    CRAP_ASSERT_DEBUG(length < S, "Cut length is bigger than size");
    memset(&_memory[length], 0, S-length);
}

template<size_t32 S>
void static_string<S>::trim()
{
    size_t32 startPos = 0;
    size_t32 endPos = strlen(reinterpret_cast<crap::cstring*>( &_memory[0] ));

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
size_t32 static_string<S>::size() const
{
    return strlen(reinterpret_cast<crap::cstring*>(&_memory[0]));
}

//typedefs
typedef static_string<8> string8;
typedef static_string<16> string16;
typedef static_string<32> string32;
typedef static_string<64> string64;
typedef static_string<128> string128;
typedef static_string<256> string256;
typedef static_string<512> string512;
typedef static_string<1024> string1024;

}	// namespace crap

#endif // CRAP_TYPES_STATICSTRING_H
