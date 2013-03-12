#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "math/random.h"

namespace
{

TEST(MathRandomTitle)
{
    std::cout << "Testing \"math/random.h\"" << std::endl;
}

TEST(MathRandomGenerate)
{
	std::cout << "\tgenerating random numbers" << std::endl;
	/*std::cout << "\tsigned 8 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << (i32)crap::random<i8>::generate() << std::endl;

	std::cout << "\tunsigned 8 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << (i32)crap::random<u8>::generate() << std::endl;

	std::cout << "\tsigned 16 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i16>::generate() << std::endl;

	std::cout << "\tunsigned 16 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u16>::generate() << std::endl;

	std::cout << "\tsigned 32 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i32>::generate() << std::endl;

	std::cout << "\tunsigned 32 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u32>::generate() << std::endl;

	std::cout << "\tsigned 64 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i64>::generate() << std::endl;

	std::cout << "\tunsigned 64 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u64>::generate() << std::endl;

	std::cout << "\tfloat" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << std::fixed << crap::random<f32>::generate() << std::endl;

	std::cout << "\tdouble" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << std::fixed << crap::random<f64>::generate() << std::endl; */
}

TEST(MathRandomGeneratePositive)
{
	std::cout << "\tgenerating random positive numbers" << std::endl;
	/*std::cout << "\tsigned 8 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << (i32)crap::random<i8>::generate_positive() << std::endl;

	std::cout << "\tunsigned 8 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << (i32)crap::random<u8>::generate_positive() << std::endl;

	std::cout << "\tsigned 16 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i16>::generate_positive() << std::endl;

	std::cout << "\tunsigned 16 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u16>::generate_positive() << std::endl;

	std::cout << "\tsigned 32 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i32>::generate_positive() << std::endl;

	std::cout << "\tunsigned 32 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u32>::generate_positive() << std::endl;

	std::cout << "\tsigned 64 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i64>::generate_positive() << std::endl;

	std::cout << "\tunsigned 64 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u64>::generate_positive() << std::endl;

	std::cout << "\tfloat" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << std::fixed << crap::random<f32>::generate_positive() << std::endl;

	std::cout << "\tdouble" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << std::fixed  << crap::random<f64>::generate_positive() << std::endl; */
}

TEST(MathRandomGenerateNegative)
{
	std::cout << "\tgenerating random negative numbers" << std::endl;
	/* std::cout << "\tsigned 8 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << (i32)crap::random<i8>::generate_negative() << std::endl;

	std::cout << "\tunsigned 8 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << (i32)crap::random<u8>::generate_negative() << std::endl;

	std::cout << "\tsigned 16 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i16>::generate_negative() << std::endl;

	std::cout << "\tunsigned 16 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u16>::generate_negative() << std::endl;

	std::cout << "\tsigned 32 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i32>::generate_negative() << std::endl;

	std::cout << "\tunsigned 32 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u32>::generate_negative() << std::endl;

	std::cout << "\tsigned 64 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i64>::generate_negative() << std::endl;

	std::cout << "\tunsigned 64 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u64>::generate_negative() << std::endl;

	std::cout << "\tfloat" << std::endl;
	for(int i=0; i<5; ++i)
	{
		
		std::cout << "\t" << std::fixed << crap::random<f32>::generate_negative() << std::endl;
	}

	std::cout << "\tdouble" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << std::fixed << crap::random<f64>::generate_negative() << std::endl; */
}

TEST(MathRandomRange)
{
	std::cout << "\tgenerating random range numbers" << std::endl;
	/*
	std::cout << "\tsigned 8 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << (i32)crap::random<i8>::range( -10, 10 ) << std::endl;

	std::cout << "\tunsigned 8 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << (i32)crap::random<u8>::range( 0, 10 ) << std::endl;

	std::cout << "\tsigned 16 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i16>::range( -10, 10 ) << std::endl;

	std::cout << "\tunsigned 16 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u16>::range( 0, 10 ) << std::endl;

	std::cout << "\tsigned 32 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i32>::range( -10, 10 ) << std::endl;

	std::cout << "\tunsigned 32 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u32>::range( 0, 10 ) << std::endl;

	std::cout << "\tsigned 64 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<i64>::range( -10, 10 ) << std::endl;

	std::cout << "\tunsigned 64 bit" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<u64>::range( 0, 10 ) << std::endl;

	std::cout << "\tfloat" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<f32>::range( -10, 10 ) << std::endl;

	std::cout << "\tdouble" << std::endl;
	for(int i=0; i<5; ++i)
		std::cout << "\t" << crap::random<f64>::range( -10, 10 ) << std::endl; */
}

}   // namespace
