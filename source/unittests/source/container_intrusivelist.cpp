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


TEST(ContainerIntrusiveListConstructor)
{
	_intrusive_list = new crap::intrusive_list<IntrusiveStruct>();
}

TEST(ContainerIntruciveListPushback)
{
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
}

TEST(ContainerIntruciveListIsEmpty)
{
	crap::intrusive_list<IntrusiveStruct>::iterator it;
	for(it = _intrusive_list->begin(); it != _intrusive_list->end(); ++it)
	{
		std::cout << it->number << " " << it->another_number << " " << it->str << std::endl;
	}
}

TEST(ContainerIntruciveListScopes)
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

}