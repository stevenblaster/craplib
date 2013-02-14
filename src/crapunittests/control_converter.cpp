#include "UnitTest++.h"

//lib includes
#include "control/converter.h"

namespace
{

TEST(ConfigConverterTitle)
{
    std::cout << "Testing \"control/converter.h\"" << std::endl;
	std::cout << "\tConverting basic types" << std::endl;
}


TEST(ConverterC8C8)
{
	c8 test = 0;
	CHECK_EQUAL( 0, (crap::convert<c8, c8>( test )) );

	test = 25;
	CHECK_EQUAL( 25, (crap::convert<c8, c8>( test )) );

	test = -25;
	CHECK_EQUAL( -25, (crap::convert<c8, c8>( test )) );

	test = -128;
	CHECK_EQUAL( -128, (crap::convert<c8, c8>( test )) );

	test = 127;
	CHECK_EQUAL( 127, (crap::convert<c8, c8>( test )) );
}

TEST(ConverterC8I8)
{
        c8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<c8, i8>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<c8, i8>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<c8, i8>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<c8, i8>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<c8, i8>( test )) );
}

TEST(ConverterC8U8)
{
        c8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<c8, u8>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<c8, u8>( test )) );

        test = -25;
        CHECK_EQUAL( 0, (crap::convert<c8, u8>( test )) );

        test = -128;
        CHECK_EQUAL( 0, (crap::convert<c8, u8>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<c8, u8>( test )) );
}

TEST(ConverterC8I16)
{
        c8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<c8, i16>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<c8, i16>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<c8, i16>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<c8, i16>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<c8, i16>( test )) );
}

TEST(ConverterC8U16)
{
        c8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<c8, u16>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<c8, u16>( test )) );

        test = -25;
        CHECK_EQUAL( 0, (crap::convert<c8, u16>( test )) );

        test = -128;
        CHECK_EQUAL( 0, (crap::convert<c8, u16>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<c8, u16>( test )) );
}

TEST(ConverterC8I32)
{
        c8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<c8, i32>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<c8, i32>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<c8, i32>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<c8, i32>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<c8, i32>( test )) );
}

TEST(ConverterC8U32)
{
        c8 test = 0;
        CHECK_EQUAL( (u32)0, (crap::convert<c8, u32>( test )) );

        test = 25;
        CHECK_EQUAL( (u32)25, (crap::convert<c8, u32>( test )) );

        test = -25;
        CHECK_EQUAL( (u32)0, (crap::convert<c8, u32>( test )) );

        test = -128;
        CHECK_EQUAL( (u32)0, (crap::convert<c8, u32>( test )) );

        test = 127;
        CHECK_EQUAL( (u32)127, (crap::convert<c8, u32>( test )) );
}

TEST(ConverterC8I64)
{
        c8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<c8, i64>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<c8, i64>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<c8, i64>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<c8, i64>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<c8, i64>( test )) );
}

TEST(ConverterC8U64)
{
        c8 test = 0;
        CHECK_EQUAL( (u64)0, (crap::convert<c8, u64>( test )) );

        test = 25;
        CHECK_EQUAL( (u64)25, (crap::convert<c8, u64>( test )) );

        test = -25;
        CHECK_EQUAL( (u64)0, (crap::convert<c8, u64>( test )) );

        test = -128;
        CHECK_EQUAL( (u64)0, (crap::convert<c8, u64>( test )) );

        test = 127;
        CHECK_EQUAL( (u64)127, (crap::convert<c8, u64>( test )) );
}

TEST(ConverterC8F32)
{
        c8 test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<c8, f32>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0f, (crap::convert<c8, f32>( test )) );

        test = -25;
        CHECK_EQUAL( -25.0f, (crap::convert<c8, f32>( test )) );

        test = -128;
        CHECK_EQUAL( -128.0f, (crap::convert<c8, f32>( test )) );

        test = 127;
        CHECK_EQUAL( 127.0f, (crap::convert<c8, f32>( test )) );
}

TEST(ConverterC8F64)
{
        c8 test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<c8, f64>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0, (crap::convert<c8, f64>( test )) );

        test = -25;
        CHECK_EQUAL( -25.0, (crap::convert<c8, f64>( test )) );

        test = -128;
        CHECK_EQUAL( -128.0, (crap::convert<c8, f64>( test )) );

        test = 127;
        CHECK_EQUAL( 127.0, (crap::convert<c8, u64>( test )) );
}

//I8
TEST(ConverterI8C8)
{
        i8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i8, c8>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<i8, c8>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<i8, c8>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<i8, c8>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<i8, c8>( test )) );
}

TEST(ConverterI8I8)
{
        i8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i8, i8>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<i8, i8>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<i8, i8>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<i8, i8>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<i8, i8>( test )) );
}

