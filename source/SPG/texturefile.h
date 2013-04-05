#pragma once

#ifndef TEXTUREFILE_H
#define TEXTUREFILE_H

namespace crap
{
template<size_t32 S> class fixed_string;
typedef fixed_string<256> string256;
template<typename T> struct vector2;
typedef vector2<i32> vector2i;
class memory_pool;
}

struct texture_content;

class texture_file
{
public:

	enum file_type
	{
		bmp = 0,
		tga,
		dds
	};

	texture_file( const crap::string256& filename , file_type type, crap::memory_pool* pool  );
	~texture_file( void );

	void create_texture_content( texture_content* createme );

	size_t32 size( void ) const;
	crap::vector2i dimension( void ) const;
	i32 format( void ) const;
	i32 bpp( void ) const;
	u8* data( void ) const;

private:

	void load_tga( const crap::string256& str );
	void load_bmp( const crap::string256& str );

	texture_file( const texture_file& other ) {}
	texture_file& operator=( const texture_file& other ) { return *this; }

	size_t32 _size;
	crap::vector2i _dimension;
	i32 _format;
	i32 _bpp;
	u8* _data;

	crap::memory_pool* _content_pool;
};

#endif //TEXTUREFILE_H