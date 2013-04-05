
#include <algorithm>

#include "precompiled.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/geometry.h"
#include "container/fixedstring.h"
#include "files/file.h"
#include "memory/memorypool.h"
#include "geometrycontent.h"
#include "geometryfile.h"


geometry_file::geometry_file( const crap::string256& filename, file_type type, crap::memory_pool* pool ) : _vertices_index(0), _uvs_index(0), _normals_index(0), 
	_face_index(0), _group_index(0), _material_index(0), _vertices(0), _uvs(0), _normals(0), _faces(0), _groups(0), _material_groups(0), _content_pool(pool)
{
	if( type == wavefront )
		load_wavefront( filename );
}

geometry_file::~geometry_file( void )
{
	_content_pool->deallocate(_vertices);
	_content_pool->deallocate(_uvs);
	_content_pool->deallocate(_normals);
	_content_pool->deallocate(_faces);
	_content_pool->deallocate(_groups);
	_content_pool->deallocate(_material_groups);
}

crap::vector3f* geometry_file::vertices( void ) const
{
	return _vertices;
}

crap::vector2f* geometry_file::uvs( void ) const
{
	return _uvs;
}

crap::vector3f* geometry_file::normals( void ) const
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

void geometry_file::load_wavefront( const crap::string256& filename )
{
	crap::file obj_file( DATA_PATH + filename );
	size_t32 file_size = (size_t32)obj_file.size();
	u8* buffer = (u8*) _content_pool->allocate( file_size );
	obj_file.read_bytes( buffer, file_size );
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
		_vertices = (crap::vector3f*)_content_pool->allocate( _vertices_index * sizeof(crap::vector3f) );

	if( _uvs_index != 0 )
		_uvs = (crap::vector2f*)_content_pool->allocate( _uvs_index * sizeof(crap::vector2f) );

	if( _normals_index != 0 )
		_normals = (crap::vector3f*)_content_pool->allocate( _normals_index * sizeof(crap::vector3f) );

	if( _face_index != 0 )
		_faces = (face*)_content_pool->allocate( _face_index * sizeof(face) );

	if( _group_index != 0 )
		_groups = (group*)_content_pool->allocate( _group_index * sizeof(group) );

	if( _material_index != 0 )
		_material_groups = (material_group*)_content_pool->allocate( _material_index * sizeof(material_group) );

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
						crap::vector2f uv_vec;
						sscanf( (const char*)buffer+i+3, "%f %f", &uv_vec.x, &uv_vec.y );
						_uvs[ count_uvs++ ] = uv_vec;
					}
					else if( buffer[ i+1 ] == 'n' )
					{
						crap::vector3f norm_vec;
						sscanf( (const char*)buffer+i+3, "%f %f %f", &norm_vec.x, &norm_vec.y, &norm_vec.z );
						_normals[ count_normals++ ] = norm_vec;
					}
					else if( buffer[ i+1 ] == ' ' )
					{
						crap::vector3f vert_vec;
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

void geometry_file::create_geometry_content( geometry_content* createme )
{
	struct simple_vertex_index
	{
		i16 index;
		i32 position;
		i32 uv;
		i32 normal;

		b8 operator==( const simple_vertex_index& other )
		{
			return position == other.position && uv == other.uv && normal == other.normal;
		}
	};


	crap::vector<simple_vertex_index> vertex_list;
	crap::vector<u16> index_list;

	i32 index = 0;
	for(u32 i=0; i< _face_index; ++i)
	{
		for(u32 j=0; j<3; ++j)
		{
			simple_vertex_index ind;
			ind.position = _faces[i].vertices[j];
			ind.uv = _faces[i].uvs[j];
			ind.normal = _faces[i].normals[j];

			crap::vector<simple_vertex_index>::iterator find_iterator = std::find(vertex_list.begin(), vertex_list.end(), ind);
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

	createme->indices_size = index_list.size();
	createme->vertices_size = vertex_list.size();
	createme->indices = (u16*) _content_pool->allocate( index_list.size()* sizeof(u16) );
	createme->positions = (crap::vector3f*) _content_pool->allocate( vertex_list.size()* sizeof(crap::vector3f) );
	createme->uvs = (crap::vector2f*) _content_pool->allocate( vertex_list.size()* sizeof(crap::vector2f) );
	createme->normals = (crap::vector3f*) _content_pool->allocate( vertex_list.size()* sizeof(crap::vector3f) );

	index = 0;
	for( crap::vector<u16>::iterator it = index_list.begin(); it != index_list.end(); ++it )
	{
		createme->indices[index++] = *it;
	}

	index = 0;
	crap::vector<simple_vertex_index>::iterator it = vertex_list.begin();
	for( it; it != vertex_list.end(); ++it )
	{
		createme->positions[index] = _vertices[ it->position -1 ];
		createme->uvs[index] = _uvs[ it->uv -1 ];
		createme->normals[index++] = _normals[ it->normal -1 ];
	}



	createme->tangents = (crap::vector3f*) _content_pool->allocate( vertex_list.size()* sizeof(crap::vector3f) );
	createme->binormals = (crap::vector3f*) _content_pool->allocate( vertex_list.size()* sizeof(crap::vector3f) );

	for( u32 i=0; i< createme->indices_size; i+=3 )
	{
		u32 idx1 = createme->indices[i];
		u32 idx2 = createme->indices[i+1];
		u32 idx3 = createme->indices[i+2];

		crap::vector3f& pos1 = createme->positions[idx1];
		crap::vector3f& pos2 = createme->positions[idx2];
		crap::vector3f& pos3 = createme->positions[idx3];

		crap::vector2f& uv1 = createme->uvs[idx1];
		crap::vector2f& uv2 = createme->uvs[idx2];
		crap::vector2f& uv3 = createme->uvs[idx3];

		crap::vector3f& nor1 = createme->normals[idx1];
		crap::vector3f& nor2 = createme->normals[idx2];
		crap::vector3f& nor3 = createme->normals[idx3];

		// Edges of the triangle : postion delta
		crap::vector3f delta_pos1 = pos2-pos1;
		crap::vector3f delta_pos2 = pos3-pos1;

		// UV delta
		crap::vector2f delta_uv1 = uv2-uv1;
		crap::vector2f delta_uv2 = uv3-uv1;

		f32 r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
		createme->tangents[idx1] = (delta_pos1 * delta_uv2.y - delta_pos2 * delta_uv1.y)*r;
		createme->binormals[idx1] = (delta_pos2 * delta_uv1.x - delta_pos1 * delta_uv2.x)*r;
		createme->tangents[idx2] = createme->tangents[idx1];
		createme->binormals[idx2] = createme->binormals[idx1];
		createme->tangents[idx3] = createme->tangents[idx1];
		createme->binormals[idx3] = createme->binormals[idx1];

		//first
		createme->tangents[idx1] = createme->tangents[idx1] - nor1 * crap::geometryf::dot(nor1, createme->tangents[idx1]);
		crap::geometryf::normalize( &(createme->tangents[idx1]) );
		if (crap::geometryf::dot( crap::geometryf::cross(nor1, createme->tangents[idx1]), createme->binormals[idx1]) < 0.0f)
		{
			createme->tangents[idx1] *= -1.0f;
		}

		//second
		createme->tangents[idx2] = createme->tangents[idx2] - nor2 * crap::geometryf::dot(nor2, createme->tangents[idx2]);
		crap::geometryf::normalize( &(createme->tangents[idx2]) );
		if (crap::geometryf::dot( crap::geometryf::cross(nor2, createme->tangents[idx2]), createme->binormals[idx2]) < 0.0f)
		{
			createme->tangents[idx2] *= -1.0f;
		}

		//third
		createme->tangents[idx3] = createme->tangents[idx3] - nor3 * crap::geometryf::dot(nor3, createme->tangents[idx3]);
		crap::geometryf::normalize( &(createme->tangents[idx3]) );
		if (crap::geometryf::dot(crap::geometryf::cross(nor3, createme->tangents[idx3]), createme->binormals[idx3]) < 0.0f)
		{
			createme->tangents[idx3] *= -1.0f;
		}
	}
}