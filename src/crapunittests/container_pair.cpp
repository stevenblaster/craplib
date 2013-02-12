#include "UnitTest++.h"

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

TEST(ContainerPairDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _pair;
}

}   // namespace
