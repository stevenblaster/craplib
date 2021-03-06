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

#include "math/matrix2.h"
#include "math/matrix3.h"
#include "math/matrix4.h"

#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"

#include "control/zero.h"
#include "math/basemath.h"

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

	//! @brief create perspecive matrix with existing matrix 3d
    static const CRAP_INLINE
    matrix4<T>& perspective_matrix4( matrix4<T>* matrix, const T& fov_y, const T& aspect, const T& z_near, const T& z_far );

	//! @brief create perspecive matrix with existing matrix 3d
    static const CRAP_INLINE
    matrix4<T>& look_at_matrix4( matrix4<T>* matrix, const vector3<T>& position, const vector3<T>& direction, const vector3<T>& up_vector );

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
    matrix->xx = crap::basemath<T>::cos(vector.x);
    matrix->xy = -crap::basemath<T>::sin(vector.x);
    matrix->yx = crap::basemath<T>::sin(vector.x);
    matrix->yy = crap::basemath<T>::cos(vector.x);

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
    x_matrix.yy = crap::basemath<T>::cos(vector.x);
    x_matrix.yz = -crap::basemath<T>::sin(vector.x);
    x_matrix.zy = crap::basemath<T>::sin(vector.x);
    x_matrix.zz = crap::basemath<T>::cos(vector.x);

    identity_matrix4( &y_matrix );
    y_matrix.xx = crap::basemath<T>::cos(vector.y);
    y_matrix.zx = -crap::basemath<T>::sin(vector.y);
    y_matrix.xz = crap::basemath<T>::sin(vector.y);
    y_matrix.zz = crap::basemath<T>::cos(vector.y);

    identity_matrix4( &z_matrix );
    z_matrix.xx = crap::basemath<T>::cos(vector.z);
    z_matrix.xy = -crap::basemath<T>::sin(vector.z);
    z_matrix.yx = crap::basemath<T>::sin(vector.z);
    z_matrix.yy = crap::basemath<T>::cos(vector.z);

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
    return crap::basemath<T>::sqrt( vec2.x*vec2.x + vec2.y*vec2.y );
}

//! lenght vector3
template<typename T>
const T geometry<T>::lenght( const vector3<T>& vec3 )
{
    //return crap::basemath<T>::sqrt( vec3.x*vec3.x + vec3.y*vec3.y + vec3.z*vec3.z 
	return ::sqrt( vec3.x*vec3.x + vec3.y*vec3.y + vec3.z*vec3.z );
}

//! lenght vector4
template<typename T>
const T geometry<T>::lenght( const vector4<T>& vec4 )
{
    return crap::basemath<T>::sqrt( vec4.x*vec4.x + vec4.y*vec4.y + vec4.z*vec4.z + vec4.w*vec4.w );
}

//! euler to quaternion
template<typename T>
const quaternion<T> geometry<T>::euler_to_quaternion( const vector3<T>& euler_angles )
{
    quaternion<T> result;
    vector3<T> tmp = euler_angles;
    tmp *= T(0.5f);

    result.x = ( crap::basemath<T>::sin( tmp.x ) * crap::basemath<T>::cos( tmp.y ) * crap::basemath<T>::cos( tmp.z ) );
    result.x -= ( crap::basemath<T>::cos( tmp.x ) * crap::basemath<T>::sin( tmp.y ) * crap::basemath<T>::sin( tmp.z ) );

    result.y = ( crap::basemath<T>::cos( tmp.x ) * crap::basemath<T>::sin( tmp.y ) * crap::basemath<T>::cos( tmp.z ) );
    result.y += ( crap::basemath<T>::sin( tmp.x ) * crap::basemath<T>::cos( tmp.y ) * crap::basemath<T>::sin( tmp.z ) );

    result.z = ( crap::basemath<T>::cos( tmp.x ) * crap::basemath<T>::cos( tmp.y ) * crap::basemath<T>::sin( tmp.z ) );
    result.z -= ( crap::basemath<T>::sin( tmp.x ) * crap::basemath<T>::sin( tmp.y ) * crap::basemath<T>::cos( tmp.z ) );

    result.w = ( crap::basemath<T>::cos( tmp.x ) * crap::basemath<T>::cos( tmp.y ) * crap::basemath<T>::cos( tmp.z ) );
    result.w += ( crap::basemath<T>::sin( tmp.x ) * crap::basemath<T>::sin( tmp.y ) * crap::basemath<T>::sin( tmp.z ) );

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

    if (dot < T(0.95f))
    {
        f32 angle = crap::basemath<T>::acos(dot);
        result = quat1 * crap::basemath<T>::sin( angle * (1-t) ) + result * crap::basemath<T>::sin( angle * t );
        result /= crap::basemath<T>::sin( angle );
    }
    else
        result = lerp(quat1,result,t);

    return result;
}

