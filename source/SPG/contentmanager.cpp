
#include "precompiled.h"

#include "math/vector3.h"
#include "math/vector2.h"
#include "files/file.h"
#include "stringhash.h"
#include "geometrycontent.h"
#include "geometryfile.h"
#include "texturecontent.h"
#include "texturefile.h"
#include "shadercontent.h"
#include "shaderfile.h"
#include "memory/memorypool.h"
#include "control/converter.h"
#include "contentmanager.h"

void content_manager::init( const crap::string256& initfile, size_t32 memory /* = 10485760  10 MB */ )
{
	_content_pool = new crap::memory_pool( memory );

	crap::file init_file( DATA_PATH + initfile );
	CRAP_ASSERT_DEBUG( init_file.readable(), "Initfile not readable." );

	size_t32 file_size = (size_t32)init_file.size();
	u8* data = (u8*) _content_pool->allocate( file_size );
	init_file.read_bytes( data, file_size );

	crap::string256 folder;
	for( size_t32 i=0; i < file_size; ++i )
	{
		if( data[i] == '#' )
		{
			//cathegory
			c8* nextpos = strchr( (c8*)data+i, '\n' );
			if( nextpos != 0 )
			{
				if( *(nextpos -1) == '\r' ) //shitty windump
					*(nextpos -1) = '\0';
				*nextpos = '\0';
				memset( &folder, 0, 256);
				strcpy((c8*)&folder, (c8*)data+i+1);
				i = (size_t32)nextpos - (size_t32) data;
				continue;
			}
			else
				break;
		}
		if( data[i] >= 97 && data[i] <= 122 ) // a-z
		{
			//dataset
			c8* nextpos = strchr( (c8*)data+i, '\n' );
			if( nextpos != 0 )
			{
				if( *(nextpos -1) == '\r' ) //shitty windump
					*(nextpos -1) = '\0';
				*nextpos = '\0';
				crap::string256 parse_me( (c8*)data+i );
				crap::vector< crap::string256 > sets = parse_me.split('=');
				crap::string256 insert( folder);
				insert += "/";
				insert += sets[1];
				_filelist.insert( std::pair<u32, crap::string256 >( string_to_hash<256>(sets[0]), insert ) );
				i = (size_t32)nextpos - (size_t32) data;
				continue;
			}
			else
				break;
		}
		else
		{
			//anything else
			c8* nextpos = strchr( (c8*)data+i, '\n' );
			if( nextpos != 0 )
			{
				i = (size_t32)nextpos - (size_t32) data;
				continue;
			}
			else
				break;
		}	
	}
	_content_pool->deallocate( data );
}

void content_manager::load_file( u32 str_hash, void* data, type_name type)
{
	if( type == type_name::geometry )
	{
		if( is_binary( str_hash ) )
		{
			load_binary( str_hash, data, type );
		}
		else
		{
			geometry_file geo_file( _filelist.find( str_hash )->second, geometry_file::wavefront, _content_pool );
			geo_file.create_geometry_content( (geometry_content*)data );
		}
		return;
	}

	if( type == type_name::texture )
	{
		if( is_binary( str_hash ) )
		{
			load_binary( str_hash, data, type );
		}
		else
		{
			((texture_content*)data)->data = (crap::texture*)_content_pool->allocate( sizeof(crap::texture) );
			crap::string256 path = DATA_PATH;
			path += _filelist.find( str_hash )->second;
			*((texture_content*)data)->data = crap::create_texture( path.cstring(), crap::tga );
		}
		return;
	}

	if( type == type_name::shader )
	{
		if( is_binary( str_hash ) )
		{
			load_binary( str_hash, data, type );
		}
		else
		{
			shader_file sdr_file( _filelist.find( str_hash )->second, _content_pool );
			sdr_file.create_shader_content( (shader_content*)data );
		}
		return;
	}
}

