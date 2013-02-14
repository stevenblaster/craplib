#include "UnitTest++.h"

//lib includes
#include "control/limits.h"

namespace
{

TEST(ControlLimitsTitle)
{
    std::cout << "Testing \"control/limits.h\"" << std::endl;
}

TEST(ControlLimitsFloat)
{
	std::cout << "\tChecking floating points (they're linked)" << std::endl;

	CHECK( crap::limits<f32>::MAX > 0 );
	CHECK( crap::limits<f32>::MIN < 0 );
}

TEST(ControlLimitsDouble)
{
	CHECK( crap::limits<f64>::MAX > 0 );
	CHECK( crap::limits<f64>::MIN < 0 );
}

}   // namespace
