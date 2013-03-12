#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/map.h"

namespace
{

crap::map<i32, f32>* _map;

TEST(ContainerMapTitle)
{
    std::cout << "Testing \"container/map.h\"" << std::endl;
}

TEST(ContainerMapConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_map = new crap::map<int, float>;
}

TEST(ContainerMapSTLinfo)
{
	std::cout << "\tInherited from STL - guess its tested" << std::endl;
}

TEST(ContainerMapDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _map;
}

}   // namespace