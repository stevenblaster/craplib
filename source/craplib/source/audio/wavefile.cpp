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
#include "files/file.h"
#include "files/fileheaders.h"
#include "math/vector3.h"
#include "audio/wavefile.h"

//lib namespace
namespace crap
{

wave_file::wave_file( const crap::string256& filename ) : _file( filename ), _data( 0 ), _al_source(0), _al_buffer(0), 
	_al_format(0), _pitch(1.f), _gain(1.f), _loop(0)
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
f32 wave_file::pitch( void ) const
{
	return _pitch;
}

void wave_file::set_pitch( f32 p )
{
	_pitch = p;
}

f32 wave_file::gain( void ) const
{
	return _gain;
}

void wave_file::set_gain( f32 g )
{
	_gain = g;
}

b8 wave_file::loop( void ) const
{
	return _loop == 1;
}

void wave_file::set_loop( b8 val )
{
	_loop = ( val ) ? 1 : 0;
}

void wave_file::play( vector3f source_pos, vector3f source_vel, vector3f listener_pos,
		vector3f listener_vel, vector3f listener_dir, vector3f listener_up )
{
	struct orientation
	{
		vector3f dir;
		vector3f up;
		orientation(vector3f d, vector3f u) : dir(d), up(u) {}
	};

	orientation listener_ori( listener_dir, listener_up );

	alListenerfv(AL_POSITION, (ALfloat*)&listener_pos);
    alListenerfv(AL_VELOCITY, (ALfloat*)&listener_vel);
    alListenerfv(AL_ORIENTATION, (ALfloat*)&listener_ori);

	alSourcei (_al_source, AL_BUFFER, _al_buffer);
    alSourcef (_al_source, AL_PITCH, _pitch);
    alSourcef (_al_source, AL_GAIN, _gain);
    alSourcefv(_al_source, AL_POSITION, (ALfloat*)&source_pos);
    alSourcefv(_al_source, AL_VELOCITY, (ALfloat*)&source_vel);
    alSourcei (_al_source, AL_LOOPING, _loop);

	alSourcePlay(_al_source); 
}

u8* wave_file::data( void )
{
	return _data;
}

} //namespace crap
