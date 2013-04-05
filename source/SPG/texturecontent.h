#pragma once

#ifndef TEXTURECONTENT_H
#define TEXTURECONTENT_H

namespace crap
{
template<typename T> struct vector2;
typedef vector2<i32> vector2i;
}

struct texture_content
{
	size_t32 size;
	crap::vector2i dimension;
	i32 format;
	i32 bpp;
	u8* data;

	texture_content( void );
};

#endif // TEXTURECONTENT_H