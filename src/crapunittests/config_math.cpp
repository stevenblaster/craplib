#include "UnitTest++.h"

//lib includes
#include "config/math.h"

namespace
{

TEST(ConfigMathTitle)
{
    std::cout << "Testing \"config/math.h\"" << std::endl;
}

TEST(ConfigMathDefines)
{
	std::cout << "\tChecking defines" << std::endl;

	CHECK_EQUAL(CRAP_E, 2.71828182845904523536F);
	CHECK_EQUAL(CRAP_PI, 3.14159265358979323846F);
	CHECK_EQUAL(CRAP_TWO_PI, 6.28318530718958647692F);
	CHECK_EQUAL(CRAP_PI_HALF, 1.57079632679489661923F);
	CHECK_EQUAL(CRAP_PI_QUATER, 0.78539816339744830962F);
	CHECK_EQUAL(CRAP_1_DIV_PI, 0.31830988618379067154F);
	CHECK_EQUAL(CRAP_2_DIV_PI, 0.63661977236758134308F);
	CHECK_EQUAL(CRAP_LOG2E, 1.44269504088896340736F);
	CHECK_EQUAL(CRAP_LOG10_E, 0.43429448190325182765F);
	CHECK_EQUAL(CRAP_LN_2, 0.69314718055994530942F);
	CHECK_EQUAL(CRAP_LN_10, 2.30258509299404568402F);
	CHECK_EQUAL(CRAP_2_DIV_SQRT_PI, 1.12837916709551257390F);
	CHECK_EQUAL(CRAP_SQRT_2, 1.41421356237309504880F);
	CHECK_EQUAL(CRAP_SQRT_3, 1.73205080756887729353F);
	CHECK_EQUAL(CRAP_SQRT_1_DIV_2, 0.70710678118654752440F);
	CHECK_EQUAL(CRAP_SQRT_1_DIV_3, 0.57735027955204221151F);
	CHECK_EQUAL(CRAP_SQRT_PI, 9.86960440108935861883F);
	CHECK_EQUAL(CRAP_DEG_TO_RAD, 0.01745329238F);
	CHECK_EQUAL(CRAP_RAD_TO_DEG, 57.295779513F);
	CHECK_EQUAL(CRAP_EPSILON, 1E-5F);
}

}   // namespace

