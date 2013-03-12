#include "UnitTest++.h"
#include "crap.h"

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

TEST(ContainerTreemapInsert)
{
	std::cout << "\tnot working as supposed -> TODO: remove or fix" << std::endl;
	crap::pair<int, float> pr( 1, 0.1f );
	_treemap->insert( pr );
	crap::pair<int, float> pr2( 2, 0.2f );
	_treemap->insert( pr );
	crap::pair<int, float> pr3( 3, 0.3f );
	_treemap->insert( pr );
//	std::cout << _treemap->size();
	//for( crap::tree_map<int, float>::iterator it = _treemap->begin(); it != _treemap->end(); ++it )
	//{
	//	std::cout << "key: " << it->data.first << ", value : " << it->data.second << std::endl;
	//}
}

TEST(ContainerTreemapDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _treemap;
}

}   // namespace
