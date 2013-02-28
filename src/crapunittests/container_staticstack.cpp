#include "UnitTest++.h"

//lib includes
#include "container/stack.h"

namespace
{

crap::static_stack<int, 10>* _staticstack;

TEST(ContainerStaticstackTitle)
{
    std::cout << "Testing \"container/stack.h\" (static_stack)" << std::endl;
}

TEST(ContainerStaticstackConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_staticstack = new crap::static_stack<int, 10>;
}

TEST(ContainerStaticStackCopyContructor)
{
	std::cout << "\tdoing tests..." << std::endl;
	_staticstack->push(25);
	_staticstack->push(36);
	crap::static_stack<int,10> tmp(*_staticstack);
	CHECK_EQUAL( 36, tmp.top() );
	tmp.pop();
	CHECK_EQUAL( 25, tmp.top() );
}

TEST(ContainerStaticStackAssigmentOperator)
{
	crap::static_stack<int,10> tmp;
	tmp = *_staticstack;
	CHECK_EQUAL( 36, tmp.top() );
	tmp.pop();
	CHECK_EQUAL( 25, tmp.top() );
}

TEST(ContainerStaticStackSize)
{
	CHECK_EQUAL( 2, _staticstack->size() );
	_staticstack->push(47);
	_staticstack->push(58);
	CHECK_EQUAL( 4, _staticstack->size() );
}

TEST(ContainerStaticStackMaxSize)
{
	CHECK_EQUAL( 10, _staticstack->max_size() );
}

TEST(ContainerStaticStackIsEmpty)
{
	CHECK_EQUAL( false, _staticstack->is_empty() );
	_staticstack->clear();
	CHECK_EQUAL( true, _staticstack->is_empty() );
}

TEST(ContainerStaticStackIsFull)
{
	CHECK_EQUAL( false, _staticstack->is_full() );
	_staticstack->push(1);
	_staticstack->push(2);
	_staticstack->push(3);
	_staticstack->push(4);
	_staticstack->push(5);
	_staticstack->push(6);
	_staticstack->push(7);
	_staticstack->push(8);
	_staticstack->push(9);
	_staticstack->push(10);
	CHECK_EQUAL( true, _staticstack->is_full() );
}

TEST(ContainerStaticStackPushPop)
{
	CHECK_EQUAL( 10, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 9, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 8, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 7, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 6, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 5, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 4, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 3, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 2, _staticstack->top() );
	_staticstack->pop();
	CHECK_EQUAL( 1, _staticstack->top() );
	_staticstack->pop();
}

TEST(ContainerStackDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _staticstack;
}

}   // namespace
