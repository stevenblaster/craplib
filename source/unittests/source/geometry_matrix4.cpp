#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "math/matrix4.h"

namespace
{

crap::matrix4f* _mat4f;

TEST(GeometryMatrix4Title)
{
    std::cout << "Testing \"geometry/matrix4.h\"" << std::endl;
}

TEST(GeometryMatrix4Constructor)
{
	std::cout << "\tConstruction" << std::endl;
	_mat4f = new crap::matrix4f;
}

TEST(GeometryMatrix4Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _mat4f;
}

}   // namespace