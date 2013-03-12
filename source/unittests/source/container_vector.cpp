#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/vector.h"

namespace
{

crap::vector<int>* _vector;

TEST(ContainerVectorTitle)
{
    std::cout << "Testing \"container/vector.h\"" << std::endl;
}

TEST(ContainerVectorConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_vector = new crap::vector<int>;
}

TEST(ContainerVectorDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete 	_vector;
}

}   // namespace
