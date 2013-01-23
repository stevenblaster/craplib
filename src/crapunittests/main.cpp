#include "UnitTest++.h"

int main ()
{
    std::cout << "Starting Unittests:" << std::endl << "=====================" << std::endl;
    int rtn =  UnitTest::RunAllTests();

#ifdef CRAP_COMPILER_VC
    std::cout << "Press a button" << std::endl;
	getchar();
#endif
    return rtn;
}
