#include "UnitTest++.h"

//lib includes
#include "container/binarytree.h"

namespace
{

crap::binary_tree<int>* _bintree;

TEST(ContainerBinarytreeTitle)
{
    std::cout << "Testing \"container/binarytree.h\"" << std::endl;
}

TEST(ContainerBinaryTreeConstruct)
{
	std::cout << "\tConstruction" << std::endl;

	_bintree = new crap::binary_tree<int>;
}

TEST(ContainerBinaryTreeInsert)
{
        for(i32 i=10; i>0; --i)
                if(i%2 == 1)
                        _bintree->insert(i);

        for(i32 i=0; i<10; ++i)
                if(i%2 == 0)
                        _bintree->insert(i);

}

TEST(ContainerBinaryTreeMinNode)
{
        //std::cout << "Minimum Node: " << *_bintree->min_node() << std::endl;
		CHECK_EQUAL( 0, *_bintree->min_node() );
}

TEST(ContainerBinaryTreeMaxNode)
{
        //std::cout << "Maximum Node: " << *_bintree->max_node() << std::endl;
		CHECK_EQUAL( 9, *_bintree->max_node() );
}

TEST(ContainerBinaryTreeLeftDeth)
{
        //std::cout << "Left depth: " << _bintree->depth_left() << std::endl;
		CHECK_EQUAL( 5, _bintree->depth_left() );
}

TEST(ContainerBinaryTreeRightDepth)
{
        //std::cout << "Right depth: " << _bintree->depth_right() << std::endl;
		CHECK_EQUAL( 0, _bintree->depth_right() );
}

TEST(ContainerBinaryTreeDepth)
{
        //std::cout << "Total depth: " << _bintree->depth() << std::endl;
		CHECK_EQUAL( 5, _bintree->depth() );
}


TEST(ContainerBinaryTreeWidthAtPosition)
{
        //std::cout << "Nodes as level..." << std::endl;
        //for(u32 i=0; i<= _bintree->depth(); ++i)
        //{
        //        std::cout << "Level" << i <<":" << _bintree->depth_elements(i) << std::endl;
        //}
        //std::cout << std::endl;
}

TEST(ContainerBinaryTreeSuccessor)
{
	std::cout << "\tTesting successor iteration";
	i32 counter = 0;
	crap::binary_tree<int>::node_pointer node = _bintree->min_node().ptr();
	while(node != 0)
	{
		//std::cout << node->data << ",";
		CHECK_EQUAL( counter++, node->data );
		node = node->successor_iterative(node);
	}
	std::cout << std::endl;
}

TEST(ContainerBinaryTreePredecessor)
{
	std::cout << "\tTesting predecessor iteration";
	i32 counter = 9;
	crap::binary_tree<int>::node_pointer node = _bintree->max_node().ptr();
	while(node != 0)
	{
		//std::cout << node->data << ",";
		CHECK_EQUAL( counter--, node->data );
		node = node->predecessor_iterative(node);
	}
	std::cout << std::endl;
}

TEST(ContainerBinaryTreeIteratorHigher)
{
	i32 counter = 0;
	std::cout << "\tTesting Iterator low to high";
	for(crap::binary_tree<int>::iterator it = _bintree->begin(); it != _bintree->end(); ++it)
	{
		//std::cout << *it << ",";
		CHECK_EQUAL( counter++, *it );
	}
	std::cout << std::endl;
}

TEST(ContainerBinaryTreeIteratorLower)
{
	i32 counter = 9;
	std::cout << "\tTesting Iterator high to low";
	for(crap::binary_tree<int>::iterator it = _bintree->max_node(); it != _bintree->end(); --it)
	{
		//std::cout << *it << ",";
		CHECK_EQUAL( counter--, *it );
	}
	std::cout << std::endl;
}

TEST(ContainerBinaryTreeFind)
{
	CHECK_EQUAL(5, *_bintree->find(5) );
	CHECK_EQUAL(0, *_bintree->find(0) );
	CHECK_EQUAL(1, *_bintree->find(1) );
	CHECK_EQUAL(3, *_bintree->find(3) );
	crap::binary_tree<int>::iterator it = _bintree->find(20);
	crap::binary_tree<int>::iterator it2 = _bintree->end();

	CHECK( it == it2 );
}

TEST(ContainerBinaryTreeTop)
{
	CHECK_EQUAL( 9, *_bintree->top() );
}

TEST(ContainerBinaryTreeRotateRight)
{
	crap::binary_tree<int>::node_pointer leftof = _bintree->top()->sub_node[crap::binary_tree<int>::node_type::left];

	_bintree->rotate_right();

	CHECK_EQUAL( leftof->data, _bintree->top()->data );

	_bintree->rotate_right();
	_bintree->rotate_right();
	
	i32 counter = 0;
	for(crap::binary_tree<int>::iterator it = _bintree->begin(); it != _bintree->end(); ++it)
	{
		//std::cout << *it << ",";
		CHECK_EQUAL( counter++, *it );
	}
}

TEST(ContainerBinaryTreeRotateLeft)
{
	crap::binary_tree<int>::node_pointer rightof = _bintree->top()->sub_node[crap::binary_tree<int>::node_type::right];

	_bintree->rotate_left();

	CHECK_EQUAL( rightof->data, _bintree->top()->data );

	_bintree->rotate_left();
	_bintree->rotate_left();

	i32 counter = 0;
	for(crap::binary_tree<int>::iterator it = _bintree->begin(); it != _bintree->end(); ++it)
	{
		//std::cout << *it << ",";
		CHECK_EQUAL( counter++, *it );
	}
}

TEST(ContainerBinaryTreeRealign)
{
	_bintree->realign();

	i32 counter = 0;
	for(crap::binary_tree<int>::iterator it = _bintree->begin(); it != _bintree->end(); ++it)
	{
		//std::cout << *it << ",";
		CHECK_EQUAL( counter++, *it );
	}
}

TEST(ContainerBinaryTreeRemove)
{
	//std::cout << "Size before deletion: " << _bintree->size() << std::endl;
	_bintree->remove(6);
	_bintree->remove(2);
	_bintree->remove(4);
	_bintree->remove(3);
	_bintree->remove(1);
	_bintree->remove(5);
	CHECK_EQUAL( 4, _bintree->size() );
	//std::cout << "Size after deletion: " << _bintree->size() << std::endl;
	//std::cout << "Iterator after removing elements: 
	for(crap::binary_tree<int>::iterator it = _bintree->begin(); it != _bintree->end(); ++it)
	{
		//std::cout << *it << ",";
	}
	//std::cout << std::endl;
}

TEST(TestBinaryTreeClear)
{
	_bintree->clear();

	CHECK_EQUAL( 0, _bintree->size() );
}


TEST(ContainerBinaryTreeDestruct)
{
	std::cout << "\tDestruction" << std::endl;
	delete _bintree;
}

}   // namespace
