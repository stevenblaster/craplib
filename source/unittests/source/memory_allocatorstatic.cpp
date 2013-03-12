#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "memory/allocatorstatic.h"

namespace
{

crap::allocator_static<i32, 10>* _allsta;
i32* test_prt3; 

TEST(MemoryAllocatorStaticTitle)
{
    std::cout << "Testing \"memory/allocatordefault.h\"" << std::endl;
}

TEST(MemoryAllocatorStaticConstructor)
{
    std::cout << "\tConstruction" << std::endl;
	_allsta = new crap::allocator_static<i32, 10>();
}

TEST(MemoryAllocatorStaticCopyConstructor)
{
	crap::allocator_static<i32, 10> tmp( *_allsta );
}

TEST(MemoryAllocatorStaticAddress)
{
	i32 test = 23;
	CHECK_EQUAL( &test, _allsta->address( test ) );
}

TEST(MemoryAllocatorStaticConstAddress)
{
	const i32 test = 23;
	CHECK_EQUAL( &test, _allsta->address( test ) );
}

TEST(MemoryAllocatorStaticAllocateSingle)
{
	test_prt3 = _allsta->allocate();
	CHECK_EQUAL( true, test_prt3 != 0 );
}

TEST(MemoryAllocatorStaticConstruct)
{
	_allsta->construct( test_prt3, 234 );
	CHECK_EQUAL( 234, *test_prt3 );
}

TEST(MemoryAllocatorStaticDestroy)
{
	_allsta->destroy( test_prt3 );
	CHECK_EQUAL( 234, *test_prt3 );
}

TEST(MemoryAllocatorStaticDeallocateSingle)
{
	_allsta->deallocate( test_prt3 );
}

TEST(MemoryAllocatorStaticAllocateMultiple)
{
	test_prt3 = _allsta->allocate( 10 );
}

TEST(MemoryAllocatorStaticDeallocateMultiple)
{
	_allsta->deallocate( test_prt3, 10 );
}

TEST(MemoryAllocatorStaticDestructor)
{
    std::cout << "\tDestruction" << std::endl;
	delete _allsta;
}

}