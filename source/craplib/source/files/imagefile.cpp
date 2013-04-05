////////////////////////////////////////////////////////
// CRAP Library
//!		@file imagefile.cpp
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
#include "crap.h"
#include "GL/glfw.h"
#include "files/file.h"
#include "files/fileheaders.h"


#include "files/imagefile.h"

//lib namespace
namespace crap
{

image_file::image_file( const string256& filename , file_type type  ) : _data(0)
{
	if( type == tga )
		load_tga( filename );
	else if( type == bmp )
		load_bmp( filename );
	else
		CRAP_ASSERT_ERROR( "Only TGA and BMP supported yet" );
}

image_file::~image_file( void )
{
	delete[] _data;
}

size_t32 image_file::size( void ) const
{
	return _size;
}

vector2i image_file::dimension( void ) const
{
	return _dimension;
}

i32 image_file::format( void ) const
{
	return _format;
}

i32 image_file::bpp( void ) const
{
	return _bpp;
}

u8* image_file::data( void ) const
{
	return _data;
}

void image_file::load_tga( const string256& str )
{
	GLFWimage img;
	i32 result = glfwReadImage( str.cstring() , &img, 0 );
	CRAP_ASSERT_DEBUG( result != GL_FALSE , "Not a valid BMP-file" );
	
	_dimension.x = img.Width;
	_dimension.y = img.Height;
	_format = img.Format;
	_bpp = img.BytesPerPixel;
	_size = img.Width * img.Height;
	_data = img.Data;
}

void image_file::load_bmp( const string256& str )
{
	bmp_header head;
	file bmp_file(str);
	CRAP_ASSERT_DEBUG( bmp_file.readable(), "BMP File does not exist or is not readable" );
	bmp_file.read_bytes( &head, sizeof(head) );
	CRAP_ASSERT_DEBUG( head.validate(), "Not a valid BMP-file" );

	if( head.size_of_image == 0 )
		head.size_of_image = head.width * head.height * 3; // 3 = RGB

	if( head.offset == 0 )
		head.offset = 54; //default

	u8* dat = new u8[ head.size_of_image ];
	bmp_file.read_bytes( dat, head.size_of_image );
	bmp_file.close();

	_dimension.x = head.width;
	_dimension.y = head.height;
	_format = GL_RGB;
	_bpp = 24;
	_size = head.width * head.height * 3;
	_data = dat;
}

int image_file::load_glfw_tga( const string256& str, void* data )
{
	GLFWimage* img = (GLFWimage*) data;
	i32 result = glfwReadImage( str.cstring() , img, 0 );
	return result;
}

} //crap lib namespace