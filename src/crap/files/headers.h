////////////////////////////////////////////////////////
// CRAP Library
//!		@file headers.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Some file headers
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_FILES_HEADERS_H
#define CRAP_FILES_HEADERS_H

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
};

#endif // HEADERS_H
