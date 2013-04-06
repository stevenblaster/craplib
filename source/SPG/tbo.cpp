#include "precompiled.h"

#include "math/vector2.h"
#include "container/fixedstring.h"
#include "opengl/texture.h"
#include "contentmanager.h"
#include "texturecontent.h"
#include "tbo.h"


tbo::tbo( const crap::string64& id, content_manager* cm, image_type type ) : _id(id), _cm(cm)
{
	_tex = new texture_content();
	cm->create_content( id , _tex, type_name::texture );
}

tbo::~tbo( void )
{
	_cm->delete_content( _id , _tex, type_name::texture );
	delete _tex;
}

void tbo::bind_buffer( void )
{
	_tex->data->bind();
}

void tbo::activate( void )
{
	_tex->data->activate();
}