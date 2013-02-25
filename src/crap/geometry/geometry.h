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

	//! @brief dot product of vector2
	static const CRAP_INLINE
	T dot( const vector2<T>& left, const vector2<T>& right );

	//! @brief dot product of vector3
	static const CRAP_INLINE
	T dot( const vector3<T>& left, const vector3<T>& right );

	//! @brief dot product of vector4
	static const CRAP_INLINE
	T dot( const vector4<T>& left, const vector4<T>& right );

	//! @brief cross product of vector2
	static const CRAP_INLINE
	vector2<T> cross( const vector2<T>& vec2 );

	//! @brief cross product of vector2
	static const CRAP_INLINE
	T cross( const vector2<T>& left, const vector2<T>& right );

	//! @brief cross product of vector3
	static const CRAP_INLINE
	vector3<T> cross( const vector3<T>& left, const vector3<T>& right );

	//! @brief normalize vector2
	static const CRAP_INLINE
	vector2<T>& normalize( vector2<T>* vec2 );

	//! @brief normalize vector3
	static const CRAP_INLINE
	vector3<T>& normalize( vector3<T>* vec3 );

	//! @brief normalize vector4
	static const CRAP_INLINE
	vector4<T>& normalize( vector4<T>* vec4 );

	//! @brief lenght vector2
	static const CRAP_INLINE
	T lenght( const vector2<T>& vec2 );

	//! @brief lenght vector3
	static const CRAP_INLINE
	T lenght( const vector3<T>& vec3 );

	//! @brief lenght vector4
	static const CRAP_INLINE
	T lenght( const vector4<T>& vec4 );

	//! @brief euler to quaternion
	static const CRAP_INLINE
	quaternion<T> euler_to_quaternion( const vector3<T>& euler_angles );

	//! @brief quaternion linear interpolation
	static const CRAP_INLINE
	quaternion<T> quaternion_lerp( const quaternion<T>& quat1, const quaternion<T>& quat2, T t );

	//! @brief quaternion spherical linear interpolation
	static const CRAP_INLINE
	quaternion<T> quaternion_slerp( const quaternion<T>& quat1, const quaternion<T>& quat2, T t );

	//! @brief quaternion spherical linear interpolation, no checking for angle
	static const CRAP_INLINE
	quaternion<T> quaternion_slerp_no_invert( const quaternion<T>& quat1, const quaternion<T>& quat2, T t );

	//! @brief quaternion spherical cubic linear interpolation
	static const CRAP_INLINE
	quaternion<T> quaternion_squad( const quaternion<T>& quat1, const quaternion<T>& quat2, const quaternion<T>& quat3, const quaternion<T>& quat4, T t );

	//! @brief quaternion bezier interpolation
	static const CRAP_INLINE
	quaternion<T> quaternion_bezier( const quaternion<T>& quat1, const quaternion<T>& quat2, const quaternion<T>& quat3, const quaternion<T>& quat4, T t );

	//! @brief quaternion to euler
	static const CRAP_INLINE
	vector3<T> quaternion_to_euler( const quaternion<T>& quat, b8 homogenous = true );

};	// class geometry

/*
 * Definitions
 */

// create zero'd matrix 2d
template<typename T>
const matrix3<T>& geometry<T>::zero_matrix3( matrix3<T>* matrix )
{
    memset( matrix, 0, sizeof( *matrix ) );
    return *matrix;
}

// create zero'd matrix 3d
template<typename T>
const matrix4<T>& geometry<T>::zero_matrix4( matrix4<T>* matrix )
{
    memset( matrix, 0, sizeof( *matrix ) );
    return *matrix;
}

// create identyty matrix 2d
template<typename T>
const matrix3<T>& geometry<T>::identity_matrix3( matrix3<T>* matrix )
{
    memset( matrix, 0, sizeof( *matrix ) );

    matrix->xx = 1;
    matrix->yy = 1;
    matrix->zz = 1;

    return *matrix;
}

