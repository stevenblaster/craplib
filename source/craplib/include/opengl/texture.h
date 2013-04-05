////////////////////////////////////////////////////////
// CRAP Library
//!		@file texture.h
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Loads an image to GPU
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_TEXTURE_H
#define CRAP_TEXTURE_H

//lib namespace
namespace crap
{

class texture
{
public:
	enum image_type
	{
		bmp = 0,
		tga,
		dds
	};

	struct setup
	{
		u32 height;
		u32 width;

		i32 wrap_s;
		i32 wrap_t;
		i32 mag_filter;
		i32 min_filter;

		image_type type;

		setup( void );
	};

	texture( void* data, size_t32 size, setup s );
	~texture( void );

	void bind( void );
	void activate( void );

	u32 id;
	u32 index;
};

} //lib namespace

#endif //CRAP_TEXTURE_H