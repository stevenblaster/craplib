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

u32 opengl_shader::compile( const char* filename , opengl_shader::shader_type type ) 
{
	u32 type_macro = 0;
	if( type == vertex_shader )
		type_macro = GL_VERTEX_SHADER;
	else if( type == fragment_shader )
		type_macro = GL_FRAGMENT_SHADER;
	else if( type == geometry_shader )
		type_macro = GL_GEOMETRY_SHADER;

	GLuint shader = glCreateShader( type_macro );

	file source_file( filename );
	CRAP_ASSERT_DEBUG( source_file.readable(), "Could not open file" );

	static_string<2048> buffer;
	source_file.read_text( buffer, 2048 );
	source_file.close();

	const char* c_text = buffer.cstring();

	glShaderSource(shader, 1, &c_text, NULL);
    glCompileShader(shader);

	GLint result = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	string1024 info;
	glGetShaderInfoLog(shader, 1024, NULL, (GLchar*)&info );
    std::cout << info << std::endl;

	CRAP_ASSERT_DEBUG( result != GL_FALSE, "Compiling failed" );

	return shader;
}

u32 opengl_shader::link( u32 vs, u32 fs, u32 gs )
{
	GLuint program = glCreateProgram();

	if( vs != 0 )
		glAttachShader(program, vs);

	if( fs != 0 )
		glAttachShader(program, fs);

	if( gs != 0 )
		glAttachShader(program, gs);

    glLinkProgram(program);

	GLint result = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	string1024 info;
	glGetProgramInfoLog(program, 1024, NULL, (GLchar*)&info );
    std::cout << info << std::endl;

	CRAP_ASSERT_DEBUG( result != GL_FALSE, "Linking shader program failed" );

	return program;
}

void opengl_shader::delete_shader( u32 shader )
{
	glDeleteShader(shader);
}

void opengl_shader::delete_program( u32 program )
{
	glDeleteShader(program);
}

void opengl_shader::activate_program( u32 program )
{
	glUseProgram(program);
}

}	//lib namespace