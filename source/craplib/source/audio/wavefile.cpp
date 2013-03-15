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
#include "AL/al.h"
#include "audio/wavefile.h"

//lib namespace
namespace crap
{

wave_file::wave_file( const crap::string256& filename ) : _file( filename ), _data( 0 ), _al_source(0), _al_buffer(0), _al_format(0)
{
	CRAP_ASSERT_DEBUG( _file.readable(), "Wave File does not exist or is not readable" );
	_file.read_bytes( &_header, sizeof(_header) );
	CRAP_ASSERT_DEBUG( _header.validate(), "Not a valid Wave-file" );
	_data = new u8[ _header.data_length ];
	_file.read_bytes( _data, _header.data_length );

    alGenBuffers(1, &_al_buffer);
    alGenSources(1, &_al_source);
	CRAP_ASSERT_DEBUG( alGetError() == AL_NO_ERROR, "Wavefile could not generate buffers" );

	if(_header.bits_per_sample == 8) 
    {
		if(_header.channels == 1)
            _al_format = AL_FORMAT_MONO8;
        else if(_header.channels == 2)
            _al_format = AL_FORMAT_STEREO8;
    }
    else if(_header.bits_per_sample == 16)
    {
        if(_header.channels == 1)
            _al_format = AL_FORMAT_MONO16;
        else if(_header.channels == 2)
            _al_format = AL_FORMAT_STEREO16;
    }
	CRAP_ASSERT_DEBUG(_al_format, "Wavefile has no valid sound format");

    alBufferData(_al_buffer, _al_format, _data, _header.data_length, _header.frequency);
    CRAP_ASSERT_DEBUG(alGetError() == AL_NO_ERROR, "Wavefile could not init buffer");
}

wave_file::~wave_file( void )
{
	delete[] _data;
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