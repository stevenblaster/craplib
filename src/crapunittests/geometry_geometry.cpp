#include "UnitTest++.h"

//lib includes
#include "geometry/geometry.h"
#include "math/math.h"

namespace
{

TEST(GeometryGeometryTitle)
{
    std::cout << "Testing \"geometry/geometry.h\"" << std::endl;
}

TEST(GeometryGeometryZeroMatrix3)
{
	std::cout << "\tZero Matrices" << std::endl;
	crap::matrix3f zerof;
	zerof.xx = 12;
	zerof.yy = 23;
	zerof.zz = 34;
	crap::geometryf::zero_matrix3( &zerof );

	CHECK_EQUAL(0, zerof.xx );
	CHECK_EQUAL(0, zerof.yy );
	CHECK_EQUAL(0, zerof.zz );
}

TEST(GeometryGeometryZeroMatrix4)
{
	crap::matrix4f zerof;
	zerof.xx = 12;
	zerof.yy = 23;
	zerof.zz = 34;
	zerof.ww = 45;
	crap::geometryf::zero_matrix4( &zerof );

	CHECK_EQUAL(0, zerof.xx );
	CHECK_EQUAL(0, zerof.yy );
	CHECK_EQUAL(0, zerof.zz );
	CHECK_EQUAL(0, zerof.ww );
}

TEST(GeometryGeometryIdentityMatrix3)
{
	std::cout << "\tIdentity Matrices" << std::endl;
	crap::matrix3f zerof;
	zerof.xx = 12;
	zerof.yy = 23;
	zerof.zz = 34;
	crap::geometryf::identity_matrix3( &zerof );

	CHECK_EQUAL(1, zerof.xx );
	CHECK_EQUAL(1, zerof.yy );
	CHECK_EQUAL(1, zerof.zz );
}

TEST(GeometryGeometryIdentityMatrix4)
{
	crap::matrix4f zerof;
	zerof.xx = 12;
	zerof.yy = 23;
	zerof.zz = 34;
	zerof.ww = 45;
	crap::geometryf::identity_matrix4( &zerof );

	CHECK_EQUAL(1, zerof.xx );
	CHECK_EQUAL(1, zerof.yy );
	CHECK_EQUAL(1, zerof.zz );
	CHECK_EQUAL(1, zerof.ww );
}

TEST(GeometryGeometryTranslationMatrix3)
{
	std::cout << "\tTranslation Matrices" << std::endl;
	crap::matrix3f zerof;
	zerof.xx = 12;
	zerof.yy = 23;
	zerof.zz = 34;

	crap::vector2f vec2;
	vec2.x = 12.5f;
	vec2.y = 23.4f;

	crap::geometryf::translation_matrix3( &zerof, vec2 );

	CHECK_EQUAL(1, zerof.xx );
	CHECK_EQUAL(1, zerof.yy );
	CHECK_EQUAL(1, zerof.zz );
	CHECK_EQUAL(12.5f, zerof.xz );
	CHECK_EQUAL(23.4f, zerof.yz );
}

TEST(GeometryGeometryTranslationMatrix4)
{
	crap::matrix4f zerof;
	zerof.xx = 12;
	zerof.yy = 23;
	zerof.zz = 34;
	zerof.ww = 45;

	crap::vector3f vec3;
	vec3.x = 12.3f;
	vec3.y = 23.4f;
	vec3.z = 34.5f;

	crap::geometryf::translation_matrix4( &zerof, vec3 );

	CHECK_EQUAL(1, zerof.xx );
	CHECK_EQUAL(1, zerof.yy );
	CHECK_EQUAL(1, zerof.zz );
	CHECK_EQUAL(1, zerof.ww );
	CHECK_EQUAL(12.3f, zerof.xw );
	CHECK_EQUAL(23.4f, zerof.yw );
	CHECK_EQUAL(34.5f, zerof.zw );
}

TEST(GeometryGeometryRotationMatrix3)
{
	std::cout << "\tRotation Matrices" << std::endl;
	crap::matrix3f zerof;

	crap::vector2f vec2;
	vec2.x = 12.5f;
	vec2.y = 23.4f;

	crap::geometryf::rotation_matrix3( &zerof, vec2 );

	CHECK_EQUAL(crap::math<f32>::cos(vec2.x), zerof.xx );
	CHECK_EQUAL(-crap::math<f32>::sin(vec2.x), zerof.xy );
	CHECK_EQUAL(crap::math<f32>::sin(vec2.x), zerof.yx );
	CHECK_EQUAL(crap::math<f32>::cos(vec2.x), zerof.yy );
}

TEST(GeometryGeometryRotationMatrix4)
{
	crap::matrix4f zerof;

	crap::vector3f vec3;
	vec3.x = 12.3f;
	vec3.y = 23.4f;
	vec3.z = 34.5f;

	crap::geometryf::rotation_matrix4( &zerof, vec3 );

	std::cout << "\t\tNo Tests for Rotation 4 (Gonna test on geometry/cam later)" << std::endl;
}

TEST(GeometryGeometryDotVector2)
{
	std::cout << "\tTesting dot products" << std::endl;
	
	crap::vector2f l,r;

	l.x = 2;
	l.y = 3;
	r.x = 4;
	r.y = 5;

	f32 result = crap::geometryf::dot(l, r);
	CHECK_EQUAL( 23, result);
}

TEST(GeometryGeometryDotVector3)
{
	crap::vector3f l,r;

	l.x = 2;
	l.y = 3;
	l.z = 4;
	r.x = 5;
	r.y = 6;
	r.z = 7;

	f32 result = crap::geometryf::dot(l, r);
	CHECK_EQUAL( 56, result);
}

TEST(GeometryGeometryDotVector4)
{
	crap::vector4f l,r;

	l.x = 2;
	l.y = 3;
	l.z = 4;
	l.w = 5;
	r.x = 6;
	r.y = 7;
	r.z = 8;
	r.w = 9; 

	f32 result = crap::geometryf::dot(l, r);
	CHECK_EQUAL( 12+21+32+45, result);
}

TEST(GeometryGeometryCrossVector2Scalar)
{
	std::cout << "\tTesting cross products" << std::endl;
	
	crap::vector2f l,r;

	l.x = 2;
	l.y = 3;
	r.x = 4;
	r.y = 5;

	f32 result = crap::geometryf::cross(l, r);
	CHECK_EQUAL( -2, result);
}

TEST(GeometryGeometryCrossVector2Vector)
{
	crap::vector2f l;

	l.x = 2;
	l.y = 3;

	crap::vector2f result = crap::geometryf::cross(l);
	CHECK_EQUAL( 3, result.x);
	CHECK_EQUAL( -2, result.y);
}

TEST(GeometryGeometryCrossVector3)
{
	crap::vector3f l,r;

	l.x = 2;
	l.y = 3;
	l.z = 4;
	r.x = 5;
	r.y = 6;
	r.z = 7;

	crap::vector3f result = crap::geometryf::cross(l, r);
	CHECK_EQUAL( -3, result.x);
	CHECK_EQUAL( 6, result.y);
	CHECK_EQUAL( -3, result.z);
}

}   // namespace
