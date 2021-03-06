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
#include "container/fixedstring.h"
#include "files/file.h"
#include "files/geometryfile.h"

//lib namespace
namespace crap
{

geometry_file::geometry_file( const string256& filename, file_type type ) : _vertices_index(0), _uvs_index(0), _normals_index(0), 
	_face_index(0), _group_index(0), _material_index(0), _vertices(0), _uvs(0), _normals(0), _faces(0), _groups(0), _material_groups(0)
{
	if( type == wavefront )
		load_wavefront( filename );
}

geometry_file::~geometry_file( void )
{
	delete[] _vertices;
	delete[] _uvs;
	delete[] _normals;
	delete[] _faces;
	delete[] _groups;
	delete[] _material_groups;
}

vector3f* geometry_file::vertices( void ) const
{
	return _vertices;
}

vector2f* geometry_file::uvs( void ) const
{
	return _uvs;
}

vector3f* geometry_file::normals( void ) const
{
	return _normals;
}

geometry_file::face* geometry_file::faces( void ) const
{
	return _faces;
}


geometry_file::group* geometry_file::groups( void ) const
{
	return _groups;
}

geometry_file::material_group* geometry_file::material_groups( void ) const
{
	return _material_groups;
}

u32 geometry_file::vertices_index( void ) const
{
	return _vertices_index;
}

u32 geometry_file::uvs_index( void ) const
{
	return _uvs_index;
}
u32 geometry_file::normals_index( void ) const
{
	return _normals_index;
}

u32 geometry_file::face_index( void ) const
{
	return _face_index;
}

u32 geometry_file::group_index( void ) const
{
	return _group_index;
}

u32 geometry_file::material_index( void ) const
{
	return _material_index;
}

void geometry_file::load_wavefront( const string256& filename )
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

} //namespace crap