TEST(ConverterI8U8)
{
        i8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i8, u8>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<i8, u8>( test )) );

        test = -25;
        CHECK_EQUAL( 0, (crap::convert<i8, u8>( test )) );

        test = -128;
        CHECK_EQUAL( 0, (crap::convert<i8, u8>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<i8, u8>( test )) );
}

TEST(ConverterI8I16)
{
        i8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i8, i16>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<i8, i16>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<i8, i16>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<i8, i16>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<i8, i16>( test )) );
}

TEST(ConverterI8U16)
{
        i8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i8, u16>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<i8, u16>( test )) );

        test = -25;
        CHECK_EQUAL( 0, (crap::convert<i8, u16>( test )) );

        test = -128;
        CHECK_EQUAL( 0, (crap::convert<i8, u16>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<i8, u16>( test )) );
}

TEST(ConverterI8I32)
{
        i8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i8, i32>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<i8, i32>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<i8, i32>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<i8, i32>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<i8, i32>( test )) );
}

TEST(ConverterI8U32)
{
        i8 test = 0;
        CHECK_EQUAL( (u32)0, (crap::convert<i8, u32>( test )) );

        test = 25;
        CHECK_EQUAL( (u32)25, (crap::convert<i8, u32>( test )) );

        test = -25;
        CHECK_EQUAL( (u32)0, (crap::convert<i8, u32>( test )) );

        test = -128;
        CHECK_EQUAL( (u32)0, (crap::convert<i8, u32>( test )) );

        test = 127;
        CHECK_EQUAL( (u32)127, (crap::convert<i8, u32>( test )) );
}

TEST(ConverterI8I64)
{
        i8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i8, i64>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<i8, i64>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<i8, i64>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<i8, i64>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<i8, i64>( test )) );
}

TEST(ConverterI8U64)
{
        i8 test = 0;
        CHECK_EQUAL( (u64)0, (crap::convert<i8, u64>( test )) );

        test = 25;
        CHECK_EQUAL( (u64)25, (crap::convert<i8, u64>( test )) );

        test = -25;
        CHECK_EQUAL( (u64)0, (crap::convert<i8, u64>( test )) );

        test = -128;
        CHECK_EQUAL( (u64)0, (crap::convert<i8, u64>( test )) );

        test = 127;
        CHECK_EQUAL( (u64)127, (crap::convert<i8, u64>( test )) );
}

TEST(ConverterI8F32)
{
        i8 test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<i8, f32>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0f, (crap::convert<i8, f32>( test )) );

        test = -25;
        CHECK_EQUAL( -25.0f, (crap::convert<i8, f32>( test )) );

        test = -128;
        CHECK_EQUAL( -128.0f, (crap::convert<i8, f32>( test )) );

        test = 127;
        CHECK_EQUAL( 127.0f, (crap::convert<i8, f32>( test )) );
}

TEST(ConverterI8F64)
{
        i8 test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<i8, f64>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0, (crap::convert<i8, f64>( test )) );

        test = -25;
        CHECK_EQUAL( -25.0, (crap::convert<i8, f64>( test )) );

        test = -128;
        CHECK_EQUAL( -128.0, (crap::convert<i8, f64>( test )) );

        test = 127;
        CHECK_EQUAL( 127.0, (crap::convert<i8, u64>( test )) );
}

//u8
TEST(ConverterU8C8)
{
        u8 test = 0;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<u8, c8>( test )) );

        test = 25;
        CHECK_EQUAL( (i32)25, (i32)(crap::convert<u8, c8>( test )) );

        test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u8, c8>( test )) );
}

TEST(ConverterU8I8)
{
        u8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<u8, i8>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<u8, i8>( test )) );

        test = 255;
        CHECK_EQUAL( 127, (crap::convert<u8, i8>( test )) );
}

TEST(ConverterU8U8)
{
        u8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<u8, u8>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<u8, u8>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<u8, u8>( test )) );
}

TEST(ConverterU8I16)
{
        u8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<u8, i16>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<u8, i16>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<u8, i16>( test )) );
}

TEST(ConverterU8U16)
{
        u8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<u8, u16>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<u8, u16>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<u8, u16>( test )) );
}

TEST(ConverterU8I32)
{
        u8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<u8, i32>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<u8, i32>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<u8, i32>( test )) );
}

TEST(ConverterU8U32)
{
        u8 test = 0;
        CHECK_EQUAL( (u32)0, (crap::convert<u8, u32>( test )) );

        test = 25;
        CHECK_EQUAL( (u32)25, (crap::convert<u8, u32>( test )) );

        test = 255;
        CHECK_EQUAL( (u32)255, (crap::convert<u8, u32>( test )) );
}

