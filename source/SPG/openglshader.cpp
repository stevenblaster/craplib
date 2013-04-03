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
#include "control/logger.h"
#include "opengl/openglshader.h"

//lib namespace
namespace crap
{

//ogl namespace
namespace opengl
{

object shader::compile( const char* filename , shader_type type ) 
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

	fixed_string<4096> buffer;
	source_file.read_text( buffer, 4096 );
	source_file.close();

	const char* c_text = buffer.cstring();

	glShaderSource(shader, 1, &c_text, NULL);
    glCompileShader(shader);

	GLint result = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	string512 info;
	glGetShaderInfoLog(shader, 512, NULL, (GLchar*)&info );
    //CRAP_LOG_INFO( crap::log_opengl, info.cstring() );
	CRAP_ASSERT_DEBUG( result != GL_FALSE, "Compiling failed" );

	return shader;
}

program shader::link( object vs, object fs, object gs )
{
	GLuint program = glCreateProgram();

	if( vs._id != 0 )
		glAttachShader(program, vs._id);

	if( fs._id != 0 )
		glAttachShader(program, fs._id);

	if( gs._id != 0 )
		glAttachShader(program, gs._id);

    glLinkProgram(program);

	GLint result = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	string512 info;
	glGetProgramInfoLog(program, 1024, NULL, (GLchar*)&info );
    //CRAP_LOG_INFO(crap::log_opengl,info.cstring());
	CRAP_ASSERT_DEBUG( result != GL_FALSE, "Linking shader program failed" );

	return program;
}


void shader::delete_object( object shader )
{
	glDeleteShader(shader._id);
}

void shader::delete_program( program program )
{
	glDeleteProgram(program._id);
}

object::~object( void )
{
	glDeleteShader(_id);
}

program::~program( void )
{
	glDeleteProgram(_id);
}

void program::activate( void )
{
	glUseProgram(_id);
}

void program::deactivate( void )
{
	glUseProgram(0);
}

uniform program::uniform_location( const char* name )
{
	return glGetUniformLocation(_id, name);
}

void program::uniform_matrix3f_value( uniform id, u32 size, f32* ptr )
{
	glUniformMatrix3fv(id._id, 1, GL_FALSE, ptr);
}

void program::uniform_matrix4f_value( uniform id, u32 size, f32* ptr )
{
	glUniformMatrix4fv(id._id, 1, GL_FALSE, ptr);
}

void program::uniform_1i( uniform id, u32 count )
{
	glUniform1i(id._id, count);
}

void program::uniform_3f( uniform id, f32 x, f32 y, f32 z )
{
	glUniform3f( id._id, x, y, z);
}

void program::vertex_attribute_array::enable( u32 index )
{
	glEnableVertexAttribArray( index );
}

void program::vertex_attribute_array::disable( u32 index )
{
	glDisableVertexAttribArray( index );
}

void program::vertex_attribute_array::pointer( u32 array_index, u32 size ,data_type type, b8 normalized, u32 stride, void* ptr )
{
	glVertexAttribPointer(
                array_index,        // attribute. No particular reason for 0, but must match the layout in the shader.
                size,               // size
                type,				// type
                normalized,         // normalized?
                stride,             // stride
                ptr			        // array buffer offset
                );
}

} //namespace opengl

}	//lib namespace
