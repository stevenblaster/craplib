////////////////////////////////////////////////////////
// CRAP Library
//!		@file file.cpp
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>

#include "files/file.h"

//lib namespace
namespace crap
{

//constructor
file::file( void ) : _handle(0), _filename(), _state(closed)
{

}

//copy constructor
file::file( const file& other ) : _handle(other._handle), _filename(other._filename), _state(other._state)
{

}

//construcutor w. filename
file::file( const string256& name ) : _handle(0), _filename(name), _state(closed)
{

}

//destructor
file::~file( void )
{
    fclose(_handle);
}

//set filename
void file::set_filename( const string256& filename )
{
    _filename = filename;
}

//get filename
const string256& file::get_filename( void ) const
{
    return _filename;
}

bool file::readable( void )
{
    if( _state != closed )
        return true;

    _handle = fopen( _filename.cstring() ,"r");
    if(_handle == 0)
        return false;

    fclose(_handle);
    return true;
}

bool file::writeable( void )
{
    if( _state != closed && _state != read && _state != read_binary )
        return true;

    mode previous_state = _state;
    close();

    _handle = fopen( _filename.cstring() ,"w" );
    if(_handle == 0)
        return false;

    close();
    open(previous_state);
    return true;
}

void file::open( mode value )
{
    if( _state != closed )
        close();

    if(value == closed)
        return;
    else if(value == read)
        _handle = fopen( _filename.cstring() ,"r");
    else if(value == write)
        _handle = fopen( _filename.cstring() ,"w");
    else if(value == append)
        _handle = fopen( _filename.cstring() ,"a");
    else if(value == read_binary)
        _handle = fopen( _filename.cstring() ,"rb");
    else if(value == write_binary)
        _handle = fopen( _filename.cstring() ,"wb");
    else if(value == append_binary)
        _handle = fopen( _filename.cstring() ,"ab");

    _state = value;
}

file::mode file::state( void )
{
    return _state;
}

void file::close( void )
{
    if( _state != closed )
    {
        fclose(_handle);
        _state = closed;
    }
}

void file::set_byte_position( i32 byte_position /* = 0 */ )
{
    if(byte_position == -1)
        return;

    mode previous_state = _state;
    if(_state != read_binary )
    {
        close();
        open(read_binary);
    }

    rewind(_handle);

    if( byte_position != 0 )
    {
        size_t32 result = (size_t32) fread( NULL, byte_position, 1, _handle );
        CRAP_ASSERT_DEBUG((i32)result == byte_position, "Setting byte position was not successful");
    }

    if(previous_state != read_binary )
    {
        close();
        open(previous_state);
    }
}

template<typename T>
void file::read_bytes( T& buffer, bool byte_wise /* = false */, i32 byte_position /* = -1 */ )
{
    mode previous_state = _state;
    if(_state != read_binary )
    {
        close();
        open(read_binary);
    }

    set_byte_position(byte_position);

    void* ptr = (void*) &buffer;
    size_t32 result = 0;

    if( byte_wise )
    {
        result = (size_t32) fread( ptr, 1, sizeof(buffer), _handle );
        CRAP_ASSERT_DEBUG(result == sizeof(buffer), "Reading bytes was not successful (bytewise)");
    }
    else
    {
        result = (size_t32) fread( ptr, sizeof(buffer), 1, _handle );
        CRAP_ASSERT_DEBUG(result == sizeof(buffer), "Reading bytes was not successful (not bytewise)");
    }

    if(previous_state != read_binary )
    {
        close();
        open(previous_state);
    }
}

template<typename T>
void file::write_bytes( const T& buffer, bool byte_wise /* = false */, i32 byte_position /* = -1 */ )
{
    mode previous_state = _state;
    if(_state != write_binary )
    {
        close();
        open(write_binary);
    }

    set_byte_position(byte_position);

    void* ptr = (void*) &buffer;
    size_t32 result = 0;

    if( byte_wise )
    {
        result = (size_t32) fwrite( ptr, 1, sizeof(buffer), _handle );
        CRAP_ASSERT_DEBUG(result == sizeof(buffer), "Reading bytes was not successful (bytewise)");
    }
    else
    {
        result = (size_t32) fwrite( ptr, sizeof(buffer), 1, _handle );
        CRAP_ASSERT_DEBUG(result == sizeof(buffer), "Reading bytes was not successful (not bytewise)");
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
void file::append_bytes( const T& buffer, bool byte_wise /* = false */ )
{
    mode previous_state = _state;
    if(_state != write_binary )
    {
        close();
        open(write_binary);
    }

    void* ptr = (void*) &buffer;
    size_t32 result = 0;

    if( byte_wise )
    {
        result = (size_t32) fwrite( ptr, 1, sizeof(buffer), _handle );
        CRAP_ASSERT_DEBUG(result == sizeof(buffer), "Reading bytes was not successful (bytewise)");
    }
    else
    {
        result = (size_t32) fwrite( ptr, sizeof(buffer), 1, _handle );
        CRAP_ASSERT_DEBUG(result == sizeof(buffer), "Reading bytes was not successful (not bytewise)");
    }

    if(previous_state != write_binary )
    {
        close();
        open(previous_state);
    }
    else
        fflush(_handle);
}

template<size_t32 S>
void file::read_text( static_string<S>& str, size_t32 size, i32 char_position /*= -1*/ )
{
    CRAP_ASSERT_DEBUG(size <= S, "Size bigger then buffer");

    mode previous_state = _state;
    if(_state != read )
    {
        close();
        open(read);
    }

    set_byte_position(char_position);

    char* result = fgets(str.get_cstring() , size , _handle);
    CRAP_ASSERT_DEBUG(result != 0, "Could not get string");

    if(previous_state != read )
    {
        close();
        open(previous_state);
    }
    else
        fflush(_handle);
}

template<size_t32 S>
void file::write_text( const static_string<S>& str, i32 char_position /*= -1*/ )
{
    mode previous_state = _state;
    if(_state != write )
    {
        close();
        open(write);
    }

    set_byte_position(char_position);

    int result = fputs(str.get_cstring(), _handle);
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
void file::append_text( const static_string<S>& str )
{
    mode previous_state = _state;
    if(_state != append )
    {
        close();
        open(append);
    }

    int result = fputs(str.get_cstring(), _handle);
    CRAP_ASSERT_DEBUG(result >= 0, "Could not append string");

    if(previous_state != write )
    {
        close();
        open(previous_state);
    }
    else
        fflush(_handle);
}


#if defined(CRAP_PLATFORM_WIN)

size_t64 file::size( void )
{
  struct __stat64 fileStat;
  int err = _stat64( _filename.cstring(), &fileStat );
  if (0 != err) return 0;
  return (size_t64) fileStat.st_size;
}

#elif defined(CRAP_COMPILER_GCC)

size_t64 file::size( void )
{
    struct stat fileStat;
    int err = stat(  _filename.cstring(), &fileStat );
    if (0 != err) return 0;
    return (size_t64) fileStat.st_size;
}

#else

size_t64 file::size( void )
{
    std::ifstream f;
    f.open(sFileName, std::ios_base::binary | std::ios_base::in);
    if (!f.good() || f.eof() || !f.is_open()) { return 0; }
    f.seekg(0, std::ios_base::beg);
    std::ifstream::pos_type begin_pos = f.tellg();
    f.seekg(0, std::ios_base::end);
    return static_cast<size_t64>(f.tellg() - begin_pos);
}


#endif

}	// namespace crap
