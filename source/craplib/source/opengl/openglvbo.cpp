////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglvbo.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief vbo data
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "math/vector3.h"
#include "math/vector2.h"

#include "opengl/openglvbo.h"

//lib namespace
namespace crap
{

//ogl namespace
namespace opengl
{

simple_vbo::simple_vbo( void ) : index_size(0), vertices_size(0), indices(0), positions(0), uvs(0), normals(0) {}

simple_vbo::~simple_vbo( void )
{
	delete[] indices;
	delete[] positions;
	delete[] uvs;
	delete[] normals;
}

vbo::vbo( void ) : index_size(0), vertices_size(0), indices(0), positions(0), uvs(0), normals(0), tangents(0), binormals(0) {}

vbo::~vbo( void )
{
	delete[] indices;
	delete[] positions;
	delete[] uvs;
	delete[] normals;
	delete[] tangents;
	delete[] binormals;
}

} // ogl namespace

} //namespace crap