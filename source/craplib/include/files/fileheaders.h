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

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

//lib namespace
namespace crap
{

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

struct bmp_header
{
	i16		bm;					// "BM" decimal 19778
	i32		size;				// size of file, might be incorrect
	i32		reserved;			// usually 0
	i32		offset;				// offset in byte to data, ususally 54 byte
	i32		header_size;		// usually 40
	i32		width;				// width of image
	i32		height;				// height of image, positive if bottom-up negative is top-down
	i16		planes;				// old and not used, usually 1
	i16		color_depth;		// in BPP: 1,2,4,8,16,24,32  should be 24
	i32		compression;		// 0=RGB, 1=RLE8, 2=RLE4, 3=BITFIELDS. should be RGB, 4 and 8 need BPP 4 or 8
	i32		size_of_image;		// 0 or size of image in byte
	i32		pix_per_meter_x;	// meant for pixel per meter for some output - usually zero
	i32		pix_per_meter_y;	// meant for pixel per meter for some output - usually zero
	i32		color_table;		// is there a colortable? - 0 for 24 bpp
	i32		color_table_imp;	// is the colortable importaint? 0 again

	bool validate( void ) const
	{
		return bm == 19778 && color_depth == 24; 
	}
};

struct dds_header
{
	struct pix_f
	{
		i32 pf_size;			// size of subheader (32)
		i32 pf_fags;			// flags
		i32 pf_four_cc;
		i32 pf_rgb_bit_count;
		i32 pf_r_bitmask;
		i32 pf_g_bitmask;
		i32 pf_b_bitmask;
		i32 pf_a_bitmask;
	};

	u8		filecode[4];		// should be "DDS "
	i32		header_size;		// should be 124
	i32		flags;				// flags
	i32		height;				// height in pixel
	i32		width;				// width in pixel
	i32		pitch_or_linear_s;	// pitch or linear size
	i32		depth;				// depth of volume (if volume pixel)
	i32		mip_map_count;		// number of mip maps
	i32		reserved[11];		// unused
	pix_f	pixelformat;		// pixelformat
	i32		caps;				// caps
	i32		caps2;				// caps2
	i32		caps3;				// caps3
	i32		caps4;				// caps4
	i32		reserved2;			// reserved... again

	bool validate( void )
	{
		return filecode[0] == 'D' && filecode[1] == 'D' && filecode[2] == 'S' && filecode[3] == ' ' &&
			header_size == 124;
	}
};

} // lib namespace

#endif // CRAP_FILES_HEADERS_H