// create identyty matrix 3d
template<typename T>
const matrix4<T>& geometry<T>::identity_matrix4( matrix4<T>* matrix )
{
    memset( matrix, 0, sizeof( *matrix ) );

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
    identity_matrix3( matrix );

    matrix->xz = vector.x;
    matrix->yz = vector.y;

    return *matrix;
}

//create 3D translation matrix with existing matrix
template<typename T>
const matrix4<T>& geometry<T>::translation_matrix4( matrix4<T>* matrix, const vector3<T>& vector )
{
    identity_matrix4( matrix );

    matrix->xw = vector.x;
    matrix->yw = vector.y;
    matrix->zw = vector.z;

    return *matrix;
}

//! create rotation matrix with existing matrix 2d
template<typename T>
const matrix3<T>& geometry<T>::rotation_matrix3( matrix3<T>* matrix, const vector2<T>& vector )
{
    identity_matrix3( matrix );
    matrix->xx = crap::math<T>::cos(vector.x);
    matrix->xy = -crap::math<T>::sin(vector.x);
    matrix->yx = crap::math<T>::sin(vector.x);
    matrix->yy = crap::math<T>::cos(vector.x);

    return *matrix;
}

//! create rotation matrix with existing matrix 3d
template<typename T>
const matrix4<T>& geometry<T>::rotation_matrix4( matrix4<T>* matrix, const vector3<T>& vector )
{
    matrix4<T> x_matrix;
    matrix4<T> y_matrix;
    matrix4<T> z_matrix;

    identity_matrix4( &x_matrix );
    x_matrix.yy = crap::math<T>::cos(vector.x);
    x_matrix.yz = -crap::math<T>::sin(vector.x);
    x_matrix.zy = crap::math<T>::sin(vector.x);
    x_matrix.zz = crap::math<T>::cos(vector.x);

    identity_matrix4( &y_matrix );
    y_matrix.xx = crap::math<T>::cos(vector.y);
    y_matrix.zx = -crap::math<T>::sin(vector.y);
    y_matrix.xz = crap::math<T>::sin(vector.y);
    y_matrix.zz = crap::math<T>::cos(vector.y);

    identity_matrix4( &z_matrix );
    z_matrix.xx = crap::math<T>::cos(vector.z);
    z_matrix.xy = -crap::math<T>::sin(vector.z);
    z_matrix.yx = crap::math<T>::sin(vector.z);
    z_matrix.yy = crap::math<T>::cos(vector.z);

    *matrix = x_matrix * y_matrix * z_matrix;
    return *matrix;
}

//! dot product of vector2
template<typename T>
const T geometry<T>::dot( const vector2<T>& left, const vector2<T>& right )
{
	vector2<T> tmp = left * right;
	return tmp.x + tmp.y;
}

//! dot product of vector3
template<typename T>
const T geometry<T>::dot( const vector3<T>& left, const vector3<T>& right )
{
	vector3<T> tmp = left * right;
	return tmp.x + tmp.y + tmp.z;
}

//! dot product of vector4
template<typename T>
const T geometry<T>::dot( const vector4<T>& left, const vector4<T>& right )
{
	vector4<T> tmp = left * right;
	return tmp.x + tmp.y + tmp.z + tmp.w;
}

//! cross product of vector2
template<typename T>
const vector2<T> geometry<T>::cross( const vector2<T>& vec2 )
{
	return vector2<T>(vec2.y, -vec2.x);
}

//! cross product of vector2
template<typename T>
const T geometry<T>::cross( const vector2<T>& left, const vector2<T>& right )
{
	return left.x * right.y - left.y * right.x;
}

//! cross product of vector3
template<typename T>
const vector3<T> geometry<T>::cross( const vector3<T>& left, const vector3<T>& right )
{
	vector3<T> result;

	result.x = left.y * right.z - left.z * right.y;
	result.y = left.z * right.x - left.x * right.z;
	result.z = left.x * right.y - left.y * right.x;

	return result;
}

