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

private:
	u32 _shader;
	u32 _type;

public:
	opengl_shader( const char* file, shader_type type );
	~opengl_shader( void );

	u32 source( void ) const;
};

}

#endif //CRAP_OPENGLSHADER_H