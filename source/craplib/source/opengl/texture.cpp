////////////////////////////////////////////////////////
// CRAP Library
//!		@file texture.cpp
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
#include "crap.h"

#include "GL/glew.h"
#include "GL/glfw.h"

#include "opengl/texture.h"

//lib namespace
namespace crap
{

texture::setup::setup( void ) : height(0), width(0),
	wrap_s(GL_REPEAT), wrap_t(GL_REPEAT), mag_filter(GL_LINEAR), min_filter(GL_LINEAR_MIPMAP_LINEAR), type( texture::tga )
	{}

texture::texture( void* data, size_t32 size, setup s ) : id(0)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	if( s.type == bmp )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, s.width, s.height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	else if ( s.type == tga )
		glfwLoadMemoryTexture2D( data, size, 0 );
	else
		CRAP_ASSERT_ERROR("Only bmp and tga supported yet");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s.wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, s.wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, s.mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, s.min_filter); 
	glGenerateMipmap(GL_TEXTURE_2D);

	i32 ogl_id[]= {GL_TEXTURE0,GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5,
		GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13,
		GL_TEXTURE14, GL_TEXTURE15, GL_TEXTURE16, GL_TEXTURE17, GL_TEXTURE18, GL_TEXTURE19, GL_TEXTURE20,
		GL_TEXTURE21, GL_TEXTURE22, GL_TEXTURE23, GL_TEXTURE24, GL_TEXTURE25, GL_TEXTURE26, GL_TEXTURE27,
		GL_TEXTURE28, GL_TEXTURE29, GL_TEXTURE30, GL_TEXTURE31 };
		/* .. continue .. */

	static i32 index_counter = 0;

	index = ogl_id[index_counter++];
}

texture::~texture( void )
{
	glDeleteTextures(1, &id);
}

void texture::bind( void )
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void texture::activate( void )
{
	glActiveTexture(index);
}

} // namespace crap