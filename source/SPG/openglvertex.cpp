////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglvertex.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief vertex info
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "math/vector3.h"
#include "math/vector2.h"
#include "opengl/openglvertex.h"

//lib namespace
namespace crap
{

//ogl namespace
namespace opengl
{

template<typename T>
b8 simple_vertex<T>::operator<( const simple_vertex& other )
{
	return position < other.position && uv < other.uv && normal < other.normal;
}

template<typename T>
b8 simple_vertex<T>::operator==( const simple_vertex& other )
{
	return position == other.position && uv == other.uv && normal == other.normal;
}

template<typename T>
b8 vertex<T>::operator<( const vertex& other )
{
	return position < other.position && uv < other.uv && normal < other.normal && tangent < other.tangent && binormal < other.binormal;
}

template<typename T>
b8 vertex<T>::operator==( const vertex& other )
{
	return position == other.position && uv == other.uv && normal == other.normal && tangent == other.tangent && binormal == other.binormal;
}


b8 simple_vertex_index::operator<( const simple_vertex_index& other )
{
    return position < other.position && uv < other.uv && normal < other.normal;
    //return index < other.index;
}

b8 simple_vertex_index::operator==( const simple_vertex_index& other )
{
	return position == other.position && uv == other.uv && normal == other.normal;
}

b8 simple_vertex_index::operator!=( const simple_vertex_index& other )
{
    return !(*this == other);
}

b8 vertex_index::operator<( const vertex_index& other )
{
    return position < other.position && uv < other.uv && normal < other.normal && tangent < other.tangent && binormal < other.binormal;
    //return index < other.index;
}

b8 vertex_index::operator==( const vertex_index& other )
{
	return position == other.position && uv == other.uv && normal == other.normal && tangent == other.tangent && binormal == other.binormal;
}

b8 vertex_index::operator!=( const vertex_index& other )
{
    return !(*this == other);
}

} //ogl namespace

} //crap namespace
