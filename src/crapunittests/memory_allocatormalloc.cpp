#include "UnitTest++.h"

//lib includes
#include "memory/allocatormalloc.h"

namespace
{

crap::allocator_malloc<i32>* _allmal;
i32* test_ptr2; 

TEST(MemoryAllocatorMallocTitle)
{
    std::cout << "Testing \"memory/allocatormalloc.h\"" << std::endl;
}

TEST(MemoryAllocatorMallocConstructor)
{
    std::cout << "\tConstruction" << std::endl;
	_allmal = new crap::allocator_malloc<i32>();
}

TEST(MemoryAllocatorMallocCopyConstructor)
{
	crap::allocator_malloc<i32> tmp( *_allmal );
}

TEST(MemoryAllocatorMallocAddress)
{
	i32 test = 23;
	CHECK_EQUAL( &test, _allmal->address( test ) );
}

TEST(MemoryAllocatorMallocConstAddress)
{
	const i32 test = 23;
	CHECK_EQUAL( &test, _allmal->address( test ) );
}

TEST(MemoryAllocatorMallocAllocateSingle)
{
	test_ptr2 = _allmal->allocate();
	CHECK_EQUAL( true, test_ptr2 != 0 );
}

TEST(MemoryAllocatorMallocConstruct)
{
	_allmal->construct( test_ptr2, 234 );
	CHECK_EQUAL( 234, *test_ptr2 );
}

TEST(MemoryAllocatorMallocDestroy)
{
	_allmal->destroy( test_ptr2 );
	CHECK_EQUAL( 234, *test_ptr2 );
}

TEST(MemoryAllocatorMallocDeallocateSingle)
{
	_allmal->deallocate( test_ptr2 );
}

TEST(MemoryAllocatorMallocAllocateMultiple)
{
	test_ptr2 = _allmal->allocate( 10 );
}

TEST(MemoryAllocatorDeallocateMultiple)
{
	_allmal->deallocate( test_ptr2, 10 );
}

TEST(MemoryAllocatorMallocDestructor)
{
    std::cout << "\tDestruction" << std::endl;
	delete _allmal;
}

}