TEST(ConverterU8I64)
{
        u8 test = 0;
        CHECK_EQUAL( 0, (crap::convert<u8, i64>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<u8, i64>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<u8, i64>( test )) );
}

TEST(ConverterU8U64)
{
        u8 test = 0;
        CHECK_EQUAL( (u64)0, (crap::convert<u8, u64>( test )) );

        test = 25;
        CHECK_EQUAL( (u64)25, (crap::convert<u8, u64>( test )) );

        test = 255;
        CHECK_EQUAL( (u64)255, (crap::convert<u8, u64>( test )) );
}

TEST(ConverterU8F32)
{
        u8 test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<u8, f32>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0f, (crap::convert<u8, f32>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<u8, f32>( test )) );
}

TEST(ConverterU8F64)
{
        u8 test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<u8, f64>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0, (crap::convert<u8, f64>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<u8, u64>( test )) );
}

//i16
TEST(ConverterI16C8)
{
        i16 test = 0;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<i16, c8>( test )) );

        test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<i16, c8>( test )) );

        test = -255;
        CHECK_EQUAL( (i32)-128, (i32)(crap::convert<i16, c8>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<i16, c8>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( (i32)-128, (i32)(crap::convert<i16, c8>( test )) );
}

TEST(ConverterI16I8)
{
        i16 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i16, i8>( test )) );

        test = 255;
        CHECK_EQUAL( 127, (crap::convert<i16, i8>( test )) );

        test = -255;
        CHECK_EQUAL( -128, (crap::convert<i16, i8>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( 127, (crap::convert<i16, i8>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( -128, (crap::convert<i16, i8>( test )) );
}

TEST(ConverterI16U8)
{
        i16 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i16, u8>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i16, u8>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<i16, u8>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( 255, (crap::convert<i16, u8>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( 0, (crap::convert<i16, u8>( test )) );
}

TEST(ConverterI16I16)
{
        i16 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i16, i16>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i16, i16>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i16, i16>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<i16, i16>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( I16_MIN, (crap::convert<i16, i16>( test )) );
}

TEST(ConverterI16U16)
{
        i16 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i16, u16>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i16, u16>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<i16, u16>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<i16, u16>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( 0, (crap::convert<i16, u16>( test )) );
}

TEST(ConverterI16I32)
{
        i16 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i16, i32>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i16, i32>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i16, i32>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<i16, i32>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( I16_MIN, (crap::convert<i16, i32>( test )) );
}

TEST(ConverterI16U32)
{
        i16 test = 0;
        CHECK_EQUAL( (u32)0, (crap::convert<i16, u32>( test )) );

        test = 255;
        CHECK_EQUAL( (u32)255, (crap::convert<i16, u32>( test )) );

        test = -255;
        CHECK_EQUAL( (u32)0, (crap::convert<i16, u32>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( (u32)I16_MAX, (crap::convert<i16, u32>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( (u32)0, (crap::convert<i16, u32>( test )) );
}

TEST(ConverterI16I64)
{
        i16 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i16, i64>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i16, i64>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i16, i64>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<i16, i64>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( I16_MIN, (crap::convert<i16, i64>( test )) );
}

TEST(ConverterI16U64)
{
        i16 test = 0;
        CHECK_EQUAL( (u64)0, (crap::convert<i16, u64>( test )) );

        test = 255;
        CHECK_EQUAL( (u64)255, (crap::convert<i16, u64>( test )) );

        test = -255;
        CHECK_EQUAL( (u64)0, (crap::convert<i16, u64>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( (u64)I16_MAX, (crap::convert<i16, u64>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( (u64)0, (crap::convert<i16, u64>( test )) );
}

TEST(ConverterI16F32)
{
        i16 test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<i16, f32>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<i16, f32>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0f, (crap::convert<i16, f32>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<i16, f32>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( I16_MIN, (crap::convert<i16, f32>( test )) );
}

TEST(Converteri16F64)
{
        i16 test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<i16, f64>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<i16, f64>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0, (crap::convert<i16, f64>( test )) );

        test = I16_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<i16, f64>( test )) );

        test = I16_MIN;
        CHECK_EQUAL( I16_MIN, (crap::convert<i16, f64>( test )) );
}

//U16
TEST(ConverterU16C8)
{
        u16 test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u16, c8>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u16, c8>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<u16, c8>( test )) );
}

TEST(ConverterU16I8)
{
        u16 test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u16, i8>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u16, i8>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<u16, i8>( test )) );
}

TEST(ConverterU16U8)
{
        u16 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u16, u8>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( 255, (crap::convert<u16, u8>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( 0, (crap::convert<u16, u8>( test )) );
}

TEST(ConverterU16I16)
{
        u16 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u16, i16>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<u16, i16>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( 0, (crap::convert<u16, i16>( test )) );
}

TEST(ConverterU16U16)
{
        u16 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u16, u16>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( U16_MAX, (crap::convert<u16, u16>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( 0, (crap::convert<u16, u16>( test )) );
}

TEST(ConverterU16I32)
{
        u16 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u16, i32>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( U16_MAX, (crap::convert<u16, i32>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( U16_MIN, (crap::convert<u16, i32>( test )) );
}

TEST(ConverterU16U32)
{
        u16 test = 255;
        CHECK_EQUAL( (u32)255, (crap::convert<u16, u32>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( (u32)U16_MAX, (crap::convert<u16, u32>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( (u32)0, (crap::convert<u16, u32>( test )) );
}

TEST(ConverterU16I64)
{
        u16 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u16, i64>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( U16_MAX, (crap::convert<u16, i64>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( U16_MIN, (crap::convert<u16, i64>( test )) );
}

TEST(ConverterU16U64)
{
        u16 test = 255;
        CHECK_EQUAL( (u64)255, (crap::convert<u16, u64>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( (u64)U16_MAX, (crap::convert<u16, u64>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( (u64)0, (crap::convert<u16, u64>( test )) );
}

TEST(ConverterU16F32)
{
        u16 test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<u16, f32>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( 65535.0f, (crap::convert<u16, f32>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( 0.f, (crap::convert<u16, f32>( test )) );
}

TEST(ConverterU16F64)
{
        u16 test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<u16, f64>( test )) );

        test = U16_MAX;
        CHECK_EQUAL( U16_MAX, (crap::convert<u16, f64>( test )) );

        test = U16_MIN;
        CHECK_EQUAL( U16_MIN, (crap::convert<u16, f64>( test )) );
}


//i32
TEST(ConverterI32C8)
{
        i32 test = 0;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<i32, c8>( test )) );

        test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<i32, c8>( test )) );

        test = -255;
        CHECK_EQUAL( (i32)-128, (i32)(crap::convert<i32, c8>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<i32, c8>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( (i32)-128, (i32)(crap::convert<i32, c8>( test )) );
}

TEST(ConverterI32I8)
{
        i32 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i32, i8>( test )) );

        test = 255;
        CHECK_EQUAL( 127, (crap::convert<i32, i8>( test )) );

        test = -255;
        CHECK_EQUAL( -128, (crap::convert<i32, i8>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( 127, (crap::convert<i32, i8>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( -128, (crap::convert<i32, i8>( test )) );
}

TEST(ConverterI32U8)
{
        i32 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i32, u8>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i32, u8>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<i32, u8>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( 255, (crap::convert<i32, u8>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( 0, (crap::convert<i32, u8>( test )) );
}

TEST(ConverterI32I16)
{
        i32 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i32, i16>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i32, i16>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i32, i16>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<i32, i16>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( I16_MIN, (crap::convert<i32, i16>( test )) );
}

TEST(ConverterI32U16)
{
        i32 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i32, u16>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i32, u16>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<i32, u16>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( U16_MAX, (crap::convert<i32, u16>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( 0, (crap::convert<i32, u16>( test )) );
}

TEST(ConverterI32I32)
{
        i32 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i32, i32>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i32, i32>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i32, i32>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( I32_MAX, (crap::convert<i32, i32>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( I32_MIN, (crap::convert<i32, i32>( test )) );
}

TEST(ConverterI32U32)
{
        i32 test = 0;
        CHECK_EQUAL( (u32)0, (crap::convert<i32, u32>( test )) );

        test = 255;
        CHECK_EQUAL( (u32)255, (crap::convert<i32, u32>( test )) );

        test = -255;
        CHECK_EQUAL( (u32)0, (crap::convert<i32, u32>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( (u32)I32_MAX, (crap::convert<i32, u32>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( (u32)0, (crap::convert<i32, u32>( test )) );
}

TEST(ConverterI32I64)
{
        i32 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i32, i64>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i32, i64>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i32, i64>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( I32_MAX, (crap::convert<i32, i64>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( I32_MIN, (crap::convert<i32, i64>( test )) );
}

TEST(ConverterI32U64)
{
        i32 test = 0;
        CHECK_EQUAL( (u64)0, (crap::convert<i32, u64>( test )) );

        test = 255;
        CHECK_EQUAL( (u64)255, (crap::convert<i32, u64>( test )) );

        test = -255;
        CHECK_EQUAL( (u64)0, (crap::convert<i32, u64>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( (u64)I32_MAX, (crap::convert<i32, u64>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( (u64)0, (crap::convert<i32, u64>( test )) );
}

TEST(ConverterI32F32)
{
        i32 test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<i32, f32>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<i32, f32>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0f, (crap::convert<i32, f32>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( static_cast<f32>(I32_MAX),(crap::convert<i32, f32>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( I32_MIN, (crap::convert<i32, f32>( test )) );
}

TEST(ConverterI32F64)
{
        i32 test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<i32, f64>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<i32, f64>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0, (crap::convert<i32, f64>( test )) );

        test = I32_MAX;
        CHECK_EQUAL( (f64)I32_MAX, (crap::convert<i32, f64>( test )) );

        test = I32_MIN;
        CHECK_EQUAL( (f64)I32_MIN, (crap::convert<i32, f64>( test )) );
}


//U32
TEST(ConverterU32C8)
{
        u32 test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u32, c8>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u32, c8>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<u32, c8>( test )) );
}

TEST(ConverterU32I8)
{
        u32 test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u32, i8>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u32, i8>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<u32, i8>( test )) );
}

TEST(ConverterU32U8)
{
        u32 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u32, u8>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( 255, (crap::convert<u32, u8>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( 0, (crap::convert<u32, u8>( test )) );
}

TEST(ConverterU32I16)
{
        u32 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u32, i16>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<u32, i16>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( 0, (crap::convert<u32, i16>( test )) );
}

TEST(ConverterU32U16)
{
        u32 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u32, u16>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( U16_MAX, (crap::convert<u32, u16>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( 0, (crap::convert<u32, u16>( test )) );
}

TEST(ConverterU32I32)
{
        u32 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u32, i32>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( I32_MAX, (crap::convert<u32, i32>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( U32_MIN, (crap::convert<u32, i32>( test )) );
}

TEST(ConverterU32U32)
{
        u32 test = 255;
        CHECK_EQUAL( (u32)255, (crap::convert<u32, u32>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( (u32)U32_MAX, (crap::convert<u32, u32>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( (u32)0, (crap::convert<u32, u32>( test )) );
}

TEST(ConverterU32I64)
{
        u32 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u32, i64>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( U32_MAX, (crap::convert<u32, i64>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( U32_MIN, (crap::convert<u32, i64>( test )) );
}

TEST(ConverterU32U64)
{
        u32 test = 255;
        CHECK_EQUAL( (u64)255, (crap::convert<u32, u64>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( (u64)U32_MAX, (crap::convert<u32, u64>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( (u64)0, (crap::convert<u32, u64>( test )) );
}

TEST(ConverterU32F32)
{
        u32 test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<u32, f32>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( (f32)U32_MAX, (crap::convert<u32, f32>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( 0.f, (crap::convert<u32, f32>( test )) );
}

TEST(ConverterU32F64)
{
        u32 test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<u32, f64>( test )) );

        test = U32_MAX;
        CHECK_EQUAL( U32_MAX, (crap::convert<u32, f64>( test )) );

        test = U32_MIN;
        CHECK_EQUAL( U32_MIN, (crap::convert<u32, f64>( test )) );
}


//i64
TEST(ConverterI64C8)
{
        i64 test = 0;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<i64, c8>( test )) );

        test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<i64, c8>( test )) );

        test = -255;
        CHECK_EQUAL( (i32)-128, (i32)(crap::convert<i64, c8>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<i64, c8>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( (i32)-128, (i32)(crap::convert<i64, c8>( test )) );
}

TEST(ConverterI64I8)
{
        i64 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i64, i8>( test )) );

        test = 255;
        CHECK_EQUAL( 127, (crap::convert<i64, i8>( test )) );

        test = -255;
        CHECK_EQUAL( -128, (crap::convert<i64, i8>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( 127, (crap::convert<i64, i8>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( -128, (crap::convert<i64, i8>( test )) );
}

TEST(ConverterI64U8)
{
        i64 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i64, u8>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i64, u8>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<i64, u8>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( 255, (crap::convert<i64, u8>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( 0, (crap::convert<i64, u8>( test )) );
}

TEST(ConverterI64I16)
{
        i64 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i64, i16>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i64, i16>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i64, i16>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<i64, i16>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( I16_MIN, (crap::convert<i64, i16>( test )) );
}

TEST(ConverterI64U16)
{
        i64 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i64, u16>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i64, u16>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<i64, u16>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( U16_MAX, (crap::convert<i64, u16>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( 0, (crap::convert<i64, u16>( test )) );
}

TEST(ConverterI64I32)
{
        i64 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i64, i32>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i64, i32>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i64, i32>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( I32_MAX, (crap::convert<i64, i32>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( I32_MIN, (crap::convert<i64, i32>( test )) );
}

TEST(ConverterI64U32)
{
        i64 test = 0;
        CHECK_EQUAL( (u32)0, (crap::convert<i64, u32>( test )) );

        test = 255;
        CHECK_EQUAL( (u32)255, (crap::convert<i64, u32>( test )) );

        test = -255;
        CHECK_EQUAL( (u32)0, (crap::convert<i64, u32>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( (u32)I64_MAX, (crap::convert<i64, u32>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( (u32)0, (crap::convert<i64, u32>( test )) );
}

TEST(ConverterI64I64)
{
        i64 test = 0;
        CHECK_EQUAL( 0, (crap::convert<i64, i64>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<i64, i64>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<i64, i64>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( I64_MAX, (crap::convert<i64, i64>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( I64_MIN, (crap::convert<i64, i64>( test )) );
}

TEST(ConverterI64U64)
{
        i64 test = 0;
        CHECK_EQUAL( (u64)0, (crap::convert<i64, u64>( test )) );

        test = 255;
        CHECK_EQUAL( (u64)255, (crap::convert<i64, u64>( test )) );

        test = -255;
        CHECK_EQUAL( (u64)0, (crap::convert<i64, u64>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( (u64)I64_MAX, (crap::convert<i64, u64>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( (u64)0, (crap::convert<i64, u64>( test )) );
}

TEST(ConverterI64F32)
{
        i64 test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<i64, f32>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<i64, f32>( test )) );

        test = -255;
        //CHECK_EQUAL( -255.0f, (crap::convert<i64, f32>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( static_cast<f32>(I64_MAX),(crap::convert<i64, f32>( test )) );

        test = I64_MIN;
        //CHECK_EQUAL( I64_MIN, (crap::convert<i64, f32>( test )) );
}

TEST(ConverterI64F64)
{
        i64 test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<i64, f64>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<i64, f64>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0, (crap::convert<i64, f64>( test )) );

        test = I64_MAX;
        CHECK_EQUAL( (f64)I64_MAX, (crap::convert<i64, f64>( test )) );

        test = I64_MIN;
        CHECK_EQUAL( (f64)I64_MIN, (crap::convert<i64, f64>( test )) );
}



//U64
TEST(ConverterU64C8)
{
        u64 test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u64, c8>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u64, c8>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<u64, c8>( test )) );
}

TEST(ConverterU64I8)
{
        u64 test = 255;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u64, i8>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( (i32)127, (i32)(crap::convert<u64, i8>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( (i32)0, (i32)(crap::convert<u64, i8>( test )) );
}

TEST(ConverterU64U8)
{
        u64 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u64, u8>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( 255, (crap::convert<u64, u8>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( 0, (crap::convert<u64, u8>( test )) );
}

TEST(ConverterU64I16)
{
        u64 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u64, i16>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( I16_MAX, (crap::convert<u64, i16>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( 0, (crap::convert<u64, i16>( test )) );
}

TEST(ConverterU64U16)
{
        u64 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u64, u16>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( U16_MAX, (crap::convert<u64, u16>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( 0, (crap::convert<u64, u16>( test )) );
}

TEST(ConverterU64I32)
{
        u64 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u64, i32>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( I32_MAX, (crap::convert<u64, i32>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( U64_MIN, (crap::convert<u64, i32>( test )) );
}

TEST(ConverterU64U32)
{
        u64 test = 255;
        CHECK_EQUAL( (u32)255, (crap::convert<u64, u32>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( (u32)U32_MAX, (crap::convert<u64, u32>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( (u32)0, (crap::convert<u64, u32>( test )) );
}

TEST(ConverterU64I64)
{
        u64 test = 255;
        CHECK_EQUAL( 255, (crap::convert<u64, i64>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( I64_MAX, (crap::convert<u64, i64>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( U64_MIN, (crap::convert<u64, i64>( test )) );
}

TEST(ConverterU64U64)
{
        u64 test = 255;
        CHECK_EQUAL( (u64)255, (crap::convert<u64, u64>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( (u64)U64_MAX, (crap::convert<u64, u64>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( (u64)0, (crap::convert<u64, u64>( test )) );
}

TEST(ConverterU64F32)
{
        u64 test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<u64, f32>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( (f32)U64_MAX, (crap::convert<u64, f32>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( 0.f, (crap::convert<u64, f32>( test )) );
}

TEST(ConverterU64F64)
{
        u64 test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<u64, f64>( test )) );

        test = U64_MAX;
        CHECK_EQUAL( U64_MAX, (crap::convert<u64, f64>( test )) );

        test = U64_MIN;
        CHECK_EQUAL( U64_MIN, (crap::convert<u64, f64>( test )) );
}


//f32
TEST(ConverterF32C8)
{
	f32 test = 0.0f;
	CHECK_EQUAL( (i32)0, (i32)(crap::convert<f32, c8>( test )) );

	test = 255.f;
	CHECK_EQUAL( (i32)127, (i32)(crap::convert<f32, c8>( test )) );

	test = -255.f;
	CHECK_EQUAL( (i32)-128, (i32)(crap::convert<f32, c8>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( (i32)127, (i32)(crap::convert<f32, c8>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( (i32)-128, (i32)(crap::convert<f32, c8>( test )) );
}

TEST(ConverterF32I8)
{
	f32 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f32, i8>( test )) );

	test = 255;
	CHECK_EQUAL( 127, (crap::convert<f32, i8>( test )) );

	test = -255;
	CHECK_EQUAL( -128, (crap::convert<f32, i8>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( 127, (crap::convert<f32, i8>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( -128, (crap::convert<f32, i8>( test )) );
}

TEST(ConverterF32U8)
{
	f32 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f32, u8>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f32, u8>( test )) );

	test = -255;
	CHECK_EQUAL( 0, (crap::convert<f32, u8>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( 255, (crap::convert<f32, u8>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( 0, (crap::convert<f32, u8>( test )) );
}

TEST(ConverterF32I16)
{
	f32 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f32, i16>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f32, i16>( test )) );

	test = -255;
	CHECK_EQUAL( -255, (crap::convert<f32, i16>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( I16_MAX, (crap::convert<f32, i16>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( I16_MIN, (crap::convert<f32, i16>( test )) );
}

TEST(ConverterF32U16)
{
	f32 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f32, u16>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f32, u16>( test )) );

	test = -255;
	CHECK_EQUAL( 0, (crap::convert<f32, u16>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( U16_MAX, (crap::convert<f32, u16>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( 0, (crap::convert<f32, u16>( test )) );
}

TEST(ConverterF32I32)
{
	f32 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f32, i32>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f32, i32>( test )) );

	test = -255;
	CHECK_EQUAL( -255, (crap::convert<f32, i32>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( I32_MAX, (crap::convert<f32, i32>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( I32_MIN, (crap::convert<f32, i32>( test )) );
}

TEST(ConverterF32U32)
{
	f32 test = 0;
	CHECK_EQUAL( (u32)0, (crap::convert<f32, u32>( test )) );

	test = 255;
	CHECK_EQUAL( (u32)255, (crap::convert<f32, u32>( test )) );

	test = -255;
	CHECK_EQUAL( (u32)0, (crap::convert<f32, u32>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( U32_MAX, (crap::convert<f32, u32>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( (u32)0, (crap::convert<f32, u32>( test )) );
}

TEST(ConverterF32I64)
{
	f32 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f32, i64>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f32, i64>( test )) );

	test = -255;
	CHECK_EQUAL( -255, (crap::convert<f32, i64>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( I64_MAX, (crap::convert<f32, i64>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( I64_MIN, (crap::convert<f32, i64>( test )) );
}

TEST(ConverterF32U64)
{
	f32 test = 0;
	CHECK_EQUAL( (u64)0, (crap::convert<f32, u64>( test )) );

	test = 255;
	CHECK_EQUAL( (u64)255, (crap::convert<f32, u64>( test )) );

	test = -255;
	CHECK_EQUAL( (u64)0, (crap::convert<f32, u64>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( U64_MAX, (crap::convert<f32, u64>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( (u64)0, (crap::convert<f32, u64>( test )) );
}

TEST(ConverterF32F32)
{
	f32 test = 0;
	CHECK_EQUAL( 0.0f, (crap::convert<f32, f32>( test )) );

	test = 255;
	CHECK_EQUAL( 255.0f, (crap::convert<f32, f32>( test )) );

	test = -255;
	CHECK_EQUAL( -255.0f, (crap::convert<f32, f32>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( F32_MAX,(crap::convert<f32, f32>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( F32_MIN, (crap::convert<f32, f32>( test )) );
}

TEST(ConverterF32F64)
{
	f32 test = 0;
	CHECK_EQUAL( 0.0, (crap::convert<f32, f64>( test )) );

	test = 255;
	CHECK_EQUAL( 255.0, (crap::convert<f32, f64>( test )) );

	test = -255;
	CHECK_EQUAL( -255.0, (crap::convert<f32, f64>( test )) );

	test = F32_MAX;
	CHECK_EQUAL( (f64)F32_MAX, (crap::convert<f32, f64>( test )) );

	test = F32_MIN;
	CHECK_EQUAL( (f64)F32_MIN, (crap::convert<f32, f64>( test )) );
}


//f64
TEST(ConverterF64C8)
{
	f64 test = 0.0f;
	CHECK_EQUAL( (i32)0, (i32)(crap::convert<f64, c8>( test )) );

	test = 255.f;
	CHECK_EQUAL( (i32)127, (i32)(crap::convert<f64, c8>( test )) );

	test = -255.f;
	CHECK_EQUAL( (i32)-128, (i32)(crap::convert<f64, c8>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( (i32)127, (i32)(crap::convert<f64, c8>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( (i32)-128, (i32)(crap::convert<f64, c8>( test )) );
}

TEST(ConverterF64I8)
{
	f64 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f64, i8>( test )) );

	test = 255;
	CHECK_EQUAL( 127, (crap::convert<f64, i8>( test )) );

	test = -255;
	CHECK_EQUAL( -128, (crap::convert<f64, i8>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( 127, (crap::convert<f64, i8>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( -128, (crap::convert<f64, i8>( test )) );
}

TEST(ConverterF64U8)
{
	f64 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f64, u8>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f64, u8>( test )) );

	test = -255;
	CHECK_EQUAL( 0, (crap::convert<f64, u8>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( 255, (crap::convert<f64, u8>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( 0, (crap::convert<f64, u8>( test )) );
}

TEST(ConverterF64I16)
{
	f64 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f64, i16>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f64, i16>( test )) );

	test = -255;
	CHECK_EQUAL( -255, (crap::convert<f64, i16>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( I16_MAX, (crap::convert<f64, i16>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( I16_MIN, (crap::convert<f64, i16>( test )) );
}

TEST(ConverterF64U16)
{
	f64 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f64, u16>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f64, u16>( test )) );

	test = -255;
	CHECK_EQUAL( 0, (crap::convert<f64, u16>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( U16_MAX, (crap::convert<f64, u16>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( 0, (crap::convert<f64, u16>( test )) );
}

TEST(ConverterF64I32)
{
	f64 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f64, i32>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f64, i32>( test )) );

	test = -255;
	CHECK_EQUAL( -255, (crap::convert<f64, i32>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( I32_MAX, (crap::convert<f64, i32>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( I32_MIN, (crap::convert<f64, i32>( test )) );
}

TEST(ConverterF64U32)
{
	f64 test = 0;
	CHECK_EQUAL( (u32)0, (crap::convert<f64, u32>( test )) );

	test = 255;
	CHECK_EQUAL( (u32)255, (crap::convert<f64, u32>( test )) );

	test = -255;
	CHECK_EQUAL( (u32)0, (crap::convert<f64, u32>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( (u32)U32_MAX, (crap::convert<f64, u32>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( (u32)0, (crap::convert<f64, u32>( test )) );
}

TEST(ConverterF64I64)
{
	f64 test = 0;
	CHECK_EQUAL( 0, (crap::convert<f64, i64>( test )) );

	test = 255;
	CHECK_EQUAL( 255, (crap::convert<f64, i64>( test )) );

	test = -255;
	CHECK_EQUAL( -255, (crap::convert<f64, i64>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( I64_MAX, (crap::convert<f64, i64>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( I64_MIN, (crap::convert<f64, i64>( test )) );
}

TEST(ConverterF64U64)
{
	f64 test = 0;
	CHECK_EQUAL( (u64)0, (crap::convert<f64, u64>( test )) );

	test = 255;
	CHECK_EQUAL( (u64)255, (crap::convert<f64, u64>( test )) );

	test = -255;
	CHECK_EQUAL( (u64)0, (crap::convert<f64, u64>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( U64_MAX, (crap::convert<f64, u64>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( (u64)0, (crap::convert<f64, u64>( test )) );
}

TEST(ConverterF64F32)
{
	f64 test = 0.0;
	CHECK_EQUAL( 0.0f, (crap::convert<f64, f32>( test )) );

	test = 255;
	CHECK_EQUAL( 255.0f, (crap::convert<f64, f32>( test )) );

	test = -255;
	CHECK_EQUAL( -255.0f, (crap::convert<f64, f32>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( F32_MAX,(crap::convert<f64, f32>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( F32_MIN, (crap::convert<f64, f32>( test )) );
}

TEST(ConverterF64F64)
{
	f64 test = 0.0;
	CHECK_EQUAL( 0.0, (crap::convert<f64, f64>( test )) );

	test = 255;
	CHECK_EQUAL( 255.0, (crap::convert<f64, f64>( test )) );

	test = -255;
	CHECK_EQUAL( -255.0, (crap::convert<f64, f64>( test )) );

	test = F64_MAX;
	CHECK_EQUAL( (f64)F64_MAX, (crap::convert<f64, f64>( test )) );

	test = F64_MIN;
	CHECK_EQUAL( (f64)F64_MIN, (crap::convert<f64, f64>( test )) );
}


}   // namespace
