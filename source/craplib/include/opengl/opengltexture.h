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
	void uniform_1i( u32 location, u32 num ); //TODO

	static texture create( const char* name, image_type type );

	texture& operator=( const texture& other );
	texture( const texture& other );

private:
	texture( u32 id=0 );
	
	
	static texture from_bmp( const char* name );
	static texture from_tga( const char* name );
	static texture from_dds( const char* name );

};

} // namespace opengl

} //namespace crap

#endif //CRAP_OPENGLTEXTURE_H