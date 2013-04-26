#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/fixedstring.h"
#include "container/indexedarray.h"

namespace
{

crap::indexed_array< crap::string32, 10>* _indexed_array;

TEST(ContainerIndexdArrayConstructor)
{
	_indexed_array = new crap::indexed_array< crap::string32, 10>();
}

//happy testing

TEST(ContainerIndexdArrayDestructor)
{
	delete _indexed_array;
}

}