#pragma once

#ifndef SHADERFILE_H
#define SHADERFILE_H

namespace crap
{
template<size_t32 S> class fixed_string;
typedef fixed_string<256> string256;
class memory_pool;
}

struct shader_content;

class shader_file
{
public:
	shader_file( const crap::string256& filename , crap::memory_pool* pool  );
	~shader_file( void );

	crap::fixed_string<4096*4> data;
	size_t32 size;

	void create_shader_content( shader_content* content );
private:

	crap::memory_pool* _content_pool;
};

#endif //SHADERFILE_H