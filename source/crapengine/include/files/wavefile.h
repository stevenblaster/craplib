////////////////////////////////////////////////////////
//  CRAP Library
//!		@file wavefile.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Handling WAVE files
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_WAVEFILE_H
#define CRAP_WAVEFILE_H

//lib namespace
namespace crap
{

class file;
class audiodevice;

class wave_file
{
public:
	struct wav_header
	{
		char	riff[4];			// "RIFF"
		i32		filesize;			// filesize minus 8
		char	wavefmt[8];			// "WAVEfmt "
		i32		headerlength;		// 16
		i16		version;			// 1
		i16		channels;			// 1:mono, 2:stereo
		i32		frequency;			// in Hz
		i32		bytes_per_sec;		// bytes per second
		i16		bytes_per_sample;	// eg 2 for 16 bits
		i16		bits_per_sample;	// bits per sample
		char	data[4];			// "data"
		i32		data_length;		// following data length

		bool validate( void ) const
		{
			return riff[0] == 'R' && riff[1] == 'I' && riff[2] == 'F' && riff[3] == 'F' &&
				wavefmt[0] == 'W' && wavefmt[1] == 'A' && wavefmt[2] == 'V' && wavefmt[3] == 'E' &&
				wavefmt[4] == 'f' && wavefmt[5] == 'm' && wavefmt[6] == 't' && wavefmt[7] == ' ' &&
				data[0] == 'd' && data[1] == 'a' && data[2] == 't' && data[3] == 'a';
		}
	};

private:
	file _file;
	wav_header _header;
	u8* _data;
	u32 _al_source;
    u32 _al_buffer;
    i32 _al_format;

	//setup
	f32 _pitch;
	f32 _gain;
	i32 _loop;

public:
	wave_file( const crap::string256& filename );
	~wave_file( void );

	wav_header& info( void );
	const wav_header& info( void ) const;

	f32 pitch( void ) const;
	void set_pitch( f32 p );

	f32 gain( void ) const;
	void set_gain( f32 g );

	b8 loop( void ) const;
	void set_loop( b8 val );

    void play( crap::vector3f source_pos, crap::vector3f source_vel, crap::vector3f listener_pos,
		crap::vector3f listener_vel, crap::vector3f listener_dir, crap::vector3f listener_up );

	u8* data( void );
};

}

#endif //CRAP_WAVEFILE_H
