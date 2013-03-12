#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "memory/allocatordefault.h"

namespace
{

crap::allocator_default<i32>* _alldef;
i32* test_ptr; 

TEST(MemoryAllocatorDefaultTitle)
{
    std::cout << "Testing \"memory/allocatordefault.h\"" << std::endl;
}

TEST(MemoryAllocatorDefaultConstructor)
{
    std::cout << "\tConstruction" << std::endl;
	_alldef = new crap::allocator_default<i32>();
}

TEST(MemoryAllocatorCopyConstructor)
{
	crap::allocator_default<i32> tmp( *_alldef );
}

TEST(MemoryAllocatorAddress)
{
	i32 test = 23;
	CHECK_EQUAL( &test, _alldef->address( test ) );
}

TEST(MemoryAllocatorConstAddress)
{
	const i32 test = 23;
	CHECK_EQUAL( &test, _alldef->address( test ) );
}

TEST(MemoryAllocatorAllocateSingle)
{
	test_ptr = _alldef->allocate();
	CHECK_EQUAL( true, test_ptr != 0 );
}

TEST(MemoryAllocatorConstruct)
{
	_alldef->construct( test_ptr, 234 );
	CHECK_EQUAL( 234, *test_ptr );
}

TEST(MemoryAllocatorDestroy)
{
	_alldef->destroy( test_ptr );
	CHECK_EQUAL( 234, *test_ptr );
}

TEST(MemoryAllocatorDeallocateSingle)
{
	_alldef->deallocate( test_ptr );
}

TEST(MemoryAllocatorAllocateMultiple)
{
	test_ptr = _alldef->allocate( 10 );
}

TEST(MemoryAllocatorDeallocateMultiple)
{
	_alldef->deallocate( test_ptr, 10 );
}

TEST(MemoryAllocatorDefaultDestructor)
{
    std::cout << "\tDestruction" << std::endl;
	delete _alldef;
}

}