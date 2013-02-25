#include "UnitTest++.h"

//lib includes
#include "geometry/vector2.h"

namespace
{

crap::vector2f* _vec2f;

TEST(ConfigVector2Title)
{
    std::cout << "Testing \"geometry/vector2.h\"" << std::endl;
}

TEST(GeometryVector2Constructor)
{
	std::cout << "\tConstruction" << std::endl;
	_vec2f = new crap::vector2f;
}

TEST(GeometryVector2Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _vec2f;
}

}   // namespace

