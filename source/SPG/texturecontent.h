#pragma once

#ifndef TEXTURECONTENT_H
#define TEXTURECONTENT_H

namespace crap
{
struct texture;
}

struct texture_content
{
	crap::texture* data;

	texture_content( void );
	
};

#endif // TEXTURECONTENT_H