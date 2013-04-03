////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglvbo.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief vbo data
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_OPENGL_VBO_H
#define CRAP_OPENGL_VBO_H

//lib namespace
namespace crap
{

template<typename T> struct vector3;
template<typename T> struct vector2;
typedef vector3<f32> vector3f;
typedef vector2<f32> vector2f;

namespace opengl
{

struct simple_vbo
{
	size_t32 index_size;
	size_t32 vertices_size;
	u16* indices;
	vector3f* positions;
	vector2f* uvs;
	vector3f* normals;

	simple_vbo( void );
	~simple_vbo( void );
};

struct vbo
{
	size_t32 index_size;
	size_t32 vertices_size;
	u16* indices;
	vector3f* positions;
	vector2f* uvs;
	vector3f* normals;
	vector3f* tangents;
	vector3f* binormals;

	vbo( void );
	~vbo( void );
};

} // namespace vbo

} //namespace crap

#endif //CRAP_OPENGL_VBO_H