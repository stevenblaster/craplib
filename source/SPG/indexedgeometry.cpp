#include "precompiled.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "indexgeometry.h"

indexed_geometry::indexed_geometry( void ) : indices_size(0), vertices_size(0), indices(0),
	positions(0), uvs(0), normals(0), tangents(0), binormals(0)
{

}

indexed_geometry::~indexed_geometry( void )
{
	delete[] indices;
	delete[] positions;
	delete[] uvs;
	delete[] normals;
	delete[] tangents;
	delete[] binormals;
}