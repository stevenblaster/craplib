#include "UnitTest++.h"

//lib includes
#include "container/queue.h"

namespace
{

crap::static_queue<int, 20>* _staticqueue;

TEST(ContainerQueueTitle)
{
    std::cout << "Testing \"container/queue.h\" (static_queue)" << std::endl;
}

TEST(ContainerQueueConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_staticqueue = new crap::static_queue<int, 20>;
}

TEST(ContainerQueueDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _staticqueue;
}

}   // namespace