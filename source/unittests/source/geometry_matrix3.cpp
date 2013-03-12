#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "geometry/matrix3.h"

namespace
{

crap::matrix3f* _mat3f;

TEST(GeometryMatrix3Title)
{
    std::cout << "Testing \"geometry/matrix3.h\"" << std::endl;
}

TEST(GeometryMatrix3Constructor)
{
	std::cout << "\tConstruction" << std::endl;
	_mat3f = new crap::matrix3f;
}

TEST(GeometryMatrix3Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _mat3f;
}

}   // namespace