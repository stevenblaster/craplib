////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglbuffer.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief wrapper for openglbuffer functions
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_OPENGL_OPENGLBUFFER_H
#define CRAP_OPENGL_OPENGLBUFFER_H

//lib namespace
namespace crap
{

struct opengl_buffer
{
	enum buffer_type
	{
		array_buffer,
        atomic_counter_buffer,
        copy_read_buffer,
        copy_write_buffer,
        draw_indirect_buffer,
        dispatch_indirect_buffer,
        element_array_buffer,
        pixel_pack_buffer,
        pixel_unpack_buffer,
        shader_storage_buffer,
        texture_buffer,
        transform_feedback_buffer, 
        uniform_buffer
	};

	enum buffer_usage
	{
		stream_draw, 
		stream_read, 
		stream_copy, 
		static_draw, 
		static_read, 
		static_copy, 
		dynamic_draw, 
		dynamic_read,
		dynamic_copy
	};

	opengl_buffer( buffer_type type, buffer_usage usage );
	~opengl_buffer( void );

	void bind( void );

	void set_data( size_t32 size, void* data );

private:

	u32 _buffer;
	u32 _type;
	u32 _usage;
};

}	//lib namespace

#endif //CRAP_OPENGL_OPENGLBUFFER_H