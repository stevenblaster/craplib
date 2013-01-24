////////////////////////////////////////////////////////
// CRAP Library
//!		@file geometry.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Geometry functions/methods for matrices
//		and vectors
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_GEOMETRY_GEOMETRY_H
#define CRAP_GEOMETRY_GEOMETRY_H

#include "geometry/matrix2.h"
#include "geometry/matrix3.h"
#include "geometry/matrix4.h"

#include "geometry/vector2.h"
#include "geometry/vector3.h"
#include "geometry/vector4.h"

#include "control/zero.h"
#include "math/math.h"

//lib namespace
namespace crap
{

template<typename T>
class geometry
{
public:

	/*
	 * Create matrices
	 */

	//! @brief create zero'd matrix 2d
	static const CRAP_INLINE
	matrix3<T>& zero_matrix3( matrix3<T>* matrix );

	//! @brief create zero'd matrix 3d
	static const CRAP_INLINE
	matrix4<T>& zero_matrix4( matrix4<T>* matrix );

	//! @brief create identyty matrix 2d
	static const CRAP_INLINE
	matrix3<T>& identity_matrix3( matrix3<T>* matrix );

	//! @brief create identyty matrix 3d
	static const CRAP_INLINE
	matrix4<T>& identity_matrix4( matrix4<T>* matrix );

	//! @brief create translation matrix with existing matrix 2d
	static const CRAP_INLINE 
	matrix3<T>& translation_matrix3( matrix3<T>* matrix, const vector2<T>& vector );

	//! @brief create translation matrix with existing matrix 3d
	static const CRAP_INLINE 
	matrix4<T>& translation_matrix4( matrix4<T>* matrix, const vector3<T>& vector );

	//! @brief create rotation matrix with existing matrix 2d, angles in rad
	static const CRAP_INLINE 
	matrix3<T>& rotation_matrix3( matrix3<T>* matrix, const vector2<T>& vector );

	//! @brief create rotation matrix with existing matrix 3d, angles in rad
	static const CRAP_INLINE 
	matrix4<T>& rotation_matrix4( matrix4<T>* matrix, const vector3<T>& vector );

};	// class geometry

/*
 * Definitions
 */

// create zero'd matrix 2d
template<typename T>
const matrix3<T>& zero_matrix3( matrix3<T>* matrix )
{
	memset( matrix, crap::zero<T>::VALUE, sizeof( *matrix ) );
	return *matrix;
}

// create zero'd matrix 3d
template<typename T>
const matrix4<T>& zero_matrix4( matrix4<T>* matrix )
{
	memset( matrix, crap::zero<T>::VALUE, sizeof( *matrix ) );
	return *matrix;
}

// create identyty matrix 2d
template<typename T>
const matrix3<T>& geometry<T>::identity_matrix3( matrix3<T>* matrix )
{
	memset( matrix, crap::zero<T>::VALUE, sizeof( *matrix ) );

	matrix->xx = 1;
	matrix->yy = 1;
	matrix->zz = 1;

	return *matrix;
}

// create identyty matrix 3d
template<typename T>
const matrix4<T>& geometry<T>::identity_matrix4( matrix4<T>* matrix )
{
	memset( matrix, crap::zero<T>::VALUE, sizeof( *matrix ) );

	matrix->xx = 1;
	matrix->yy = 1;
	matrix->zz = 1;
	matrix->ww = 1;

	return *matrix;
}


//create 2D translation matrix with existing matrix
template<typename T>
const matrix3<T>& geometry<T>::translation_matrix3( matrix3<T>* matrix, const vector2<T>& vector )
{
	identity_matrix3( &matrix );

	mat->xw = vector.x;
	mat->yw = vector.y;

	return *matrix;
}

//create 3D translation matrix with existing matrix
template<typename T>
const matrix4<T>& geometry<T>::translation_matrix4( matrix4<T>* matrix, const vector3<T>& vector )
{
	identity_matrix4( &matrix );

	mat->xw = vector.x;
	mat->yw = vector.y;
	mat->zw = vector.z;

	return *matrix;
}

//! create rotation matrix with existing matrix 2d
template<typename T>
const matrix3<T>& rotation_matrix3( matrix3<T>* matrix, const vector2<T>& vector )
{
	identity_matrix3( &matrix );
	matrix->xx = crap::math::cos(vector.x);
	matrix->xy = -crap::math::sin(vector.x);
	matrix->yx = crap::math::sin(vector.x);
	matrix->xy = crap::math::cos(vector.x);

	return *matrix;
}

//! create rotation matrix with existing matrix 3d
template<typename T>
const matrix4<T>& rotation_matrix4( matrix4<T>* matrix, const vector3<T>& vector )
{
	matrix4<T> x_matrix;
	matrix4<T> y_matrix;
	matrix4<T> z_matrix;

	identity_matrix4( &x_matrix );
	x_matrix.yy = crap::math::cos(vector.x);
	x_matrix.yz = -crap::math::sin(vector.x);
	x_matrix.zy = crap::math::sin(vector.x);
	x_matrix.zz = crap::math::cos(vector.x);

	identity_matrix4( &y_matrix );
	y_matrix.xx = crap::math::cos(vector.y);
	y_matrix.zx = -crap::math::sin(vector.y);
	y_matrix.xz = crap::math::sin(vector.y);
	y_matrix.zz = crap::math::cos(vector.y);

	identity_matrix4( &z_matrix );
	z_matrix.xx = crap::math::cos(vector.z);
	z_matrix.xy = -crap::math::sin(vector.z);
	z_matrix.yx = crap::math::sin(vector.z);
	z_matrix.yy = crap::math::cos(vector.z);

	*matrix = x_matrix * y_matrix * z_matrix;
	return *matrix;
}

} // namespace crap

#endif // CRAP_GEOMETRY_GEOMETRY_H