#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/list.h"

namespace
{

crap::list<int>* _list;

TEST(ContainerListTitle)
{
    std::cout << "Testing \"container/list.h\"" << std::endl;
}

TEST(ContainerListConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_list = new crap::list<int>;
}

TEST(ContainerListSTLInfo)
{
	std::cout << "\tInherited from STL - guess its tested" << std::endl;
}

TEST(ContainerListDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _list;
}

}   // namespace