//! quaternion spherical linear interpolation, no checking for angle
template<typename T>
const quaternion<T> geometry<T>::quaternion_slerp_no_invert( const quaternion<T>& quat1, const quaternion<T>& quat2, T t )
{
    quaternion<T> result;
    float dot_quat = dot(quat1, quat2);

    if (dot_quat >  T(-0.95f) && dot_quat < T(0.95f) )
    {
        T angle = crap::basemath<T>::acos(dot);
        result = quat1 * crap::basemath<T>::sin( angle * (1-t) ) + quat2 * crap::basemath<T>::sin( angle * t );
        result /= crap::basemath<T>::sin( angle );
    }
    else
        result = lerp(quat1,quat2,t);

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
    T square_x = quat.x * quat.x;
    T square_y = quat.y * quat.y;
    T square_z = quat.z * quat.z;
    T square_w = quat.w * quat.w;

    vector3<T> result;

    if (homogenous)
    {
        result.x = crap::basemath<T>::atan2( 2.f * ( quat.x * quat.y + quat.z * quat.w ), square_x - square_y - square_z + square_w );
        result.y = crap::basemath<T>::asin( -2.f * ( quat.x * quat.z - quat.y * quat.w ));
        result.z = crap::basemath<T>::atan2( 2.f * ( quat.y * quat.z + quat.x * quat.w ), -square_x - square_y + square_z + square_w );
    }
    else
    {
        result.x = crap::basemath<T>::atan2( 2.f * ( quat.z * quat.y + quat.x * quat.w ), 1 - 2*(square_x + square_y) );
        result.y = crap::basemath<T>::asin( -2.f * ( quat.x * quat.z - quat.y * quat.w ));
        result.z = crap::basemath<T>::atan2( 2.f * ( quat.x * quat.y + quat.z * quat.w ), 1 - 2*(square_y + square_z) );
    }
    return result;
}

// create perspecive matrix with existing matrix 3d
template<typename T>
const matrix4<T>& geometry<T>::perspective_matrix4( matrix4<T>* matrix, const T& fov_y, const T& aspect, const T& z_near, const T& z_far )
{
	T range = crap::basemath<T>::tan( fov_y / T(2)) * z_near;	
	T left = -range * aspect;
	T right = range * aspect;
	T bottom = -range;
	T top = range;

	matrix->m[0][0] = (T(2) * z_near) / (right - left);
	matrix->m[1][1] = (T(2) * z_near) / (top - bottom);
	matrix->m[2][2] = - (z_far + z_near) / (z_far - z_near);
	matrix->m[2][3] = - T(1);
	matrix->m[3][2] = - (T(2) * z_far * z_near) / (z_far - z_near);
	return *matrix;
}

template<typename T>
const matrix4<T>& geometry<T>::look_at_matrix4( matrix4<T>* matrix, const vector3<T>& position, const vector3<T>& direction, const vector3<T>& up_vector )
{
	vector3<T> f = direction;
	geometry<T>::normalize( &f );
	vector3<T> u = up_vector;
	geometry<T>::normalize( &u );
	vector3<T> s = geometry<T>::cross(f, u);
	geometry<T>::normalize( &s );
	u = cross(s, f);

	geometry<T>::identity_matrix4( matrix );
	matrix->m[0][0] = s.x;
	matrix->m[1][0] = s.y;
	matrix->m[2][0] = s.z;
	matrix->m[0][1] = u.x;
	matrix->m[1][1] = u.y;
	matrix->m[2][1] = u.z;
	matrix->m[0][2] =-f.x;
	matrix->m[1][2] =-f.y;
	matrix->m[2][2] =-f.z;
	matrix->m[3][0] =-crap::geometry<T>::dot(s, position + direction);
	matrix->m[3][1] =-crap::geometry<T>::dot(u, position + direction);
	matrix->m[3][2] = crap::geometry<T>::dot(f, position + direction);
	return *matrix;
}

typedef geometry<i32> geometryi;
typedef geometry<i64> geometryl;
typedef geometry<f32> geometryf;
typedef geometry<f64> geometryd;

} // namespace crap

#endif // CRAP_GEOMETRY_GEOMETRY_H
