////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglshader.h
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Loads and compiles a shader
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_OPENGLSHADER_H
#define CRAP_OPENGLSHADER_H

//lib namespace
namespace crap
{

class opengl_shader
{
public:
	enum shader_type
	{
		vertex_shader = 0,
		fragment_shader = 1,
		geometry_shader = 2
	};

	struct object
	{
		u32 _id;

		object( u32 id ) : _id(id) {}
		~object( void );
	};

	struct program
	{
		u32 _id;
		program( u32 id ) : _id(id) {}
		~program( void );

		void activate( void );
		void deactivate( void );

		u32 uniform_location( const char* name );

		void uniform_matrix4f_value( u32 handle, u32 count, f32* ptr );

		struct vertex_attribute_array
		{
			void enable( u32 index );
			void disable( u32 index );
		} 
		vertex_attribute_array;

		void vertex_attribute_pointer( u32 array_index, u32 size, b8 normalized, u32 stride, void* ptr ); 
	};

	struct vertex_array
	{
		u32 _id;

		void bind( void );

		vertex_array( u32 id ) : _id(id) {}
		~vertex_array( void );
	};

	static opengl_shader::object compile( const char* file, shader_type type );
	static opengl_shader::program link( opengl_shader::object vs, opengl_shader::object fs, opengl_shader::object gs );
	static opengl_shader::vertex_array create_vertex_array( void );

	static void delete_object( opengl_shader::object obj );
	static void delete_program( opengl_shader::program pro );
};

} // lib namespace

#endif //CRAP_OPENGLSHADER_H