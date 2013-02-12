#include "UnitTest++.h"

//lib includes
#include "container/treemap.h"

namespace
{

crap::tree_map<int, float>* _treemap;

TEST(ContainerTreemapTitle)
{
    std::cout << "Testing \"container/treemap.h\"" << std::endl;
}

TEST(ContainerTreemapConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_treemap = new crap::tree_map<int, float>;
}

TEST(ContainerTreemapDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _treemap;
}

}   // namespace
