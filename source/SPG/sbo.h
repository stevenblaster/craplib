#pragma once

#ifndef SBO_H
#define SBO_H

#include "opengl/shader.h"

class content_manager;

class sbo
{
public:
	enum sbo_type
	{
		vertex_shader = 0,
		fragment_shader = 1,
		geometry_shader = 2
	};

	struct uniforms
	{
		crap::uniform world_matrix;
		crap::uniform view_matrix;
		crap::uniform model_matrix;
		crap::uniform model_view_matrix;
		crap::uniform diffuse_texture;
		crap::uniform normal_texture;
		crap::uniform specular_texture;
		crap::uniform specular_type;
		crap::uniform light_position;
		crap::uniform light_view_matrix;
		crap::uniform light_type;
		crap::uniform light_color;
		crap::uniform light_power;
		crap::uniform ambient_color;
		crap::uniform specular_color;
	};

	sbo( const crap::string64& vs, const crap::string64& ps, content_manager* cm );

	crap::program* operator->( void );
	crap::program& operator*( void );

private:
	crap::program _program;
};

#endif //SBO_H