#pragma once

#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "container/map.h"
#include "container/fixedstring.h"
#include "control/converter.h"
#include "stringhash.h"

namespace crap
{
	class memory_pool;
}

enum type_name
{
	geometry,
	texture,
	shader
};

template<>
inline crap::fixed_string<256> crap::convert<u32, crap::fixed_string<256> >( const u32& variable )
{
	c8 buffer[256];
	sprintf(buffer, "%" PRIu32, variable);
	return crap::fixed_string<256>( buffer);
}

class content_manager
{
public:
	void init( const crap::string256& initfile, size_t32 memory = 10485760 /* 10 MB */ );

	void create_content( const crap::string64& id, void* ptr, type_name type );
	void delete_content( const crap::string64& id, void* ptr, type_name type );
	void save_content( const crap::string64& id, void* ptr, type_name type );

private:
	crap::memory_pool* _content_pool;
	std::map< u32, crap::string256 > _filelist;

	void load_file( u32 str_hash, void* data, type_name type);

	void save_binary( u32 str_hash, void* ptr, type_name type );
	void load_binary( u32 str_hash, void* ptr, type_name type );
	bool is_binary( u32 str_hash );
};

#endif //CONTENTMANAGER_H