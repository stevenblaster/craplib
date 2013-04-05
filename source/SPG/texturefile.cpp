#include "precompiled.h"

#include "files/file.h"
#include "files/fileheaders.h"
#include "files/imagefile.h"
#include "math/vector2.h"
#include "memory/memorypool.h"

#include "texturecontent.h"
#include "texturefile.h"


texture_file::texture_file( const crap::string256& filename , file_type type, crap::memory_pool* pool  ) : _data(0), _content_pool(pool)
{
	if( type == tga )
		load_tga( filename );
	else if( type == bmp )
		load_bmp( filename );
	else
		CRAP_ASSERT_ERROR( "Only TGA and BMP supported yet" );
}

texture_file::~texture_file( void )
{
	_content_pool->deallocate(_data);
}

size_t32 texture_file::size( void ) const
{
	return _size;
}

crap::vector2i texture_file::dimension( void ) const
{
	return _dimension;
}

i32 texture_file::format( void ) const
{
	return _format;
}

i32 texture_file::bpp( void ) const
{
	return _bpp;
}

u8* texture_file::data( void ) const
{
	return _data;
}

void texture_file::load_tga( const crap::string256& str )
{
	struct image_data
	{
		int Width, Height;
		int Format;
		int BytesPerPixel;
		unsigned char *Data;
	} img;

	i32 result = crap::image_file::load_glfw_tga( DATA_PATH + str.cstring() , &img );
	CRAP_ASSERT_DEBUG( result != 0 , "Not a valid TGA-file" );
	
	_dimension.x = img.Width;
	_dimension.y = img.Height;
	_format = img.Format;
	_bpp = img.BytesPerPixel;
	_size = img.Width * img.Height * img.BytesPerPixel;
	_data = (u8*)_content_pool->allocate( _size );
	memcpy( _data, img.Data, _size );
	delete[] img.Data;
}

void texture_file::load_bmp( const crap::string256& str )
{
	crap::bmp_header head;
	crap::file bmp_file(str);
	CRAP_ASSERT_DEBUG( bmp_file.readable(), "BMP File does not exist or is not readable" );
	bmp_file.read_bytes( &head, sizeof(head) );
	CRAP_ASSERT_DEBUG( head.validate(), "Not a valid BMP-file" );

	if( head.size_of_image == 0 )
		head.size_of_image = head.width * head.height * 3; // 3 = RGB

	if( head.offset == 0 )
		head.offset = 54; //default

	u8* dat = (u8*)_content_pool->allocate( head.size_of_image  );
	bmp_file.read_bytes( dat, head.size_of_image );
	bmp_file.close();

	_dimension.x = head.width;
	_dimension.y = head.height;
	_format = 0x1907;
	_bpp = 24;
	_size = head.width * head.height * 3;
	_data = dat;
}

void texture_file::create_texture_content( texture_content* createme )
{
	createme->size = _size;
	createme->dimension = _dimension;
	createme->format = _format;
	createme->bpp = _bpp;
	createme->data = (u8*)_content_pool->allocate( _size );
	memcpy( createme->data, _data, _size );
}