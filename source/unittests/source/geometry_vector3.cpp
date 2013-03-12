#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "geometry/vector3.h"

namespace
{

crap::vector3f* _vec3f;

TEST(ConfigVector3Title)
{
    std::cout << "Testing \"geometry/vector3.h\"" << std::endl;
}

TEST(GeometryVector3Constructor)
{
	std::cout << "\tConstruction" << std::endl;
	_vec3f = new crap::vector3f;
}

TEST(GeometryVector3Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _vec3f;
}

}   // namespace


