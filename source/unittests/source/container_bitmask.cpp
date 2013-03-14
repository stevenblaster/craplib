#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "container/bitmask.h"

namespace
{

char* _bitmask_memory;
crap::bit_mask* _bitmask;

TEST(ContainerBitmaskTitle)
{
    std::cout << "Testing \"container/bitmask.h\"" << std::endl;
}

TEST(ContainerBitmaskConstruct)
{
	std::cout << "\tConstruction" << std::endl;

	_bitmask_memory = new char[10];
	_bitmask = new crap::bit_mask( _bitmask_memory, 10*8 );
}

TEST(ContainerBitMaskCopyConstructor)
{
	std::cout << "\tdoing tests..." << std::endl;
	crap::bit_mask mask(*_bitmask);
	CHECK_EQUAL( mask.pointer(), _bitmask->pointer() );
}

TEST(ContainerBitMaskInit)
{
	crap::bit_mask mask;
	mask.init(_bitmask_memory, 10);
	CHECK_EQUAL( mask.pointer(), _bitmask->pointer() );
}

TEST(ContainerBitMaskAssignmentOperator)
{
	u8 localtestmem[10];
	crap::bit_mask mask(localtestmem, 10);
	CHECK( mask.pointer() != _bitmask->pointer() );
	mask.init(_bitmask_memory, 10);
	CHECK_EQUAL( mask.pointer(), _bitmask->pointer() );
}

TEST(ContainerBitMaskAssignmentOperatorVoid)
{
	u8 localtestmem[10];
	crap::bit_mask mask(localtestmem, 10);
	mask.reset();
	localtestmem[0] = 10; //maybe not working with big endian
        
	CHECK( mask.pointer() != _bitmask->pointer() );
    CHECK_EQUAL( *((u8*)mask.pointer()), 10 );
	mask = _bitmask->pointer();
	CHECK( *((u8*)mask.pointer()) != 10 );
	CHECK_EQUAL( *((u8*)mask.pointer()), *((u8*)_bitmask->pointer()) );
}

TEST(ContainerBitMaskPlusEqualOperator)
{
        u8 localtestmem[1], localtestmem2[1];
        crap::bit_mask mask(localtestmem, 1);
        crap::bit_mask mask2(localtestmem2, 1);
        mask.reset();
        mask2.reset();
        localtestmem[0] = 10;
        localtestmem2[0] = 100;
        CHECK( *((u8*)mask.pointer()) == 10 );
        CHECK( *((u8*)mask2.pointer()) == 100 );
        mask += mask2;
        CHECK( *((u8*)mask.pointer()) == 110 );
}

TEST(ContainerBitMaskPlusEqualOperatorVoid)
{
        u8 localtestmem[1], localtestmem2[1];
        crap::bit_mask mask(localtestmem, 1);
        crap::bit_mask mask2(localtestmem2, 1);
        mask.reset();
        mask2.reset();
        localtestmem[0] = 10;
        localtestmem2[0] = 100;
        CHECK( *((u8*)mask.pointer()) == 10 );
        CHECK( *((u8*)mask2.pointer()) == 100 );
        mask += mask2.pointer();
        CHECK( *((u8*)mask.pointer()) == 110 );
}

TEST(ContainerBitMaskMinusEqualOperator)
{
        u8 localtestmem[1], localtestmem2[1];
        crap::bit_mask mask(localtestmem, 1);
        crap::bit_mask mask2(localtestmem2, 1);
        mask.reset();
        mask2.reset();
        localtestmem[0] = 95;
        localtestmem2[0] = 15;

//      std::cout << mask << " " << (u32)*((u8*)mask.pointer()) << std::endl;
//      std::cout << mask2 << " " << (u32)*((u8*)mask2.pointer()) << std::endl;

        CHECK( *((u8*)mask.pointer()) == 95 );
        CHECK( *((u8*)mask2.pointer()) == 15 );
        mask -= mask2;
        CHECK( *((u8*)mask.pointer()) == 80 );
}

TEST(TestBitMaskMinusEqualOperatorVoid)
{
        u8 localtestmem[1], localtestmem2[1];
        crap::bit_mask mask(localtestmem, 1);
        crap::bit_mask mask2(localtestmem2, 1);
        mask.reset();
        mask2.reset();
        localtestmem[0] = 95;
        localtestmem2[0] = 15;

//      std::cout << mask << " " << (u32)*((u8*)mask.pointer()) << std::endl;
//      std::cout << mask2 << " " << (u32)*((u8*)mask2.pointer()) << std::endl;

        CHECK( *((u8*)mask.pointer()) == 95 );
        CHECK( *((u8*)mask2.pointer()) == 15 );
        mask -= mask2.pointer();
        CHECK( *((u8*)mask.pointer()) == 80 );
}

TEST(TestBitMaskComparsionOperator)
{
        _bitmask->reset();
        _bitmask_memory[0] = 10;
        crap::bit_mask mask(_bitmask_memory, 80);
        CHECK(mask == *_bitmask);
}

TEST(TestBitMaskComparsionOperatorVoid)
{
        _bitmask->reset();
        _bitmask_memory[0] = 10;
        crap::bit_mask mask(_bitmask_memory, 10);
        CHECK(mask == _bitmask->pointer());
}

TEST(TestBitMaskIndexOperator)
{
        _bitmask->reset();
        _bitmask_memory[0] = 10;
        CHECK_EQUAL( false, (*_bitmask)[0]);
        CHECK_EQUAL( true, (*_bitmask)[1]);
        CHECK_EQUAL( false, (*_bitmask)[2]);
        CHECK_EQUAL( true, (*_bitmask)[3]);
}

TEST(TestBitMaskTest)
{
//      std::cout << *_mask << std::endl;
       // CHECK_EQUAL(true, _bitmask->test());
        _bitmask->reset();
//      std::cout << *_mask << std::endl;
        CHECK_EQUAL(false, _bitmask->test());
}

TEST(TestBitMaskTestPosition)
{
        CHECK_EQUAL(false, _bitmask->test(1));
        _bitmask_memory[0] = 10;
        CHECK_EQUAL(true, _bitmask->test(1));
}

TEST(TestBitMaskSet)
{
        CHECK_EQUAL(false, _bitmask->test(0));
        _bitmask->set();
        CHECK_EQUAL(true, _bitmask->test(0));
//      std::cout << *_mask << std::endl;
}

TEST(TestBitMaskSetPosition)
{
        _bitmask->reset();
        CHECK_EQUAL(false, _bitmask->test(3));
        _bitmask->set(3);
        CHECK_EQUAL(true, _bitmask->test(3));
//      std::cout << *_mask << std::endl;
}


TEST(TestBitMaskSetFromToLength)
{
        _bitmask->reset();
        CHECK_EQUAL(false, _bitmask->test(3));
        CHECK_EQUAL(false, _bitmask->test(4));
        CHECK_EQUAL(false, _bitmask->test(5));
        CHECK_EQUAL(false, _bitmask->test(6));
        _bitmask->set(4,2);
        CHECK_EQUAL(false, _bitmask->test(3));
        CHECK_EQUAL(true, _bitmask->test(4));
        CHECK_EQUAL(true, _bitmask->test(5));
        CHECK_EQUAL(false, _bitmask->test(6));
//      std::cout << *_mask << std::endl;
}

TEST(TestBitMaskReset)
{
        CHECK_EQUAL(true, _bitmask->test(4));
        CHECK_EQUAL(true, _bitmask->test(5));
        _bitmask->reset();
        CHECK_EQUAL(false, _bitmask->test(4));
        CHECK_EQUAL(false, _bitmask->test(5));
//      std::cout << *_mask << std::endl;
}

TEST(TestBitMaskResetPosition)
{
        _bitmask->set();
        CHECK_EQUAL(true, _bitmask->test(4));
        _bitmask->reset(4);
        CHECK_EQUAL(false, _bitmask->test(4));
//      std::cout << *_mask << std::endl;
}

TEST(TestBitMaskResetFromLength)
{
        _bitmask->set();
        CHECK_EQUAL(true, _bitmask->test(3));
        CHECK_EQUAL(true, _bitmask->test(4));
        CHECK_EQUAL(true, _bitmask->test(5));
        CHECK_EQUAL(true, _bitmask->test(6));
        _bitmask->reset(4, 2);
        CHECK_EQUAL(true, _bitmask->test(3));
        CHECK_EQUAL(false, _bitmask->test(4));
        CHECK_EQUAL(false, _bitmask->test(5));
        CHECK_EQUAL(true, _bitmask->test(6));
//      std::cout << *_mask << std::endl;
}

TEST(TestBitMaskFlip)
{
        _bitmask->set();
        CHECK_EQUAL(true, _bitmask->test(3));
        CHECK_EQUAL(true, _bitmask->test(4));
        CHECK_EQUAL(true, _bitmask->test(5));
        _bitmask->reset(4);
        CHECK_EQUAL(true, _bitmask->test(3));
        CHECK_EQUAL(false, _bitmask->test(4));
        CHECK_EQUAL(true, _bitmask->test(5));
        _bitmask->flip();
        CHECK_EQUAL(false, _bitmask->test(3));
        CHECK_EQUAL(true, _bitmask->test(4));
        CHECK_EQUAL(false, _bitmask->test(5));
//      std::cout << *_mask << std::endl;
}

TEST(TestBitMaskFlipPosition)
{
        CHECK_EQUAL(true, _bitmask->test(4));
        _bitmask->flip(4);
        CHECK_EQUAL(false, _bitmask->test(4));
        _bitmask->flip(4);
        CHECK_EQUAL(true, _bitmask->test(4));
}

TEST(TestBitMaskFirstSet)
{
        _bitmask->reset();
        _bitmask->set(4);
        CHECK_EQUAL(4, _bitmask->find_set());
}

TEST(TestBitMaskFirstSetFromLength)
{
        _bitmask->reset();
        _bitmask->set(1);
        _bitmask->set(4);
        CHECK_EQUAL(4, _bitmask->find_set(2, 4));
}

TEST(TestBitMaskFirstUnSet)
{
        _bitmask->set();
        _bitmask->reset(4);
        CHECK_EQUAL(4, _bitmask->find_unset());
}

TEST(TestBitMaskFirstUnSetFromLength)
{
        _bitmask->set();
        _bitmask->reset(1);
        _bitmask->reset(4);
        CHECK_EQUAL(4, _bitmask->find_unset(2, 4));
}

TEST(TestBitMaskPointer)
{
	crap::bit_mask tmp( *_bitmask );
	CHECK_EQUAL(tmp.pointer(), _bitmask->pointer());
}

TEST(ContainerBitmaskDestruct)
{
	std::cout << "\tDestruction" << std::endl;
    delete _bitmask;
    delete[] _bitmask_memory;
}

}   // namespace
