////////////////////////////////////////////////////////
// CRAP Library
//!		@file opengltexture.h
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Loads and image for opengl
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_OPENGLTEXTURE_H
#define CRAP_OPENGLTEXTURE_H

//lib namespace
namespace crap
{

//ogl namespace
namespace opengl
{

enum image_type
{
	bmp = 0,
	tga,
	dds
};

struct texture
{
	u32 _id;
	u32 _index;
	~texture( void );

	void bind( void );
	void activate( void );
	
	texture( u32 id , u32 index );
	texture( const texture& other );
	texture& operator=( const texture& other );
};

texture create_texture( const char* name, image_type type );
u32 create_texture_bmp( const char* name );
u32 create_texture_tga( const char* name );
u32 create_texture_dds( const char* name );

} // namespace opengl

} //namespace crap

#endif //CRAP_OPENGLTEXTURE_H