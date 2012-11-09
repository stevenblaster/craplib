#include "UnitTest++.h"

int main ()
{
    std::cout << "Starting Unittests:" << std::endl << "=====================" << std::endl;
    int rtn =  UnitTest::RunAllTests();
    std::cout << "Press a button" << std::endl;
    return rtn;
}
