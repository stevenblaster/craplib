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

TEST(ContainerBitsetCopyConstructor)
{
	std::cout << "\tdoing tests..." << std::endl;
	_bitset->set(0);
	crap::bit_set<32*8> tmp( *_bitset );
	CHECK_EQUAL( _bitset->test(0), tmp.test(0));
}

TEST(ContainerBitsetAssignmentOperator)
{
	crap::bit_set<32*8> tmp;
	tmp = *_bitset;
	CHECK_EQUAL( _bitset->test(0), tmp.test(0));
}

TEST(ContainerBitsetAssignmentOperatorVoid)
{
	crap::bit_set<32*8> tmp;
	tmp = _bitset->pointer();
	CHECK_EQUAL( _bitset->test(0), tmp.test(0));
}

TEST(ContainerBitsetDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _bitset;
}

}   // namespace
