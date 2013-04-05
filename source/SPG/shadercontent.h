#pragma once

#ifndef SHADERCONTENT_H
#define SHADERCONTENT_H

struct shader_content
{
	size_t32 size;
	u8* data;
	shader_content( void );
};

#endif //SHADERCONTENT_H