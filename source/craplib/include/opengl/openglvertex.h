////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglvertex.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief vertex info
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_OPENGL_OPENGLVERTEX_H
#define CRAP_OPENGL_OPENGLVERTEX_H

//lib namespace
namespace crap
{

template<typename T> struct vector3;
template<typename T> struct vector2;

namespace opengl
{

template<typename T>
struct simple_vertex
{
	vector3<T> position;
	vector2<T> uv;
	vector3<T> normal;

	b8 operator<( const simple_vertex& other );
	b8 operator==( const simple_vertex& other );
};

template<typename T>
struct vertex : public simple_vertex<T>
{
	vector3<T> tangent;
	vector3<T> binormal;

	b8 operator<( const vertex& other );
	b8 operator==( const vertex& other );
};

struct simple_vertex_index
{
	i16 index;
	i32 position;
	i32 uv;
	i32 normal;

	b8 operator<( const simple_vertex_index& other );
	b8 operator==( const simple_vertex_index& other );
};

struct vertex_index : simple_vertex_index
{
	i32 tangent;
	i32 binormal;

	b8 operator<( const vertex_index& other );
	b8 operator==( const vertex_index& other );
};

} // namespace opengl

} // namespace crap

#endif //CRAP_OPENGL_OPENGLVERTEX_H