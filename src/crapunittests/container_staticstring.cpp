#include "UnitTest++.h"

//lib includes
#include "container/staticstring.h"

namespace
{

crap::static_string<20>* _staticstring;

TEST(ContainerStaticstringTitle)
{
    std::cout << "Testing \"container/staticstring.h\"" << std::endl;
}

TEST(ContainerStaticstringConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_staticstring = new crap::static_string<20>;
}

TEST(ContainerStaticstringDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete 	_staticstring;
}

}   // namespace
