
#include "precompiled.h"
#include "files/file.h"
#include "stringhash.h"
#include "memory/memorypool.h"
#include "contentmanager.h"

void content_manager::init( const crap::string256& initfile, size_t32 memory /* = 10485760  10 MB */ )
{
	_content_pool = new crap::memory_pool( memory );

	crap::file init_file( DATA_PATH + initfile );
	CRAP_ASSERT_DEBUG( init_file.readable(), "Initfile not readable." );

	size_t32 file_size = (size_t32)init_file.size();
	u8* data = (u8*) _content_pool->allocate( file_size );
	init_file.read_bytes( data, file_size );

	for( size_t32 i=0; i < file_size; ++i )
	{
		crap::string64 folder;
		if( data[i] == '#' )
		{
			//cathegory
			c8* nextpos = strchr( (c8*)data, '\n' );
			if( nextpos != 0 )
			{
				*nextpos = '\0';
				strcpy((c8*)&folder, (c8*)data+i);
				i += (size_t32)nextpos - (size_t32) data+i;
				continue;
			}
			else
				break;
		}
		if( data[i] >= 97 && data[i] <= 122 ) // a-z
		{
			//dataset
			c8* nextpos = strchr( (c8*)data, '\n' );
			if( nextpos != 0 )
			{
				*nextpos = '\0';
				crap::string64 parse_me( (c8*)data+i );
				crap::vector< crap::string64 > sets = parse_me.split('=');
				crap::string64 insert( folder);
				insert += "/";
				insert += parse_me;
				_filelist.insert( std::pair<u32, crap::string64 >( string_to_hash<64>(sets[0]), insert ) );
				u32 i = (size_t32)nextpos - (size_t32) data+1;
				continue;
			}
			else
				break;
		}
		else
		{
			//anything else
			c8* nextpos = strchr( (c8*)data, '\n' );
			if( nextpos != 0 )
			{
				i += (size_t32)nextpos - (size_t32) data + i;
				continue;
			}
			else
				break;
		}
		
	}
}