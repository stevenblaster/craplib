
#include "UnitTest++.h"

//lib includes
#include "config/types.h"

namespace
{

TEST(ConfigTypesTitle)
{
    std::cout << "Testing \"config/types.h\"" << std::endl;
}

TEST(ConfigTypesSize)
{
	std::cout << "\tSize fo Types" << std::endl;

	CHECK_EQUAL(1, sizeof(b8));
	CHECK_EQUAL(1, sizeof(c8));
	CHECK_EQUAL(1, sizeof(i8));
	CHECK_EQUAL(1, sizeof(u8));
	CHECK_EQUAL(2, sizeof(i16));
	CHECK_EQUAL(2, sizeof(u16));
	CHECK_EQUAL(4, sizeof(i32));
	CHECK_EQUAL(4, sizeof(u32));
	CHECK_EQUAL(8, sizeof(i64));
	CHECK_EQUAL(8, sizeof(u64));
	CHECK_EQUAL(4, sizeof(f32));
	CHECK_EQUAL(8, sizeof(f64));
	CHECK_EQUAL(16, sizeof(u128));
	CHECK_EQUAL(4, sizeof(size_t32));
	CHECK_EQUAL(8, sizeof(size_t64));

}

}   // namespace
