#include "UnitTest++.h"

//lib includes
#include "container/queue.h"

namespace
{

crap::static_queue<int, 10>* _staticqueue;

TEST(ContainerStaticQueueTitle)
{
    std::cout << "Testing \"container/queue.h\" (static_queue)" << std::endl;
}

TEST(ContainerStaticQueueConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_staticqueue = new crap::static_queue<int, 10>;
}

TEST(TestStaticQueueCopyContructor)
{
	std::cout << "\tdoing tests..." << std::endl;
	_staticqueue->push(25);
	_staticqueue->push(36);
	crap::static_queue<int,10> tmp(*_staticqueue);
	CHECK_EQUAL( 25, tmp.front() );
	CHECK_EQUAL( 36, tmp.back() );
}

TEST(TestStaticQueueAssigmentOperator)
{
	crap::static_queue<int,10> tmp;
	tmp = *_staticqueue;
	CHECK_EQUAL( 25, tmp.front() );
	CHECK_EQUAL( 36, tmp.back() );
}

TEST(TestStaticQueueSize)
{
	CHECK_EQUAL( 2, _staticqueue->size() );
	_staticqueue->push(47);
	_staticqueue->push(58);
	CHECK_EQUAL( 4, _staticqueue->size() );
}

TEST(TestStaticQueueMaxSize)
{
	CHECK_EQUAL( 10, _staticqueue->max_size() );
}

TEST(TestStaticQueueIsEmpty)
{
	CHECK_EQUAL( false, _staticqueue->is_empty() );
	_staticqueue->clear();
	CHECK_EQUAL( true, _staticqueue->is_empty() );
}

TEST(TestStaticQueueIsFull)
{
	CHECK_EQUAL( false, _staticqueue->is_full() );
	_staticqueue->push(1);
	_staticqueue->push(2);
	_staticqueue->push(3);
	_staticqueue->push(4);
	_staticqueue->push(5);
	_staticqueue->push(6);
	_staticqueue->push(7);
	_staticqueue->push(8);
	_staticqueue->push(9);
	_staticqueue->push(10);
	CHECK_EQUAL( true, _staticqueue->is_full() );
}

TEST(TestStaticQueuePushPop)
{
	CHECK_EQUAL( 1, _staticqueue->front() );
	CHECK_EQUAL( 10, _staticqueue->back() );
	_staticqueue->pop();
	CHECK_EQUAL( 2, _staticqueue->front() );
	_staticqueue->pop();
	CHECK_EQUAL( 3, _staticqueue->front() );
	_staticqueue->pop();
	CHECK_EQUAL( 4, _staticqueue->front() );
	_staticqueue->pop();
	CHECK_EQUAL( 5, _staticqueue->front() );
	_staticqueue->pop();
	CHECK_EQUAL( 6, _staticqueue->front() );
	_staticqueue->pop();
	CHECK_EQUAL( 7, _staticqueue->front() );
	_staticqueue->pop();
	CHECK_EQUAL( 8, _staticqueue->front() );
	_staticqueue->pop();
	CHECK_EQUAL( 9, _staticqueue->front() );
	_staticqueue->pop();
	CHECK_EQUAL( 10, _staticqueue->front() );
	CHECK_EQUAL( 10, _staticqueue->back() );
	_staticqueue->pop();
}

TEST(ContainerQueueDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _staticqueue;
}

}   // namespace