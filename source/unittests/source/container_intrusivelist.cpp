#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/intrusivelist.h"

namespace
{
struct IntrusiveStruct;

crap::intrusive_list<IntrusiveStruct>* _intrusive_list;

struct IntrusiveStruct
{
	int number;
	float another_number;
	char str[30];
	crap::intrusive_list_node<IntrusiveStruct> node;

	IntrusiveStruct( void ) : node( this, _intrusive_list, false ) {}
};

TEST(ContainerIntrusiveListTitle)
{
    std::cout << "Testing \"container/intrusivelist.h\"" << std::endl;
}


TEST(ContainerIntrusiveListConstructor)
{
	std::cout << "Testing \"Intrusive List Constructor\"" << std::endl;
	_intrusive_list = new crap::intrusive_list<IntrusiveStruct>();
}

TEST(ContainerIntrusiveListPushback)
{
	std::cout << "Testing \"Intrusive List push_back\"" << std::endl;
	IntrusiveStruct structOne;
	IntrusiveStruct structTwo;
	IntrusiveStruct structThree;

	structOne.number = 1;
	structOne.another_number = 1.1f;
	strcpy( structOne.str, "I am the first Struct\0" );

	structTwo.number = 2;
	structTwo.another_number = 2.2f;
	strcpy( structTwo.str, "I am the second Struct\0" );

	structThree.number = 3;
	structThree.another_number = 3.3f;
	strcpy( structThree.str, "I am the third Struct\0" );

	_intrusive_list->push_back( &structOne.node );
	_intrusive_list->push_back( &structTwo.node );
	_intrusive_list->push_back( &structThree.node );

	crap::intrusive_list<IntrusiveStruct>::iterator it;
	for(it = _intrusive_list->begin(); it != _intrusive_list->end(); ++it)
	{
		std::cout << it->number << " " << it->another_number << " " << it->str << std::endl;
	}
	it = _intrusive_list->begin();
	CHECK_EQUAL( 1, it->number);
	++it;
	CHECK_EQUAL( 2, it->number);
	++it;
	CHECK_EQUAL( 3, it->number);
	CHECK_EQUAL( (size_t32) 3, _intrusive_list->size() );
}

TEST(ContainerIntrusiveListIsEmpty)
{
	std::cout << "Testing \"Intrusive List is empty\"" << std::endl;
	CHECK_EQUAL( (size_t32) 0,_intrusive_list->size() );
}

TEST(ContainerIntrusiveListRemove) 
{
	std::cout << "Testing \"Intrusive List remove\"" << std::endl;
	IntrusiveStruct structOne;
	structOne.number = 1;
	structOne.another_number = 1.1f;
	strcpy( structOne.str, "I am the first Struct\0" );
	_intrusive_list->push_back( &structOne.node );
	_intrusive_list->remove( &structOne.node );
	CHECK_EQUAL( (size_t32) 0,_intrusive_list->size() );
}

TEST(ContainerIntrusiveListPopBack) 
{
	std::cout << "Testing \"Intrusive List popback\"" << std::endl;
	IntrusiveStruct structOne;
	structOne.number = 1;
	structOne.another_number = 1.1f;
	strcpy( structOne.str, "I am the first Struct\0" );
	_intrusive_list->push_back( &structOne.node );
	_intrusive_list->pop_back();
	CHECK_EQUAL( (size_t32) 0,_intrusive_list->size() );
}

TEST(ContainerIntrusiveListPopFront) 
{
	std::cout << "Testing \"Intrusive List popfront\"" << std::endl;
	IntrusiveStruct structOne;
	structOne.number = 1;
	structOne.another_number = 1.1f;
	strcpy( structOne.str, "I am the first Struct\0" );
	_intrusive_list->push_back( &structOne.node );
	_intrusive_list->pop_front();
	CHECK_EQUAL( (size_t32) 0,_intrusive_list->size() );
}

TEST(ContainerIntrusiveListPushFront) 
{
	std::cout << "Testing \"Intrusive List push front\"" << std::endl;
	IntrusiveStruct structOne;
	structOne.number = 1;
	structOne.another_number = 1.1f;
	strcpy( structOne.str, "I am the first Struct\0" );
	IntrusiveStruct structTwo;
	structOne.number = 2;
	structOne.another_number = 2.2f;
	strcpy( structOne.str, "I am the second Struct\0" );
	_intrusive_list->push_back( &structOne.node );
	_intrusive_list->push_front( &structTwo.node );
	CHECK_EQUAL( (size_t32) 2,_intrusive_list->size() );
}

TEST(ContainerIntrusiveListScopes)
{
	IntrusiveStruct structOne;
	structOne.number = 1;
	structOne.another_number = 1.1f;
	strcpy( structOne.str, "I am the first Struct\0" );

	_intrusive_list->push_back( &structOne.node );

	crap::intrusive_list<IntrusiveStruct>::iterator it;
	for(it = _intrusive_list->begin(); it != _intrusive_list->end(); ++it)
	{
		std::cout << it->number << " " << it->another_number << " " << it->str << std::endl;
	}
	{
		IntrusiveStruct structTwo;
		structTwo.number = 2;
		structTwo.another_number = 2.2f;
		strcpy( structTwo.str, "I am the second Struct\0" );

		_intrusive_list->push_back( &structTwo.node );

		crap::intrusive_list<IntrusiveStruct>::iterator it;
		for(it = _intrusive_list->begin(); it != _intrusive_list->end(); ++it)
		{
			std::cout << it->number << " " << it->another_number << " " << it->str << std::endl;
		}
	}
	for(it = _intrusive_list->begin(); it != _intrusive_list->end(); ++it)
	{
		std::cout << it->number << " " << it->another_number << " " << it->str << std::endl;
	}
}

TEST(ContainerIntrusiveListPopBack) 
{
	std::cout << "Testing \"Intrusive List pop back\"" << std::endl;
	IntrusiveStruct structOne;
	structOne.number = 1;
	structOne.another_number = 1.1f;
	strcpy( structOne.str, "I am the first Struct\0" );
	_intrusive_list->push_back( &structOne.node );
	_intrusive_list->pop_back();
	CHECK_EQUAL( (size_t32) 0,_intrusive_list->size() );
}

}