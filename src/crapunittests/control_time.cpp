#include "UnitTest++.h"

//lib includes
#include "control/time.h"

namespace
{

TEST(ControlTimeTitle)
{
    std::cout << "Testing \"control/time.h\"" << std::endl;
}

TEST(ControlTimeCurrentTime)
{
	std::cout << "\t" << crap::time::instance().week_day_name( crap::time::instance().current_time().weekday ) << ", " << 
		crap::time::instance().current_time().day << "'th of " << 
		crap::time::instance().month_name( crap::time::instance().current_time().month ) << " - " << 
		crap::time::instance().current_time().hours << ":" <<
		crap::time::instance().current_time().minutes << ":" <<
		crap::time::instance().current_time().seconds << std::endl;
}

}   // namespace
