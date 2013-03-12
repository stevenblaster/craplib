#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/string.h"

namespace
{

crap::string* _string;

TEST(ContainerStringTitle)
{
    std::cout << "Testing \"container/string.h\"" << std::endl;
}

TEST(ContainerStringConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_string = new crap::string;
}

TEST(ContainerStrinSTLInfo)
{
	std::cout << "\tInherited from STL - guess its tested" << std::endl;
}

TEST(ContainerStringDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete 	_string;
}

}   // namespace
