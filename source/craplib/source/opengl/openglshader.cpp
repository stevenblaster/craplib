////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglshader.cpp
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
#include "crap.h"

#include "GL/glew.h"

#include "container/string.h"
#include "files/file.h"
#include "opengl/openglshader.h"

//lib namespace
namespace crap
{

opengl_shader::opengl_shader( const char* filename , opengl_shader::shader_type type ) 
{
	if( type == vertex_shader )
		_type = GL_VERTEX_SHADER;
	else if( type == fragment_shader )
		_type = GL_FRAGMENT_SHADER;
	else 
		_type = GL_GEOMETRY_SHADER;

	_shader = glCreateShader(_type);

	file source_file( filename );
	CRAP_ASSERT_DEBUG( source_file.readable(), "Could not open file" );

	static_string<2048> buffer;
	source_file.read_text( buffer, 2048 );
	source_file.close();

	const char* c_text = buffer.cstring();

	glShaderSource(_shader, 1, &c_text, NULL);
    glCompileShader(_shader);

	GLint result = GL_FALSE;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &result);

	CRAP_ASSERT_DEBUG( result != GL_FALSE, "Compiling failed" );
}

opengl_shader::~opengl_shader( void )
{
	glDeleteShader(_shader);
}

u32 opengl_shader::source( void ) const
{
	return _shader;
}

}	//lib namespace