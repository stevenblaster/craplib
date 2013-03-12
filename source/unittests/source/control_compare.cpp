#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "control/compare.h"

namespace
{

TEST(ControlCompareTitle)
{
    std::cout << "Testing \"control/compare.h\"" << std::endl;
}

TEST(ControlLessPositive)
{
	std::cout << "\tcrap::less" << std::endl;
	crap::less<i32> less_object;
	CHECK_EQUAL( true, less_object(10,11) );
}

TEST(ControlLessNegative)
{
	crap::less<i32> less_object;
	CHECK_EQUAL( false, less_object(11,10) );
}

TEST(ControlLessNegativeBecauseEqual)
{
	crap::less<i32> less_object;
	CHECK_EQUAL( false, less_object(11,11) );
}

TEST(ControlGreaterPositive)
{
	std::cout << "\tcrap::greater" << std::endl;
	crap::greater<i32> greater_object;
	CHECK_EQUAL( true, greater_object(11,10) );
}

TEST(ControlGreaterNegative)
{
	crap::greater<i32> greater_object;
	CHECK_EQUAL( false, greater_object(10,11) );
}

TEST(ControlGreaterNegativeBecauseEqual)
{
	crap::greater<i32> greater_object;
	CHECK_EQUAL( false, greater_object(11,11) );
}

TEST(ControlEqualtoPositive)
{
	std::cout << "\tcrap::equal_to" << std::endl;
	crap::equal_to<i32> equalto_object;
	CHECK_EQUAL( true, equalto_object(11,11) );
}

TEST(ControlEqualtoNegativeBecauseLess)
{
	crap::equal_to<i32> equalto_object;
	CHECK_EQUAL( false, equalto_object(10,11) );
}

TEST(ControlEqualtoNegativeBecauseGreater)
{
	crap::equal_to<i32> equalto_object;
	CHECK_EQUAL( false, equalto_object(11,10) );
}

TEST(ControlNotEqualToPositiveLess)
{
	std::cout << "\tcrap::not_equal_to" << std::endl;
	crap::not_equal_to<i32> notequalto_object;
	CHECK_EQUAL( true, notequalto_object(10,11) );
}

TEST(ControlNotEqualToPositiveGreater)
{
	crap::not_equal_to<i32> notequalto_object;
	CHECK_EQUAL( true, notequalto_object(11,10) );
}

TEST(ControlNotEqualToNegative)
{
	crap::not_equal_to<i32> notequalto_object;
	CHECK_EQUAL( false, notequalto_object(10,10) );
}

TEST(ControlGreaterEqualPositiveGreater)
{
	std::cout << "\tcrap::greater_equal" << std::endl;
	crap::greater_equal<i32> greaterequalto_object;
	CHECK_EQUAL( true, greaterequalto_object(11,10) );
}

TEST(ControlGreaterEqualPositiveEqual)
{
	crap::greater_equal<i32> greaterequalto_object;
	CHECK_EQUAL( true, greaterequalto_object(10,10) );
}

TEST(ControlGreaterEqualNegative)
{
	crap::greater_equal<i32> greaterequalto_object;
	CHECK_EQUAL( false, greaterequalto_object(10,11) );
}

TEST(ControlLessEqualPositiveLess)
{
	std::cout << "\tcrap::less_equal" << std::endl;
	crap::less_equal<i32> lessequalto_object;
	CHECK_EQUAL( true, lessequalto_object(10,11) );
}

TEST(ControlLessEqualPositiveEqual)
{
	crap::less_equal<i32> lessequalto_object;
	CHECK_EQUAL( true, lessequalto_object(10,10) );
}

TEST(ControlLessEqualNegative)
{
	crap::less_equal<i32> lessequalto_object;
	CHECK_EQUAL( false, lessequalto_object(11,10) );
}

}   // namespace
