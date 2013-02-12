#include "UnitTest++.h"

//lib includes
#include "container/treenode.h"

namespace
{

crap::tree_node<int>* _treenode;

TEST(ConfigTreenodeTitle)
{
    std::cout << "Testing \"container/treenode.h\"" << std::endl;
}

TEST(ContainerTreenodeConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_treenode = new crap::tree_node<int>;
}

TEST(ContainerTreenodeDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete 	_treenode;
}

}   // namespace
