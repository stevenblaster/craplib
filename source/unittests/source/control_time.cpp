#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "control/craptime.h"

namespace
{

TEST(ControlTimeTitle)
{
    std::cout << "Testing \"control/time.h\"" << std::endl;
}

TEST(ControlTimeCurrentTime)
{
	std::cout << "\t" << crap::time::week_day_name( crap::time::current_time().weekday ) << ", " << 
		crap::time::current_time().day << "'th of " << 
		crap::time::month_name( crap::time::current_time().month ) << " - " << 
		crap::time::current_time().hours << ":" <<
		crap::time::current_time().minutes << ":" <<
		crap::time::current_time().seconds << std::endl;
}

}   // namespace
