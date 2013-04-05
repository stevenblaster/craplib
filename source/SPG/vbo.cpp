#include "precompiled.h"

#include "math/vector3.h"
#include "math/vector2.h"
#include "container/fixedstring.h"
#include "opengl/buffer.h"
#include "geometrycontent.h"
#include "contentmanager.h"
#include "vbo.h"


vbo::vbo( const crap::string64& id, content_manager* cm, draw_type type ) : indicies_size(0), vertices_size(0)
{
	crap::buffer::buffer_usage bu = ( type == static_draw ) ? crap::buffer::static_draw : crap::buffer::dynamic_draw;

	geometry_content ig;
	cm->create_content( id , &ig, type_name::geometry );

	indicies_size = ig.indices_size;
	vertices_size = ig.vertices_size;

	_indicies_buffer.init( crap::buffer::element_array_buffer, bu );
	_indicies_buffer.bind();
	_indicies_buffer.set_data( ig.indices_size *sizeof(u16), &ig.indices[0] );

	_vertices_buffer.init( crap::buffer::array_buffer, bu );
	_vertices_buffer.bind();
	_vertices_buffer.set_data( ig.vertices_size*sizeof(crap::vector3f), &ig.positions[0] );

	_uvs_buffer.init( crap::buffer::array_buffer, bu );
	_uvs_buffer.bind();
	_uvs_buffer.set_data( ig.vertices_size*sizeof(crap::vector2f), &ig.uvs[0] );

	_normals_buffer.init( crap::buffer::array_buffer, bu );
	_normals_buffer.bind();
	_normals_buffer.set_data( ig.vertices_size*sizeof(crap::vector3f), &ig.normals[0] );

	_tangents_buffer.init( crap::buffer::array_buffer, bu );
	_tangents_buffer.bind();
	_tangents_buffer.set_data( ig.vertices_size*sizeof(crap::vector3f), &ig.tangents[0] );

	_binormals_buffer.init( crap::buffer::array_buffer, bu);
	_binormals_buffer.bind();
	_binormals_buffer.set_data( ig.vertices_size*sizeof(crap::vector3f), &ig.binormals[0] );

	cm->delete_content( id , &ig, type_name::geometry );
}

vbo::~vbo( void )
{
	//buffer delete themselves by getting out of scope
}

void vbo::bind_buffer( buffer_type type )
{
	if(type == indicies)
	{
		_indicies_buffer.bind();
		return;
	}
	if(type == verticies)
	{
		_vertices_buffer.bind();
		return;
	}
	if(type == uvs)
	{
		_uvs_buffer.bind();
		return;
	}
	if(type == normals)
	{
		_normals_buffer.bind();
		return;
	}
	if(type == tangents)
	{
		_tangents_buffer.bind();
		return;
	}
	if(type == binormals)
	{
		_binormals_buffer.bind();
		return;
	}
}