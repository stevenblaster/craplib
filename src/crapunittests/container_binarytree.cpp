#include "UnitTest++.h"

//lib includes
#include "container/binarytree.h"

namespace
{

crap::binary_tree<int>* _tree;

TEST(ContainerBinarytreeTitle)
{
    std::cout << "Testing \"container/binarytree.h\"" << std::endl;
}

TEST(ContainerBinaryTreeConstruct)
{
	std::cout << "\tConstruction" << std::endl;

	_tree = new crap::binary_tree<int>;
}

TEST(ContainerBinaryTreeDestruct)
{
	std::cout << "\tDestruction" << std::endl;
	delete _tree;
}

}   // namespace
