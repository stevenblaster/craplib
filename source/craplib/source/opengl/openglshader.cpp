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

opengl_shader::object opengl_shader::compile( const char* filename , opengl_shader::shader_type type ) 
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

opengl_shader::program opengl_shader::link( opengl_shader::object vs, opengl_shader::object fs, opengl_shader::object gs )
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

	string1024 info;
	glGetProgramInfoLog(program, 1024, NULL, (GLchar*)&info );
    std::cout << info << std::endl;

	CRAP_ASSERT_DEBUG( result != GL_FALSE, "Linking shader program failed" );

	return program;
}

opengl_shader::vertex_array opengl_shader::create_vertex_array( void )
{
	u32 id;
	glGenVertexArrays(1, &id);
	return id;
}

opengl_shader::vertex_array::~vertex_array( void )
{
	glDeleteVertexArrays(1, &_id );
}

void opengl_shader::vertex_array::bind( void )
{
	glBindVertexArray(_id);
}

void opengl_shader::delete_object( opengl_shader::object shader )
{
	glDeleteShader(shader._id);
}

void opengl_shader::delete_program( opengl_shader::program program )
{
	glDeleteProgram(program._id);
}

opengl_shader::object::~object( void )
{
	glDeleteShader(_id);
}

opengl_shader::program::~program( void )
{
	glDeleteProgram(_id);
}

void opengl_shader::program::activate( void )
{
	glUseProgram(_id);
}

void opengl_shader::program::deactivate( void )
{
	glUseProgram(0);
}

u32 opengl_shader::program::uniform_location( const char* name )
{
	return glGetUniformLocation(_id, name);
}

void opengl_shader::program::uniform_matrix4f_value( u32 id, u32 size, f32* ptr )
{
	glUniformMatrix4fv(id, 1, GL_FALSE, ptr);
}

void opengl_shader::program::vertex_attribute_array::enable( u32 index )
{
	glEnableVertexAttribArray( index );
}

void opengl_shader::program::vertex_attribute_array::disable( u32 index )
{
	glDisableVertexAttribArray( index );
}

void opengl_shader::program::vertex_attribute_pointer( u32 array_index, u32 size, b8 normalized, u32 stride, void* ptr )
{
	glVertexAttribPointer(
                array_index,             // attribute. No particular reason for 0, but must match the layout in the shader.
                size,               // size
                GL_FLOAT,           // type
                normalized,         // normalized?
                stride,             // stride
                ptr			        // array buffer offset
                );
}

}	//lib namespace