#pragma once

#ifndef VBO_H
#define VBO_H

#include "opengl/buffer.h"

class content_manager;
class vbo
{
public:
	enum draw_type
	{
		static_draw,
		dynamic_draw
	};

	enum buffer_type
	{
		indicies,
		verticies,
		uvs,
		normals,
		tangents,
		binormals
	};

	vbo( const crap::string64& id, content_manager* cm, draw_type type );
	~vbo( void );

	void bind_buffer( buffer_type type );

	size_t32 indicies_size;
	size_t32 vertices_size;

private:
	
	crap::buffer _indicies_buffer;
	crap::buffer _vertices_buffer;
	crap::buffer _uvs_buffer;
	crap::buffer _normals_buffer;
	crap::buffer _tangents_buffer;
	crap::buffer _binormals_buffer;
};

#endif // VBO_H