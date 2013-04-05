#include "precompiled.h"

#include "math/vector2.h"
#include "container/fixedstring.h"
#include "opengl/texture.h"
#include "contentmanager.h"
#include "texturecontent.h"
#include "tbo.h"


tbo::tbo( const crap::string64& id, content_manager* cm, image_type type )
{
	texture_content tc;
	cm->create_content( id , &tc, type_name::texture );

	crap::texture::setup is;
	is.width = tc.dimension.x;
	is.height = tc.dimension.y;
	_tex = new crap::texture( tc.data, tc.size, is );

	cm->delete_content( id, &tc, type_name::texture );
}

tbo::~tbo( void )
{
	delete _tex;
}

void tbo::bind_buffer( void )
{
	_tex->bind();
}

void tbo::activate( void )
{
	_tex->activate();
}