void content_manager::save_binary( u32 str_hash, void* ptr, type_name type )
{
	if( type == type_name::geometry )
	{
		crap::file binary_file( BINARY_PATH + crap::convert<u32, crap::string256>(str_hash) );
		CRAP_ASSERT_DEBUG( binary_file.writeable(), "Cannot wirte binary file." );

		geometry_content* idx_mem = (geometry_content*) ptr;

		u32 total_size = sizeof(u32)*2 + sizeof(u16)*idx_mem->indices_size + 
			sizeof(crap::vector3f)*4*idx_mem->vertices_size + sizeof(crap::vector2f)*idx_mem->vertices_size;
		u8* buffer = (u8*)_content_pool->allocate( total_size );

		u32 offset = 0;
		memcpy( buffer + offset, &idx_mem->indices_size, sizeof(u32) );
		offset += sizeof(u32);
		memcpy( buffer + offset, &idx_mem->vertices_size, sizeof(u32) );
		offset += sizeof(u32);
		memcpy( buffer + offset, idx_mem->indices, sizeof(u16)*idx_mem->indices_size );
		offset += sizeof(u16)*idx_mem->indices_size;
		memcpy( buffer + offset, idx_mem->positions, sizeof(crap::vector3f)*idx_mem->vertices_size );
		offset += sizeof(crap::vector3f)*idx_mem->vertices_size;
		memcpy( buffer + offset, idx_mem->uvs, sizeof(crap::vector2f)*idx_mem->vertices_size );
		offset += sizeof(crap::vector2f)*idx_mem->vertices_size;
		memcpy( buffer + offset, idx_mem->normals, sizeof(crap::vector3f)*idx_mem->vertices_size );
		offset += sizeof(crap::vector3f)*idx_mem->vertices_size;
		memcpy( buffer + offset, idx_mem->tangents, sizeof(crap::vector3f)*idx_mem->vertices_size );
		offset += sizeof(crap::vector3f)*idx_mem->vertices_size;
		memcpy( buffer + offset, idx_mem->binormals, sizeof(crap::vector3f)*idx_mem->vertices_size );

		binary_file.write_bytes( buffer, total_size );
		binary_file.close();

		_content_pool->deallocate( buffer );
		return;
	}

	if( type == type_name::texture )
	{
		CRAP_ASSERT_ERROR("Not implemented yet");
		//crap::file binary_file( BINARY_PATH + crap::convert<u32, crap::string256>(str_hash) );
		//CRAP_ASSERT_DEBUG( binary_file.writeable(), "Cannot wirte binary file." );

		//texture_content* tex_mem = (texture_content*) ptr;

		//u32 total_size = sizeof(texture_content) + tex_mem->width * tex_mem->height * tex_mem->bpp;
		//u8* buffer = (u8*)_content_pool->allocate( total_size );

		//u32 offset = 0;
		//memcpy( buffer + offset, &tex_mem->width, sizeof(i32) );
		//offset += sizeof(i32);
		//memcpy( buffer + offset, &tex_mem->height, sizeof(i32) );
		//offset += sizeof(i32);
		//memcpy( buffer + offset, &tex_mem->format, sizeof(i32) );
		//offset += sizeof(i32);
		//memcpy( buffer + offset, &tex_mem->bpp, sizeof(i32) );
		//offset += sizeof(i32);
		//memcpy( buffer + offset, tex_mem->data, tex_mem->width * tex_mem->height * tex_mem->bpp );

		//binary_file.write_bytes( buffer, total_size );
		//binary_file.close();

		//_content_pool->deallocate( buffer );
		//return;
	}

	if( type == type_name::shader )
	{
		crap::file binary_file( BINARY_PATH + crap::convert<u32, crap::string256>(str_hash) );
		CRAP_ASSERT_DEBUG( binary_file.writeable(), "Cannot wirte binary file." );

		shader_content* sdr_mem = (shader_content*) ptr;

		u32 total_size = sizeof(shader_content) + sdr_mem->size;
		u8* buffer = (u8*)_content_pool->allocate( total_size );

		u32 offset = 0;
		memcpy( buffer + offset, &sdr_mem->size, sizeof(size_t32) );
		offset += sizeof(size_t32);
		memcpy( buffer + offset, &sdr_mem->data, sdr_mem->size );

		binary_file.write_bytes( buffer, total_size );
		binary_file.close();

		_content_pool->deallocate( buffer );
		return;
	}
}

