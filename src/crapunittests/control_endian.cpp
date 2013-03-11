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
    union
    {
        i16 value;
        c8 bytes[2];
    } tb;

	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

    tb.value = crap::endian::swap<i16>( tb.value );

	CHECK_EQUAL( 0, tb.bytes[0] );
	CHECK_EQUAL( 1, tb.bytes[1] );
}

TEST(ControlCheckingSwap3)
{
    union
    {
        i32 value;
        c8 bytes[3];
    } tb;

	tb.value = 0;
    tb.bytes[0] = 0;
    tb.bytes[1] = 1;
	tb.bytes[2] = 0;

    tb.value = crap::endian::swap<i32>( tb.value );

	CHECK_EQUAL( 0, (int)tb.bytes[0] );
	CHECK_EQUAL( 0, tb.bytes[1] );
	CHECK_EQUAL( 1, tb.bytes[2] );
}

TEST(ControlCheckingSwap4)
{
    union
    {
        i32 value;
        c8 bytes[4];
    } tb;

	tb.bytes[0] = 0;
	tb.bytes[1] = 1;
	tb.bytes[2] = 0;
    tb.bytes[3] = 1;

    tb.value = crap::endian::swap<i32>( tb.value );

    CHECK_EQUAL( 1, tb.bytes[0] );
	CHECK_EQUAL( 0, tb.bytes[1] );
	CHECK_EQUAL( 1, tb.bytes[2] );
	CHECK_EQUAL( 0, tb.bytes[3] );
}

TEST(ControlCheckingSwap8)
{
    union
	{
        i64 value;
		c8 bytes[8];
    } tb;


	tb.bytes[0] = 0;
	tb.bytes[1] = 1;
	tb.bytes[2] = 0;
	tb.bytes[3] = 1;
	tb.bytes[4] = 0;
	tb.bytes[5] = 1;
	tb.bytes[6] = 0;
	tb.bytes[7] = 1;

    tb.value = crap::endian::swap<i64>( tb.value );

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
    union
    {
        i16 value;
        c8 bytes[2];
    } tb;

	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

    tb.value = crap::endian::to_big( tb.value );

#if defined( CRAP_ENDIAN_LITTLE )
	CHECK_EQUAL( 0, tb.bytes[0] );
	CHECK_EQUAL( 1, tb.bytes[1] );
#else
    CHECK_EQUAL( 1, tb.bytes[0] );
    CHECK_EQUAL( 0, tb.bytes[1] );
#endif
}

TEST(ControlCheckingToLittle)
{
    union
    {
        i16 value;
        c8 bytes[2];
    } tb;

	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

    tb.value = crap::endian::to_little( tb.value );

#if defined( CRAP_ENDIAN_LITTLE )
    CHECK_EQUAL( 1, tb.bytes[0] );
    CHECK_EQUAL( 0, tb.bytes[1] );
#else
    CHECK_EQUAL( 0, tb.bytes[0] );
    CHECK_EQUAL( 1, tb.bytes[1] );
#endif
}

TEST(ControlCheckingBigToLocal)
{
    union
    {
        i16 value;
        c8 bytes[2];
    } tb;

	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

    tb.value = crap::endian::big_to_local( tb.value );

#if defined( CRAP_ENDIAN_LITTLE )
    CHECK_EQUAL( 0, tb.bytes[0] );
    CHECK_EQUAL( 1, tb.bytes[1] );
#else
    CHECK_EQUAL( 1, tb.bytes[0] );
    CHECK_EQUAL( 0, tb.bytes[1] );
#endif
}

TEST(ControlCheckingLittleToLocal)
{
    union
    {
        i16 value;
        c8 bytes[2];
    } tb;

	tb.bytes[0] = 1;
	tb.bytes[1] = 0;

    tb.value = crap::endian::little_to_local( tb.value );

#if defined( CRAP_ENDIAN_LITTLE )
    CHECK_EQUAL( 1, tb.bytes[0] );
    CHECK_EQUAL( 0, tb.bytes[1] );
#else
    CHECK_EQUAL( 0, tb.bytes[0] );
    CHECK_EQUAL( 1, tb.bytes[1] );
#endif
}

}   // namespace
