////////////////////////////////////////////////////////
// CRAP Library
//!		@file opengl.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief wrapper for opengl functions
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"
#include "GL/glew.h"

#if defined( CRAP_PLATFORM_WIN )
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "opengl/buffer.h"

//lib namespace
namespace crap
{
buffer::buffer( void ) : 
	_buffer(0), _size(0), _type(0), _usage(0)
{

}

buffer::buffer( buffer_type type, buffer_usage usage, size_t32 size/* = 1 */ ) : 
	_buffer(0), _size(size), _type(0), _usage(0)
{
	glGenBuffers( size, &_buffer );

	if( type == array_buffer ) _type = GL_ARRAY_BUFFER;
	else if( type == atomic_counter_buffer ) _type = GL_ATOMIC_COUNTER_BUFFER;
	else if( type == copy_read_buffer ) _type = GL_COPY_READ_BUFFER;
	else if( type == copy_write_buffer ) _type = GL_COPY_WRITE_BUFFER;
	else if( type == draw_indirect_buffer ) _type = GL_DRAW_INDIRECT_BUFFER;
	else if( type == dispatch_indirect_buffer ) _type = GL_DISPATCH_INDIRECT_BUFFER;
	else if( type == element_array_buffer ) _type = GL_ELEMENT_ARRAY_BUFFER;
	else if( type == pixel_pack_buffer ) _type = GL_PIXEL_PACK_BUFFER;
	else if( type == pixel_unpack_buffer ) _type = GL_PIXEL_UNPACK_BUFFER;
	else if( type == shader_storage_buffer ) _type = GL_SHADER_STORAGE_BUFFER;
	else if( type == texture_buffer ) _type = GL_TEXTURE_BUFFER;
	else if( type == transform_feedback_buffer ) _type = GL_TRANSFORM_FEEDBACK_BUFFER;
	else if( type == uniform_buffer ) _type = GL_UNIFORM_BUFFER;
	else CRAP_ASSERT_ERROR( "Buffer type not known" );

	if( usage == stream_draw ) _usage = GL_STREAM_DRAW; 
	else if( usage == stream_read ) _usage = GL_STREAM_READ;  
	else if( usage == stream_copy ) _usage = GL_STREAM_COPY; 
	else if( usage == static_draw ) _usage = GL_STATIC_DRAW; 
	else if( usage == static_read ) _usage = GL_STATIC_READ; 
	else if( usage == static_copy ) _usage = GL_STATIC_COPY; 
	else if( usage == dynamic_draw ) _usage = GL_DYNAMIC_DRAW; 
	else if( usage == dynamic_read ) _usage = GL_DYNAMIC_READ; 
	else if( usage == dynamic_copy ) _usage = GL_DYNAMIC_COPY; 
	else CRAP_ASSERT_ERROR( "Buffer usage not known" );
}

buffer::~buffer( void )
{
	glDeleteBuffers(_size, &_buffer);
}

void buffer::init( buffer_type type, buffer_usage usage, size_t32 size/* = 1 */ )
{
	_size = size;
	glGenBuffers( size, &_buffer );

	if( type == array_buffer ) _type = GL_ARRAY_BUFFER;
	else if( type == atomic_counter_buffer ) _type = GL_ATOMIC_COUNTER_BUFFER;
	else if( type == copy_read_buffer ) _type = GL_COPY_READ_BUFFER;
	else if( type == copy_write_buffer ) _type = GL_COPY_WRITE_BUFFER;
	else if( type == draw_indirect_buffer ) _type = GL_DRAW_INDIRECT_BUFFER;
	else if( type == dispatch_indirect_buffer ) _type = GL_DISPATCH_INDIRECT_BUFFER;
	else if( type == element_array_buffer ) _type = GL_ELEMENT_ARRAY_BUFFER;
	else if( type == pixel_pack_buffer ) _type = GL_PIXEL_PACK_BUFFER;
	else if( type == pixel_unpack_buffer ) _type = GL_PIXEL_UNPACK_BUFFER;
	else if( type == shader_storage_buffer ) _type = GL_SHADER_STORAGE_BUFFER;
	else if( type == texture_buffer ) _type = GL_TEXTURE_BUFFER;
	else if( type == transform_feedback_buffer ) _type = GL_TRANSFORM_FEEDBACK_BUFFER;
	else if( type == uniform_buffer ) _type = GL_UNIFORM_BUFFER;
	else CRAP_ASSERT_ERROR( "Buffer type not known" );

	if( usage == stream_draw ) _usage = GL_STREAM_DRAW; 
	else if( usage == stream_read ) _usage = GL_STREAM_READ;  
	else if( usage == stream_copy ) _usage = GL_STREAM_COPY; 
	else if( usage == static_draw ) _usage = GL_STATIC_DRAW; 
	else if( usage == static_read ) _usage = GL_STATIC_READ; 
	else if( usage == static_copy ) _usage = GL_STATIC_COPY; 
	else if( usage == dynamic_draw ) _usage = GL_DYNAMIC_DRAW; 
	else if( usage == dynamic_read ) _usage = GL_DYNAMIC_READ; 
	else if( usage == dynamic_copy ) _usage = GL_DYNAMIC_COPY; 
	else CRAP_ASSERT_ERROR( "Buffer usage not known" );
}

void buffer::bind( void )
{
	glBindBuffer( _type, _buffer );
}

void buffer::set_data( size_t32 size, void* data )
{
	glBufferData( _type, size, data, _usage );
}

} //namespace crap