void content_manager::load_binary( u32 str_hash, void* ptr,  type_name type )
{
	if( type == type_name::geometry )
	{
		crap::file binary_file( BINARY_PATH + crap::convert<u32, crap::string256>(str_hash) );
		CRAP_ASSERT_DEBUG( binary_file.readable(), "Cannot read binary file." );

		geometry_content* idx_mem = (geometry_content*) ptr;
		
		u8* buffer = (u8*)_content_pool->allocate( (size_t32)binary_file.size() );
		binary_file.read_bytes( buffer, (size_t32)binary_file.size() );
		binary_file.close();

		u32 offset = 0;
		memcpy( &idx_mem->indices_size, buffer + offset, sizeof(u32) );
		offset += sizeof(u32);
		memcpy( &idx_mem->vertices_size, buffer + offset, sizeof(u32) );
		offset += sizeof(u32);

		idx_mem->indices = (u16*)_content_pool->allocate(sizeof(u16)*idx_mem->indices_size);
		idx_mem->positions = (crap::vector3f*)_content_pool->allocate( sizeof(crap::vector3f)*idx_mem->vertices_size );
		idx_mem->uvs = (crap::vector2f*)_content_pool->allocate( sizeof(crap::vector2f)*idx_mem->vertices_size );
		idx_mem->normals = (crap::vector3f*)_content_pool->allocate( sizeof(crap::vector3f)*idx_mem->vertices_size );
		idx_mem->tangents = (crap::vector3f*)_content_pool->allocate( sizeof(crap::vector3f)*idx_mem->vertices_size );
		idx_mem->binormals = (crap::vector3f*)_content_pool->allocate( sizeof(crap::vector3f)*idx_mem->vertices_size );

		memcpy( idx_mem->indices, buffer + offset, sizeof(u16)*idx_mem->indices_size );
		offset += sizeof(u16)*idx_mem->indices_size;
		memcpy( idx_mem->positions, buffer + offset, sizeof(crap::vector3f)*idx_mem->vertices_size );
		offset += sizeof(crap::vector3f)*idx_mem->vertices_size;
		memcpy( idx_mem->uvs, buffer + offset, sizeof(crap::vector2f)*idx_mem->vertices_size );
		offset += sizeof(crap::vector2f)*idx_mem->vertices_size;
		memcpy( idx_mem->normals, buffer + offset, sizeof(crap::vector3f)*idx_mem->vertices_size );
		offset += sizeof(crap::vector3f)*idx_mem->vertices_size;
		memcpy( idx_mem->tangents, buffer + offset, sizeof(crap::vector3f)*idx_mem->vertices_size );
		offset += sizeof(crap::vector3f)*idx_mem->vertices_size;
		memcpy( idx_mem->binormals, buffer + offset, sizeof(crap::vector3f)*idx_mem->vertices_size );
		
		_content_pool->deallocate( buffer );
		return;
	}

	if( type == type_name::texture )
	{
		CRAP_ASSERT_ERROR("Not implemented yet");
		/*crap::file binary_file( BINARY_PATH + crap::convert<u32, crap::string256>(str_hash) );
		CRAP_ASSERT_DEBUG( binary_file.readable(), "Cannot read binary file." );

		texture_content* tex_mem = (texture_content*) ptr;
		
		u8* buffer = (u8*)_content_pool->allocate( (size_t32)binary_file.size() );
		binary_file.read_bytes( buffer, (size_t32)binary_file.size() );
		binary_file.close();

		u32 offset = 0;
		memcpy( &tex_mem->width, buffer + offset, sizeof(i32) );
		offset += sizeof(i32);
		memcpy( &tex_mem->height, buffer + offset, sizeof(i32) );
		offset += sizeof(i32);
		memcpy( &tex_mem->format, buffer + offset, sizeof(i32) );
		offset += sizeof(i32);
		memcpy( &tex_mem->bpp, buffer + offset, sizeof(i32) );
		offset += sizeof(i32);

		tex_mem->data = (u8*)_content_pool->allocate( tex_mem->width * tex_mem->height * tex_mem->bpp );
		memcpy( tex_mem->data, buffer + offset, tex_mem->width * tex_mem->height * tex_mem->bpp );

		_content_pool->deallocate( buffer );*/

		return;
	}

	if( type == type_name::shader )
	{
		crap::file binary_file( BINARY_PATH + crap::convert<u32, crap::string256>(str_hash) );
		CRAP_ASSERT_DEBUG( binary_file.readable(), "Cannot read binary file." );

		shader_content* sdr_mem = (shader_content*) ptr;
		
		u8* buffer = (u8*)_content_pool->allocate( (size_t32)binary_file.size() );
		binary_file.read_bytes( buffer, (size_t32)binary_file.size() );
		binary_file.close();

		u32 offset = 0;
		memcpy( &sdr_mem->size, buffer + offset, sizeof(size_t32) );
		offset += sizeof(size_t32);

		sdr_mem->data = (c8*)_content_pool->allocate( sdr_mem->size );
		memcpy( &sdr_mem->data, buffer + offset, sdr_mem->size );

		_content_pool->deallocate( buffer );

		return;
	}
}

bool content_manager::is_binary( u32 str_hash )
{
	crap::file check_file( BINARY_PATH + crap::convert<u32, crap::string256>(str_hash) );
	return check_file.readable();
}

void content_manager::create_content( const crap::string64& id, void* ptr, type_name type )
{
	u32 str_hash = string_to_hash<64>( id );
	CRAP_ASSERT_DEBUG( _filelist.find( str_hash ) != _filelist.end(), "Object not known." );
	load_file( str_hash, ptr, type);
}

void content_manager::save_content( const crap::string64& id, void* ptr, type_name type )
{
	u32 str_hash = string_to_hash<64>( id );
	CRAP_ASSERT_DEBUG( _filelist.find( str_hash ) != _filelist.end(), "Object not known." );
	save_binary( str_hash, ptr, type);
}

void content_manager::delete_content( const crap::string64& id, void* ptr, type_name type )
{
	if( type == type_name::geometry )
	{
		geometry_content* ig = (geometry_content*) ptr;
		_content_pool->deallocate( ig->indices );
		_content_pool->deallocate( ig->positions );
		_content_pool->deallocate( ig->uvs );
		_content_pool->deallocate( ig->normals );
		_content_pool->deallocate( ig->tangents );
		_content_pool->deallocate( ig->binormals );
		return;
	}

	if( type == type_name::texture )
	{
		texture_content* tc = (texture_content*) ptr;
		tc->data->delete_texture();
		_content_pool->deallocate( tc->data );
		return;
	}

	if( type == type_name::shader )
	{
		shader_content* sc = (shader_content*) ptr;
		//_content_pool->deallocate( sc->data );
		return;
	}
}