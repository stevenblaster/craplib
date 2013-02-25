#include "UnitTest++.h"

//lib includes
#include "geometry/matrix2.h"

namespace
{

crap::matrix2f* _mat2f;

TEST(GeometryMatrix2Title)
{
    std::cout << "Testing \"geometry/matrix2.h\"" << std::endl;
}

TEST(GeometryMatrix2Constructor)
{
	std::cout << "\tConstruction" << std::endl;
	_mat2f = new crap::matrix2f;
}

TEST(GeometryMatrix2Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _mat2f;
}

}   // namespace

