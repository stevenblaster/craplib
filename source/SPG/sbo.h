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

	sbo( const crap::string64& vs, const crap::string64& ps, content_manager* cm );

	crap::program* operator->( void );

private:
	crap::program _program;
};

#endif //SBO_H