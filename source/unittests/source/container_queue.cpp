#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/queue.h"

namespace
{

crap::queue<int>* _queue;

TEST(ContainerQueueTitle)
{
    std::cout << "Testing \"container/queue.h\" (queue)" << std::endl;
}

TEST(ContainerQueueConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_queue = new crap::queue<int>;
}

TEST(ContainerQueueSTLinfo)
{
	std::cout << "\tInherited from STL - guess its tested" << std::endl;
}

TEST(ContainerQueueDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _queue;
}

}   // namespace