//! normalize vector2
template<typename T>
const vector2<T>& geometry<T>::normalize( vector2<T>* vec2 )
{
	T len = lenght( *vec2 );

	vec2->x /= len;
	vec2->y /= len;

	return *vec2;
}

//! normalize vector3
template<typename T>
const vector3<T>& geometry<T>::normalize( vector3<T>* vec3 )
{
	T len = lenght( *vec3 );

	vec3->x /= len;
	vec3->y /= len;
	vec3->z /= len;

	return *vec3;
}

//! normalize vector4
template<typename T>
const vector4<T>& geometry<T>::normalize( vector4<T>* vec4 )
{
	T len = lenght( *vec4 );

	vec4->x /= len;
	vec4->y /= len;
	vec4->z /= len;
	vec4->w /= len;

	return *vec4;
}

//! lenght vector2
template<typename T>
const T geometry<T>::lenght( const vector2<T>& vec2 )
{
	return crap::math<T>::sqrt( vec2.x*vec2.x + vec2.y*vec2.y );
}

//! lenght vector3
template<typename T>
const T geometry<T>::lenght( const vector3<T>& vec3 )
{
	return crap::math<T>::sqrt( vec3.x*vec3.x + vec3.y*vec3.y + vec3.z*vec3.z );
}

//! lenght vector4
template<typename T>
const T geometry<T>::lenght( const vector4<T>& vec4 )
{
	return crap::math<T>::sqrt( vec4.x*vec4.x + vec4.y*vec4.y + vec4.z*vec4.z + vec4.w*vec4.w );
}

//! euler to quaternion
template<typename T>
const quaternion<T> geometry<T>::euler_to_quaternion( const vector3<T>& euler_angles )
{
	quaternion<T> result;
	vector3<T> tmp = euler_angles;
	tmp *= 0.5f;

	result.x = ( crap::math<T>::sin( tmp.x ) * crap::math<T>::cos( tmp.y ) * crap::math<T>::cos( tmp.z ) );
	result.x -= ( crap::math<T>::cos( tmp.x ) * crap::math<T>::sin( tmp.y ) * crap::math<T>::sin( tmp.z ) );

	result.y = ( crap::math<T>::cos( tmp.x ) * crap::math<T>::sin( tmp.y ) * crap::math<T>::cos( tmp.z ) );
	result.y += ( crap::math<T>::sin( tmp.x ) * crap::math<T>::cos( tmp.y ) * crap::math<T>::sin( tmp.z ) );

	result.z = ( crap::math<T>::cos( tmp.x ) * crap::math<T>::cos( tmp.y ) * crap::math<T>::sin( tmp.z ) );
	result.z -= ( crap::math<T>::sin( tmp.x ) * crap::math<T>::sin( tmp.y ) * crap::math<T>::cos( tmp.z ) );

	result.w = ( crap::math<T>::cos( tmp.x ) * crap::math<T>::cos( tmp.y ) * crap::math<T>::cos( tmp.z ) );
	result.w += ( crap::math<T>::sin( tmp.x ) * crap::math<T>::sin( tmp.y ) * crap::math<T>::sin( tmp.z ) );

	return result;
}

//! quaternion linear interpolation
template<typename T>
const quaternion<T> geometry<T>::quaternion_lerp( const quaternion<T>& quat1, const quaternion<T>& quat2, T t )
{
	quaternion<T> result = quat1 * (1-t) + quat2 * t;
	return normalize( &result );
}

//! quaternion spherical linear interpolation
template<typename T>
const quaternion<T> geometry<T>::quaternion_slerp( const quaternion<T>& quat1, const quaternion<T>& quat2, T t )
{
	quaternion<T> result;
	f32 dot_quat = dot(quat1, quat2);

	if (dot_quat < 0)
	{
		dot_quat = -dot_quat;
		result = -quat2;
	} 
	else 
		result = quat2;

	if (dot < (T) 0.95f)
	{
		f32 angle = crap::math<T>::acos(dot);
		result = quat1 * crap::math<T>::sin( angle * (1-t) ) + result * crap::math<T>::sin( angle * t );
		result /= crap::math<T>::sin( angle );
	} 
	else 
		result = lerp(q1,q3,t);	

	return result;
}

