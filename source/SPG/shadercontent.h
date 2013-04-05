#pragma once

#ifndef SHADERCONTENT_H
#define SHADERCONTENT_H

struct shader_content
{
	size_t32 size;
	crap::fixed_string<4096> data;
	shader_content( void );
};

#endif //SHADERCONTENT_H