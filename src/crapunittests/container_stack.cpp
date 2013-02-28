#include "UnitTest++.h"

//lib includes
#include "container/stack.h"

namespace
{

crap::stack<int>* _stack;

TEST(ContainerStackTitle)
{
    std::cout << "Testing \"container/stack.h\" (stack)" << std::endl;
}

TEST(ContainerStackConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_stack = new crap::stack<int>;
}

TEST(ContainerMapSTLinfo)
{
	std::cout << "\tInherited from STL - guess its tested" << std::endl;
}

TEST(ContainerStackDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _stack;
}

}   // namespace
