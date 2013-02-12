#include "UnitTest++.h"

//lib includes
#include "container/stack.h"

namespace
{

crap::static_stack<int, 20>* _staticstack;

TEST(ContainerStaticstackTitle)
{
    std::cout << "Testing \"container/stack.h\" (static_stack)" << std::endl;
}

TEST(ContainerStaticstackConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_staticstack = new crap::static_stack<int, 20>;
}

TEST(ContainerStackDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _staticstack;
}

}   // namespace
