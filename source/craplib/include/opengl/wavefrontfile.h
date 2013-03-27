////////////////////////////////////////////////////////
// CRAP Library
//!		@file wavefrontfile.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief parses a wavefront obj file
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_OPENGL_WAVEFRONFILE_H
#define CRAP_OPENGL_WAVEFRONFILE_H

//lib namespace
namespace crap
{

class wavefront_file
{
public:

	struct face
	{
		i32 vertices[3];
		i32 uvs[3];
		i32 normals[3];

		face( void )
		{
			vertices[0] = 0; vertices[1] = 0; vertices[2] = 0;
			uvs[0] = 0; uvs[1] = 0; uvs[2] = 0;
			normals[0] = 0; normals[1] = 0; normals[2] = 0;
		}

		face& operator=( const face& other)
		{
			vertices[0] = other.vertices[0];
			vertices[1] = other.vertices[1];
			vertices[2] = other.vertices[2];

			uvs[0] = other.uvs[0];
			uvs[1] = other.uvs[1];
			uvs[2] = other.uvs[2];

			normals[0] = other.normals[0];
			normals[1] = other.normals[1];
			normals[2] = other.normals[2];

			return *this;
		}
	};

	struct group
	{
		i32 index_start;
		i32 index_end;

		group( void ) : index_start(-1), index_end(-1) {}

		group& operator=( const group& other )
		{
			index_start = other.index_start;
			index_end = other.index_end;

			return *this;
		}
	};

	typedef group material_group;

	wavefront_file( string256 filename );
	~wavefront_file( void );

	vector3f* vertices( void ) const;
	vector2f* uvs( void ) const;
	vector3f* normals( void ) const;

	face* faces( void ) const;
	group* groups( void ) const;
	material_group* material_groups( void ) const;

	u32 vertices_index( void ) const;
	u32 uvs_index( void ) const;
	u32 normals_index( void ) const;
	u32 face_index( void ) const;
	u32 group_index( void ) const;
	u32 material_index( void ) const;

private:
	
	vector3f* _vertices;
	vector2f* _uvs;
	vector3f* _normals;

	face* _faces;
	group* _groups;
	material_group* _material_groups;

	u32 _vertices_index;
	u32 _uvs_index;
	u32 _normals_index;
	u32 _face_index;
	u32 _group_index;
	u32 _material_index;
};

} //lib namespace

#endif // CRAP_OPENGL_WAVEFRONFILE_H