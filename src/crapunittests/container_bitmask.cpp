#include "UnitTest++.h"

//lib includes
#include "container/bitmask.h"

namespace
{

char* _bitmask_memory;
crap::bit_mask* _bitmask;

TEST(ContainerBitmaskTitle)
{
    std::cout << "Testing \"container/bitmask.h\"" << std::endl;
}

TEST(ContainerBitmaskConstruct)
{
	std::cout << "\tConstruction" << std::endl;

	_bitmask_memory = new char[32];
	_bitmask = new crap::bit_mask( _bitmask_memory, 32*8 );
}

TEST(ContainerBitmaskDestruct)
{
	std::cout << "\tDestruction" << std::endl;
    delete _bitmask;
	delete _bitmask_memory;
}

}   // namespace
