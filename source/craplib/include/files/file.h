////////////////////////////////////////////////////////
// CRAP Library
//!		@file file.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief c file wrap
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_FILES_FILE_H
#define CRAP_FILES_FILE_H

#include <cstdio>
#include "container/fixedstring.h"

//lib namespace
namespace crap
{

//typdefs
typedef FILE* file_t;

/*
 * class stuff
 */

class file
{
public:
	enum mode
	{
		closed = 0,
		read,
		write,
		append,
		read_binary,
		write_binary,
		append_binary
	};

private:
	file_t _handle;
	string256 _filename;
	mode _state;

public:
	file( void );
	file( const string256& filename );
	file( const file& other );
	~file( void );

	void set_filename( const string256& filename );
	const string256& get_filename( void ) const;

	bool readable( void );
	bool writeable( void );

	void open( mode value );
	mode state( void );
	void close( void );

	void set_byte_position( i32 byte_position = -1 );

	template<typename T>
	void read_bytes( T* buffer, size_t32 bytes, bool byte_wise = false, i32 byte_position = -1 );

	template<typename T>
	void write_bytes( const T* buffer, size_t32 bytes, bool byte_wise = false, i32 byte_position = -1 );

	template<typename T>
	void append_bytes( const T* buffer, size_t32 bytes, bool byte_wise = false);

	template<size_t32 S>
	void read_text( fixed_string<S>& str, size_t32 size, i32 char_position = -1 );

	template<size_t32 S>
	void write_text( const fixed_string<S>& str, i32 char_position = -1 );

	template<size_t32 S>
	void append_text( const fixed_string<S>& str );

	size_t64 size( void );
};

template<typename T>
void file::read_bytes( T* buffer, size_t32 bytes, bool byte_wise /* = false */, i32 byte_position /* = -1 */ )
{
    mode previous_state = _state;
    if(_state != read_binary )
    {
        close();
        open(read_binary);
    }

    set_byte_position(byte_position);

    void* ptr = (void*) buffer;
    size_t32 result = 0;

    if( byte_wise )
    {
        result = (size_t32) fread( ptr, 1, bytes, _handle );
        CRAP_ASSERT_DEBUG(result == sizeof(buffer), "Reading bytes was not successful (bytewise)");
    }
    else
    {
        result = (size_t32) fread( ptr, bytes, 1, _handle );
        CRAP_ASSERT_DEBUG(result == 1, "Reading bytes was not successful (not bytewise)");
    }

    if(previous_state != read_binary )
    {
        close();
        open(previous_state);
    }
}

template<typename T>
void file::write_bytes( const T* buffer, size_t32 bytes, bool byte_wise /* = false */, i32 byte_position /* = -1 */ )
{
    mode previous_state = _state;
    if(_state != write_binary )
    {
        close();
        open(write_binary);
    }

    set_byte_position(byte_position);

    void* ptr = (void*) buffer;
    size_t32 result = 0;

    if( byte_wise )
    {
        result = (size_t32) fwrite( ptr, 1, bytes, _handle );
        CRAP_ASSERT_DEBUG(result == bytes, "Reading bytes was not successful (bytewise)");
    }
    else
    {
        result = (size_t32) fwrite( ptr, bytes, 1, _handle );
        CRAP_ASSERT_DEBUG(result == 1, "Reading bytes was not successful (not bytewise)");
    }

    if(previous_state != write_binary )
    {
        close();
        open(previous_state);
    }
    else
        fflush(_handle);
}

template<typename T>
void file::append_bytes( const T* buffer, size_t32 bytes, bool byte_wise /* = false */ )
{
    mode previous_state = _state;
    if(_state != append_binary )
    {
        close();
        open(append_binary);
    }

    void* ptr = (void*) buffer;
    size_t32 result = 0;

    if( byte_wise )
    {
        result = (size_t32) fwrite( ptr, 1, bytes, _handle );
        CRAP_ASSERT_DEBUG(result == bytes, "Reading bytes was not successful (bytewise)");
    }
    else
    {
        result = (size_t32) fwrite( ptr, bytes, 1, _handle );
        CRAP_ASSERT_DEBUG(result == 1, "Reading bytes was not successful (not bytewise)");
    }

    if(previous_state != append_binary )
    {
        close();
        open(previous_state);
    }
    else
        fflush(_handle);
}

template<size_t32 S>
void file::read_text( fixed_string<S>& str, size_t32 size, i32 char_position /*= -1*/ )
{
    CRAP_ASSERT_DEBUG(size <= S, "Size bigger then buffer");

    mode previous_state = _state;
    if(_state != read )
    {
        close();
        open(read);
    }

    set_byte_position(char_position);
	char buffer[1024];

	while( fgets(buffer, 1024, _handle) != 0 ) 
		str += buffer;
    //char* result = fgets( const_cast<char*>(str.cstring()) , size , _handle);

    //CRAP_ASSERT_DEBUG(result == 1, "Could not get string");

    if(previous_state != read )
    {
        close();
        open(previous_state);
    }
    else
        fflush(_handle);
}

template<size_t32 S>
void file::write_text( const fixed_string<S>& str, i32 char_position /*= -1*/ )
{
    mode previous_state = _state;
    if(_state != write )
    {
        close();
        open(write);
    }

    set_byte_position(char_position);

    int result = fputs(str.cstring(), _handle);
    CRAP_ASSERT_DEBUG(result >= 0, "Could not put string");

    if(previous_state != write )
    {
        close();
        open(previous_state);
    }
    else
        fflush(_handle);
}

template<size_t32 S>
void file::append_text( const fixed_string<S>& str )
{
    mode previous_state = _state;
    if(_state != append )
    {
        close();
        open(append);
    }

    int result = fputs(str.cstring(), _handle);
    CRAP_ASSERT_DEBUG(result >= 0, "Could not append string");

    if(previous_state != append )
    {
        close();
        open(previous_state);
    }
    else
        fflush(_handle);
}

} //namespace crap

#endif // CRAP_FILES_FILE_H