//! quaternion spherical linear interpolation, no checking for angle
template<typename T>
const quaternion<T> geometry<T>::quaternion_slerp_no_invert( const quaternion<T>& quat1, const quaternion<T>& quat2, T t )
{
	quaternion<T> result;
	float dot_quat = dot(q1, q2);

	if (dot_quat > (T) -0.95f && dot_quat < (T) 0.95f)
	{
		f32 angle = crap::math<T>::acos(dot);	
		result = quat1 * crap::math<T>::sin( angle * (1-t) ) + quat2 * crap::math<T>::sin( angle * t );
		result /= crap::math<T>::sin( angle );
	}
	else 
		result = lerp(q1,q3,t);	

	return result;
}

//! quaternion spherical cubic linear interpolation
template<typename T>
const quaternion<T> geometry<T>::quaternion_squad( const quaternion<T>& quat1, const quaternion<T>& quat2, const quaternion<T>& quat3, const quaternion<T>& quat4, T t )
{
	quaternion<T> tmp1 = quaternion_slerp_no_invert( quat1, quat2, t );
	quaternion<T> tmp2 = quaternion_slerp_no_invert( quat3, quat4, t );	
	return quaternion_slerp_no_invert( tmp1, tmp2, 2*t*(1-t) );
}

//! quaternion bezier interpolation
template<typename T>
const quaternion<T> geometry<T>::quaternion_bezier( const quaternion<T>& quat1, const quaternion<T>& quat2, const quaternion<T>& quat3, const quaternion<T>& quat4, T t )
{
	// level 1
	quaternion<T> tmp1= quaternion_slerp_no_invert( quat1, quat3, t);
	quaternion<T> tmp2= quaternion_slerp_no_invert( quat3, quat4, t);
	quaternion<T> tmp3= quaternion_slerp_no_invert( quat4, quat2, t);

	//level 2
	quaternion<T> tmp4= quaternion_slerp_no_invert( tmp1, tmp2, t);
	quaternion<T> tmp5= quaternion_slerp_no_invert( tmp2, tmp3, t);

	// level 3
	return quaternion_slerp_no_invert( tmp4, tmp5, t);
}

//! quaternion to euler
template<typename T>
const vector3<T> geometry<T>::quaternion_to_euler( const quaternion<T>& quat, b8 homogenous /* = true */ )
{
	f32 square_x = quat.x * quat.x;
	f32 square_y = quat.y * quat.y;
	f32 square_z = quat.z * quat.z;
	f32 square_w = quat.w * quat.w;
	
	vector3<T> result;

	if (homogenous) 
	{
		result.x = crap::math<T>::atan2( 2.f * ( quat.x * quat.y + quat.z * quat.w ), square_x - square_y - square_z + square_w );
		result.y = crap::math<T>::asin( -2.f * ( quat.x * quat.z - quat.y * quat.w ));
		result.z = crap::math<T>::atan2( 2.f * ( quat.y * quat.z + quat.x * quat.w ), -square_x - square_y + square_z + square_w );
	} 
	else 
	{
		result.x = crap::math<T>::atan2( 2.f * ( quat.z * quat.y + quat.x * quat.w ), 1 - 2*(square_x + square_y) );
		result.y = crap::math<T>::asin( -2.f * ( quat.x * quat.z - quat.y * quat.w ));
		result.z = crap::math<T>::atan2( 2.f * ( quat.x * quat.y + quat.z * quat.w ), 1 - 2*(square_y + square_z) );
	}
	return result;
}

typedef geometry<i32> geometryi;
typedef geometry<i64> geometryl;
typedef geometry<f32> geometryf;
typedef geometry<f64> geometryd;

} // namespace crap

#endif // CRAP_GEOMETRY_GEOMETRY_H
