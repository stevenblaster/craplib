#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "control/zero.h"

namespace
{

TEST(ControlZeroTitle)
{
    std::cout << "Testing \"control/zero.h\"" << std::endl;
}

TEST(ControlZeroI32)
{
	std::cout << "\tChecking zero of basic types" << std::endl;
    //CHECK_EQUAL( 0, crap::zero<i32>::VALUE );
}

TEST(ControlZeroF32)
{
	CHECK_EQUAL( 0.f, crap::zero<f32>::VALUE );
}

TEST(ControlZeroF64)
{
	CHECK_EQUAL( 0.0, crap::zero<f64>::VALUE );
}

}   // namespace
