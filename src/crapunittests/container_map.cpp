#include "UnitTest++.h"

//lib includes
#include "container/map.h"

namespace
{

crap::map<int, float>* _map;

TEST(ContainerMapTitle)
{
    std::cout << "Testing \"container/map.h\"" << std::endl;
}

TEST(ContainerMapConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_map = new crap::map<int, float>;
}

TEST(ContainerMapDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _map;
}

}   // namespace