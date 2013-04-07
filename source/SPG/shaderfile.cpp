#include "precompiled.h"

#include "files/file.h"
#include "memory/memorypool.h"
#include "container/fixedstring.h"
#include "shadercontent.h"

#include "shaderfile.h"

shader_file::shader_file( const crap::string256& filename , crap::memory_pool* pool  ) : _content_pool(pool)
{
	crap::file sdr_file(DATA_PATH + filename);
	CRAP_ASSERT_DEBUG( sdr_file.readable(), "Shader File does not exist or is not readable" );

	sdr_file.read_text( data, 4096*4 );
	sdr_file.close();
}

shader_file::~shader_file( void )
{
	//_content_pool->deallocate( data );
}

void shader_file::create_shader_content( shader_content* content )
{
	content->size = data.size();
	content->data = data;
}