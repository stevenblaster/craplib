#include "UnitTest++.h"

//lib includes
#include "geometry/vector4.h"

namespace
{

crap::vector4f* _vec4f;

TEST(ConfigVector4Title)
{
    std::cout << "Testing \"geometry/vector4.h\"" << std::endl;
}

TEST(GeometryVector4Constructor)
{
	std::cout << "\tConstruction" << std::endl;
	_vec4f = new crap::vector4f;
}

TEST(GeometryVector4Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _vec4f;
}

}   // namespace



