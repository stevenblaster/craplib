#include "UnitTest++.h"

//lib includes
#include "container/bitset.h"

namespace
{

crap::bit_set<32*8>* _bitset;

TEST(ContainerBitsetTitle)
{
    std::cout << "Testing \"container/bitset.h\"" << std::endl;
}

TEST(ContainerBitsetConstruction)
{
	std::cout << "\tConstruction" << std::endl;
	_bitset = new crap::bit_set<32*8>;
}

TEST(ContainerBitsetDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _bitset;
}

}   // namespace
