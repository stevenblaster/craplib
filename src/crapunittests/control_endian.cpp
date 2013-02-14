#include "UnitTest++.h"

//lib includes
#include "control/endian.h"

namespace
{

TEST(ControlEndianTitle)
{
    std::cout << "Testing \"control/endian.h\"" << std::endl;
}

TEST(ControlEndianCheckingByteOrder)
{
	std::cout << "\tChecking byte order: " << crap::endian::check_endian() << std::endl;
}

TEST(ControlEndianIsBigEndian)
{
	std::cout << "\tIs big endian?: " << crap::endian::is_big() << std::endl;
}

TEST(ControlEndianIsLittleEndian)
{
	std::cout << "\tIs little endian?: " << crap::endian::is_little() << std::endl;
}

TEST(ControlCheckingByteSwap)
{
	std::cout << "\tChecking byte swap methods" << std::endl;

	c8 testbytes[3];
	testbytes[0] = 1;
	testbytes[1] = 0;
	testbytes[2] = 0;

	crap::endian::swap_bytes<3>( testbytes );

	CHECK_EQUAL( 0, testbytes[0] );
	CHECK_EQUAL( 0, testbytes[1] );
	CHECK_EQUAL( 1, testbytes[2] );
}

TEST(ControlCheckingSwap2)
{
	struct test_struct
	{
		c8 bytes[2];
	};

	test_struct tb;
	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

	tb = crap::endian::swap<test_struct>( tb );

	CHECK_EQUAL( 0, tb.bytes[0] );
	CHECK_EQUAL( 1, tb.bytes[1] );
}

TEST(ControlCheckingSwap3)
{
	struct test_struct
	{
		c8 bytes[3];
	};

	test_struct tb;
	tb.bytes[0] = 1;
	tb.bytes[1] = 0;
	tb.bytes[2] = 0;

	tb = crap::endian::swap<test_struct>( tb );

	CHECK_EQUAL( 0, tb.bytes[0] );
	CHECK_EQUAL( 0, tb.bytes[1] );
	CHECK_EQUAL( 1, tb.bytes[2] );
}

TEST(ControlCheckingSwap4)
{
	struct test_struct
	{
		c8 bytes[4];
	};

	test_struct tb;
	tb.bytes[0] = 0;
	tb.bytes[1] = 1;
	tb.bytes[2] = 0;
	tb.bytes[3] = 0;

	tb = crap::endian::swap<test_struct>( tb );

	CHECK_EQUAL( 0, tb.bytes[0] );
	CHECK_EQUAL( 0, tb.bytes[1] );
	CHECK_EQUAL( 1, tb.bytes[2] );
	CHECK_EQUAL( 0, tb.bytes[3] );
}

TEST(ControlCheckingSwap8)
{
	struct test_struct
	{
		c8 bytes[8];
	};

	test_struct tb;
	tb.bytes[0] = 0;
	tb.bytes[1] = 1;
	tb.bytes[2] = 0;
	tb.bytes[3] = 1;
	tb.bytes[4] = 0;
	tb.bytes[5] = 1;
	tb.bytes[6] = 0;
	tb.bytes[7] = 1;

	tb = crap::endian::swap<test_struct>( tb );

	CHECK_EQUAL( 1, tb.bytes[0] );
	CHECK_EQUAL( 0, tb.bytes[1] );
	CHECK_EQUAL( 1, tb.bytes[2] );
	CHECK_EQUAL( 0, tb.bytes[3] );
	CHECK_EQUAL( 1, tb.bytes[4] );
	CHECK_EQUAL( 0, tb.bytes[5] );
	CHECK_EQUAL( 1, tb.bytes[6] );
	CHECK_EQUAL( 0, tb.bytes[7] );
}

TEST(ControlCheckingToBig)
{
	struct test_struct
	{
		c8 bytes[2];
	};

	test_struct tb;
	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

	tb = crap::endian::to_big( tb );

	CHECK_EQUAL( 0, tb.bytes[0] );
	CHECK_EQUAL( 1, tb.bytes[1] );
}

TEST(ControlCheckingToLittle)
{
	struct test_struct
	{
		c8 bytes[2];
	};

	test_struct tb;
	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

	tb = crap::endian::to_little( tb );

	CHECK_EQUAL( 1, tb.bytes[0] );
	CHECK_EQUAL( 0, tb.bytes[1] );
}

TEST(ControlCheckingBigToLocal)
{
	struct test_struct
	{
		c8 bytes[2];
	};

	test_struct tb;
	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

	tb = crap::endian::big_to_local( tb );

	CHECK_EQUAL( 0, tb.bytes[0] );
	CHECK_EQUAL( 1, tb.bytes[1] );
}

TEST(ControlCheckingLittleToLocal)
{
	struct test_struct
	{
		c8 bytes[2];
	};

	test_struct tb;
	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

	tb = crap::endian::little_to_local( tb );

	CHECK_EQUAL( 1, tb.bytes[0] );
	CHECK_EQUAL( 0, tb.bytes[1] );
}

}   // namespace
