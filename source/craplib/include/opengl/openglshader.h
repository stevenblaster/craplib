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

//ogl namespace
namespace opengl
{

enum shader_type
{
	vertex_shader = 0,
	fragment_shader = 1,
	geometry_shader = 2
};

struct uniform
{
	u32 _id;

	uniform( u32 id ) : _id(id) {}
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

	uniform uniform_location( const char* name );

	void uniform_matrix4f_value( uniform id, u32 count, f32* ptr );

	void uniform_1i( uniform id, u32 count ); //TODO

	void uniform_3f( uniform id, f32 x, f32 y, f32 z );

	struct vertex_attribute_array
	{
		void enable( u32 index );
		void disable( u32 index );
		void pointer ( u32 array_index, u32 size, b8 normalized, u32 stride, void* ptr );
	} 
	vertex_attribute_array;
};


struct shader
{
	static object compile( const char* file, shader_type type );
	static program link( object vs, object fs, object gs );

	static void delete_object( object obj );
	static void delete_program( program pro );
};

} //namespace opengl

} // lib namespace

#endif //CRAP_OPENGLSHADER_H