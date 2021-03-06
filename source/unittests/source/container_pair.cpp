#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/pair.h"

namespace
{

crap::pair<int, float>* _pair;

TEST(ContainerPairTitle)
{
    std::cout << "Testing \"container/pair.h\"" << std::endl;
}

TEST(ContainerPairConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_pair = new crap::pair<int, float>;
}

TEST(ContainerPairSTLInfo)
{
	std::cout << "\tPlain copy from STL" << std::endl;
}

TEST(ContainerPairDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _pair;
}

}   // namespace
