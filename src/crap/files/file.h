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
#include "container/staticstring.h"

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
	void read_bytes( T& buffer, bool byte_wise = false, i32 byte_position = -1 );

	template<typename T>
	void write_bytes( const T& buffer, bool byte_wise = false, i32 byte_position = -1 );

	template<typename T>
	void append_bytes( const T& buffer, bool byte_wise = false);

	template<size_t32 S>
	void read_text( static_string<S>& str, size_t32 size, i32 char_position = -1 );

	template<size_t32 S>
	void write_text( const static_string<S>& str, i32 char_position = -1 );

	template<size_t32 S>
	void append_text( const static_string<S>& str );

	size_t64 size( void );
};

}

#endif // CRAP_FILES_FILE_H
