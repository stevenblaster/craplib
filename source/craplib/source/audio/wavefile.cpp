////////////////////////////////////////////////////////
// CRAP Library
//!		@file wavefile.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Handling WAVE files
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "audio/wavefile.h"

//lib namespace
namespace crap
{

wave_file::wave_file( const crap::string256& filename ) : _file( filename ), _data( 0 )
{
	CRAP_ASSERT_DEBUG( _file.readable(), "Wave File does not exist or is not readable" );
	_file.read_bytes( _header );
	CRAP_ASSERT_DEBUG( _header.validate(), "Not a valid Wave-file" );
	_data = new u8[ _header.data_length ];
	_file.read_bytes( _data, _header.data_length );
}

wave_file::~wave_file( void )
{
	delete _data;
	_file.close();
}

wave_file::wav_header& wave_file::info( void )
{
	return _header;
}

const wave_file::wav_header& wave_file::info( void ) const
{
	return _header;
}

u8* wave_file::data( void )
{
	return _data;
}

} //namespace crap