#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "memory/memorypool.h"

namespace
{

crap::memory_pool* _mempool;

TEST(MemoryMemoryPoolConstructor)
{
	std::cout << "\tConstruction" << std::endl;
	_mempool = new crap::memory_pool();
}

TEST(MemoryMemoryPoolDestructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _mempool;
}

}
