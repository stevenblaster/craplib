#pragma once

#ifndef GEOMETRYCONTENT_H
#define GEOMETRYCONTENT_H

//predeclare
namespace crap
{
template<typename T> struct vector3;
template<typename T> struct vector2;
typedef vector3<f32> vector3f;
typedef vector2<f32> vector2f;
}

struct geometry_content
{
	size_t32 indices_size;
	size_t32 vertices_size;

	u16* indices;
	crap::vector3f* positions;
	crap::vector2f* uvs;
	crap::vector3f* normals;
	crap::vector3f* tangents;
	crap::vector3f* binormals;

	geometry_content( void );
};

#endif //GEOMETRYCONTENT_H