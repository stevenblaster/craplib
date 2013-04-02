////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglshader.cpp
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Loads and compiles a shader
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include <algorithm>

#include "crap.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/geometry.h"
#include "container/staticstring.h"
#include "files/file.h"
#include "opengl/openglvertex.h"
#include "opengl/openglvbo.h"
#include "opengl/wavefrontfile.h"

#include "container/vector.h"

//lib namespace
namespace crap
{

wavefront_file::wavefront_file( string256 filename ) : _vertices_index(0), _uvs_index(0), _normals_index(0), 
	_face_index(0), _group_index(0), _material_index(0), _vertices(0), _uvs(0), _normals(0), _faces(0), _groups(0), _material_groups(0)
{
	file obj_file( filename );
	u8* buffer = new u8[ (size_t32)obj_file.size() ];
	obj_file.read_bytes( buffer, (size_t32)obj_file.size() );
	obj_file.close();

	u32 count_vertices = 0;
	u32 count_uvs = 0;
	u32 count_normals = 0;
	u32 count_faces = 0;
	u32 count_groups = 0;
	u32 count_material_groups = 0;

	//count content
	b8 newline = true;
	for( int i = 0; i< obj_file.size(); ++i )
	{
		if( newline )
		{
			newline = false;

			switch( buffer[i] )
			{
			case '#':
				{
					//comment
					break;
				}

			case 'v':
				{
					if( buffer[ i+1 ] == 't' )
						++_uvs_index;
					else if( buffer[ i+1 ] == 'n' )
						++_normals_index;
					else if( buffer[ i+1 ] == ' ' )
						++_vertices_index;

					break;
				}

			case 'f':
				{
					++_face_index;

					break;
				}

			case 'g':
				{
					++_group_index;

					break;
				}

			case 'u':
				{
					if( buffer[i+1] == 's' && buffer[i+2] == 'e' && buffer[i+3] == 'm' && buffer[i+4] == 't' && buffer[i+5] == 'l' )
						++_material_index;

					break;
				}

			default:
				{}
			}
		}
		
		if( buffer[i] == '\n' )
			newline = true;
	}

	if( _vertices_index != 0 )
		_vertices = new vector3f[ _vertices_index ];

	if( _uvs_index != 0 )
		_uvs = new vector2f[ _uvs_index ];

	if( _normals_index != 0 )
		_normals = new vector3f[ _normals_index ];

	if( _face_index != 0 )
		_faces = new face[ _face_index ];

	if( _group_index != 0 )
		_groups = new group[ _group_index ];

	if( _material_index != 0 )
		_material_groups = new material_group[ _material_index ];

	newline = true;
	for( int i = 0; i< obj_file.size(); ++i )
	{
		if( newline )
		{
			newline = false;

			switch( buffer[i] )
			{
			case '#':
				{
					//comment
					break;
				}

			case 'v':
				{
					if( buffer[ i+1 ] == 't' )
					{
						vector2f uv_vec;
						sscanf( (const char*)buffer+i+3, "%f %f", &uv_vec.x, &uv_vec.y );
						_uvs[ count_uvs++ ] = uv_vec;
					}
					else if( buffer[ i+1 ] == 'n' )
					{
						vector3f norm_vec;
						sscanf( (const char*)buffer+i+3, "%f %f %f", &norm_vec.x, &norm_vec.y, &norm_vec.z );
						_normals[ count_normals++ ] = norm_vec;
					}
					else if( buffer[ i+1 ] == ' ' )
					{
						vector3f vert_vec;
						sscanf( (const char*)buffer+i+2, "%f %f %f", &vert_vec.x, &vert_vec.y, &vert_vec.z );
						_vertices[ count_vertices++ ] = vert_vec;
					}

					break;
				}

			case 'f':
				{
					face tmp_face;
					sscanf( (const char*)buffer+i+2, "%i/%i/%i %i/%i/%i %i/%i/%i", 
						&(tmp_face.vertices[0]), &(tmp_face.uvs[0]), &(tmp_face.normals[0]),
						&(tmp_face.vertices[1]), &(tmp_face.uvs[1]), &(tmp_face.normals[1]),
						&(tmp_face.vertices[2]), &(tmp_face.uvs[2]), &(tmp_face.normals[2]) );
					_faces[ count_faces++ ] = tmp_face;

					break;
				}

			case 'g':
				{
					if( _groups[count_groups].index_start != -1 )
						_groups[ count_groups++ ].index_end = count_faces;
					else
						_groups[count_groups].index_start = count_faces;

					break;
				}

			case 'u':
				{
					if( buffer[i+1] == 's' && buffer[i+2] == 'e' && buffer[i+3] == 'm' && buffer[i+4] == 't' && buffer[i+5] == 'l' )
					{
						if( _material_groups[ count_material_groups ].index_start != -1 )
							_material_groups[ count_material_groups++ ].index_end = count_faces;
						else
							_material_groups[ count_material_groups ].index_start = count_faces;
					}

					break;
				}

			default:
				{}
			}
		}
		
		if( buffer[i] == '\n' )
			newline = true;
	}
	if( count_groups != 0 && _groups[count_groups].index_end == -1 )
		_groups[ count_groups ].index_end = count_faces;

	if( count_material_groups != 0 && _material_groups[ count_material_groups ].index_end == -1 )
		_material_groups[ count_material_groups ].index_end = count_faces;
}

wavefront_file::~wavefront_file( void )
{
	delete[] _vertices;
	delete[] _uvs;
	delete[] _normals;
	delete[] _faces;
	delete[] _groups;
	delete[] _material_groups;
}

vector3f* wavefront_file::vertices( void ) const
{
	return _vertices;
}

vector2f* wavefront_file::uvs( void ) const
{
	return _uvs;
}

vector3f* wavefront_file::normals( void ) const
{
	return _normals;
}

wavefront_file::face* wavefront_file::faces( void ) const
{
	return _faces;
}


wavefront_file::group* wavefront_file::groups( void ) const
{
	return _groups;
}

wavefront_file::material_group* wavefront_file::material_groups( void ) const
{
	return _material_groups;
}

u32 wavefront_file::vertices_index( void ) const
{
	return _vertices_index;
}

u32 wavefront_file::uvs_index( void ) const
{
	return _uvs_index;
}
u32 wavefront_file::normals_index( void ) const
{
	return _normals_index;
}

u32 wavefront_file::face_index( void ) const
{
	return _face_index;
}

u32 wavefront_file::group_index( void ) const
{
	return _group_index;
}

u32 wavefront_file::material_index( void ) const
{
	return _material_index;
}

void wavefront_file::generate_triangles( crap::vector3f* vertices, crap::vector2f* uvs, crap::vector3f* normals )
{
	int index = 0;
	for(u32 i=0; i< _face_index; ++i)
	{
		vertices[index] = _vertices[ _faces[i].vertices[0] - 1 ];
		uvs[index] = _uvs[ _faces[i].uvs[0] -1 ];
		normals[index++] = _normals[ _faces[i].normals[0] -1 ];

		vertices[index] = _vertices[ _faces[i].vertices[1] - 1 ];
		uvs[index] = _uvs[ _faces[i].uvs[1] -1 ];
		normals[index++] = _normals[ _faces[i].normals[1] -1 ];

		vertices[index] = _vertices[ _faces[i].vertices[2] - 1 ];
		uvs[index] = _uvs[ _faces[i].uvs[2] -1 ];
		normals[index++] = _normals[ _faces[i].normals[2] -1 ];
	}
}

void wavefront_file::generate_simple_vbo( opengl::simple_vbo* vbo_struct )
{
	crap::vector<opengl::simple_vertex_index> vertex_list;
	crap::vector<u16> index_list;

	i32 index = 0;
	for(u32 i=0; i< _face_index; ++i)
	{
		for(u32 j=0; j<3; ++j)
		{
			opengl::simple_vertex_index ind;
			ind.position = _faces[i].vertices[j];
			ind.uv = _faces[i].uvs[j];
			ind.normal = _faces[i].normals[j];

            crap::vector<opengl::simple_vertex_index>::iterator find_iterator = std::find(vertex_list.begin(), vertex_list.end(), ind);
            if( std::find(vertex_list.begin(), vertex_list.end(), ind) == vertex_list.end() )
			{
				ind.index = index;
				vertex_list.push_back( ind );
				index_list.push_back( index++ );
			}
			else
			{
				u16 idx = find_iterator->index;
				index_list.push_back( idx );
			}
		}
	}

	vbo_struct->index_size = index_list.size();
	vbo_struct->vertices_size = vertex_list.size();
	vbo_struct->indices = new u16[ index_list.size() ];
	vbo_struct->positions = new vector3f[ vertex_list.size() ];
	vbo_struct->uvs = new vector2f[ vertex_list.size() ];
	vbo_struct->normals = new vector3f[ vertex_list.size() ];

	index = 0;
	for( crap::vector<u16>::iterator it = index_list.begin(); it != index_list.end(); ++it )
	{
		vbo_struct->indices[index++] = *it;
	}

	index = 0;
    crap::vector<opengl::simple_vertex_index>::iterator it = vertex_list.begin();
	for( it; it != vertex_list.end(); ++it )
	{
		vbo_struct->positions[index] = _vertices[ it->position -1 ];
		vbo_struct->uvs[index] = _uvs[ it->uv -1 ];
		vbo_struct->normals[index++] = _normals[ it->normal -1 ];
	}
}

void wavefront_file::generate_vbo( opengl::vbo* vbo_struct )
{
	opengl::simple_vbo simple_vbo_struct;
	generate_simple_vbo( &simple_vbo_struct );

	vbo_struct->index_size = simple_vbo_struct.index_size;
	vbo_struct->vertices_size = simple_vbo_struct.vertices_size;

	vbo_struct->indices = simple_vbo_struct.indices;
	vbo_struct->positions = simple_vbo_struct.positions;
	vbo_struct->uvs = simple_vbo_struct.uvs;
	vbo_struct->normals = simple_vbo_struct.normals;

	vbo_struct->tangents = new vector3f[ vbo_struct->vertices_size ];
	vbo_struct->binormals = new vector3f[ vbo_struct->vertices_size ];

	simple_vbo_struct.indices = 0;
	simple_vbo_struct.positions = 0;
	simple_vbo_struct.uvs = 0;
	simple_vbo_struct.normals = 0;

	for( u32 i=0; i< vbo_struct->index_size; i+=3 )
	{
		u32 idx1 = vbo_struct->indices[i];
		u32 idx2 = vbo_struct->indices[i+1];
		u32 idx3 = vbo_struct->indices[i+2];

		crap::vector3f& pos1 = vbo_struct->positions[idx1];
		crap::vector3f& pos2 = vbo_struct->positions[idx2];
		crap::vector3f& pos3 = vbo_struct->positions[idx3];

		crap::vector2f& uv1 = vbo_struct->uvs[idx1];
		crap::vector2f& uv2 = vbo_struct->uvs[idx2];
		crap::vector2f& uv3 = vbo_struct->uvs[idx3];

		crap::vector3f& nor1 = vbo_struct->normals[idx1];
		crap::vector3f& nor2 = vbo_struct->normals[idx2];
		crap::vector3f& nor3 = vbo_struct->normals[idx3];

		// Edges of the triangle : postion delta
		crap::vector3f delta_pos1 = pos2-pos1;
		crap::vector3f delta_pos2 = pos3-pos1;

		// UV delta
		crap::vector2f delta_uv1 = uv2-uv1;
		crap::vector2f delta_uv2 = uv3-uv1;

		f32 r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
		vbo_struct->tangents[idx1] = (delta_pos1 * delta_uv2.y   - delta_pos2 * delta_uv1.y)*r;
		vbo_struct->binormals[idx1] = (delta_pos2 * delta_uv1.x   - delta_pos1 * delta_uv2.x)*r;
		vbo_struct->tangents[idx2] = vbo_struct->tangents[idx1];
		vbo_struct->binormals[idx2] = vbo_struct->binormals[idx1];
		vbo_struct->tangents[idx3] = vbo_struct->tangents[idx1];
		vbo_struct->binormals[idx3] = vbo_struct->binormals[idx1];

		//first
		vbo_struct->tangents[idx1] = vbo_struct->tangents[idx1] - nor1 * geometryf::dot(nor1, vbo_struct->tangents[idx1]);
		geometryf::normalize( &(vbo_struct->tangents[idx1]) );
		if (geometryf::dot(geometryf::cross(nor1, vbo_struct->tangents[idx1]), vbo_struct->binormals[idx1]) < 0.0f)
		{
			vbo_struct->tangents[idx1] *= -1.0f;
		}

		//second
		vbo_struct->tangents[idx2] = vbo_struct->tangents[idx2] - nor2 * geometryf::dot(nor2, vbo_struct->tangents[idx2]);
		geometryf::normalize( &(vbo_struct->tangents[idx2]) );
		if (geometryf::dot(geometryf::cross(nor2, vbo_struct->tangents[idx2]), vbo_struct->binormals[idx2]) < 0.0f)
		{
			vbo_struct->tangents[idx2] *= -1.0f;
		}

		//third
		vbo_struct->tangents[idx3] = vbo_struct->tangents[idx3] - nor3 * geometryf::dot(nor3, vbo_struct->tangents[idx3]);
		geometryf::normalize( &(vbo_struct->tangents[idx3]) );
		if (geometryf::dot(geometryf::cross(nor3, vbo_struct->tangents[idx3]), vbo_struct->binormals[idx3]) < 0.0f)
		{
			vbo_struct->tangents[idx3] *= -1.0f;
		}
	}
}

} //lib namespace
