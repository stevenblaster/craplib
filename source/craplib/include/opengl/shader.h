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

#ifndef CRAP_SHADER_H
#define CRAP_SHADER_H

//lib namespace
namespace crap
{

enum data_type
{
	gl_byte = 0x1400,
	gl_ubyte = 0x1401,
	gl_short = 0x1402,
	gl_ushort = 0x1403,
	gl_int = 0x1404,
	gl_uint = 0x1405,
	gl_float = 0x1406,
	gl_2_bytes = 0x1407,
	gl_3_bytes = 0x1408,
	gl_4_bytes = 0x1409,
	gl_double = 0x140A
};

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

	void uniform_matrix3f_value( uniform id, u32 size, f32* ptr );

	void uniform_matrix4f_value( uniform id, u32 count, f32* ptr );

	void uniform_1i( uniform id, u32 number ); //TODO

	void uniform_1f( uniform id, f32 number ); //TODO

	void uniform_3f( uniform id, f32 x, f32 y, f32 z );

	struct vertex_attribute_array
	{
		void enable( u32 index );
		void disable( u32 index );
		void pointer ( u32 array_index, u32 size, data_type type, b8 normalized, u32 stride, void* ptr );
	} 
	vertex_attribute_array;
};


struct shader
{
	static object compile( const c8* data , shader_type type );
	static program link( object vs, object fs, object gs );

	static void delete_object( object obj );
	static void delete_program( program pro );
};

} // lib namespace

#endif //CRAP_OPENGLSHADER_H