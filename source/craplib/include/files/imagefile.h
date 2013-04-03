////////////////////////////////////////////////////////
// CRAP Library
//!		@file imagefile.h
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Loads image files
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_FILES_IMAGEFILE_H
#define CRAP_FILES_IMAGEFILE_H

#include "math/vector2.h"
#include "container/fixedstring.h"

//lib namespace
namespace crap
{


class image_file
{
public:

	enum file_type
	{
		bmp = 0,
		tga,
		dds
	};

	image_file( const string256& filename , file_type type  );
	~image_file( void );

	size_t32 size( void ) const;
	vector2i dimension( void ) const;
	i32 format( void ) const;
	i32 bpp( void ) const;
	u8* data( void ) const;

private:

	void load_tga( const string256& str );
	void load_bmp( const string256& str );

	image_file( const image_file& other ) {}
	image_file& operator=( const image_file& other ) { return *this; }

	size_t32 _size;
	vector2i _dimension;
	i32 _format;
	i32 _bpp;
	u8* _data;
};

}	//namespace crap

#endif // CRAP_FILES_IMAGEFILE