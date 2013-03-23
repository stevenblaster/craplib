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

	static u32 compile( const char* file, shader_type type );
	static u32 link( u32 vs, u32 fs, u32 gs );

	static void delete_shader( u32 shader );
	static void delete_program( u32 program );
};

} // lib namespace

#endif //CRAP_OPENGLSHADER_H