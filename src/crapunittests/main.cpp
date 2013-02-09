#include "crapwindow.h"
#include "threading/sleep.h"

#include "UnitTest++.h"

int main ()
{
    std::cout << "Starting Unittests:" << std::endl << "=====================" << std::endl;
    int rtn =  UnitTest::RunAllTests();

	std::cout << std::endl;
	std::cout << "Starting Window tests:" << std::endl << "=====================" << std::endl;
	crap::window_setup setup;
    crap::crapwindow test_win( setup );
	test_win.open();

	setup.width = 800;
	setup.height = 600;
	test_win.update_settings( setup );
	test_win.reset_window();

	setup.width = 1024;
	setup.height = 768;
	setup.fullscreen = true;
	test_win.update_settings( setup );
	test_win.reset_window();

    crap::sleep_sec(1);

	setup.width = 320;
	setup.height = 240;
	setup.fullscreen = false;
	test_win.update_settings( setup );
	test_win.reset_window();

	crap::sleep_sec(1);

	test_win.close();
	

#ifdef CRAP_COMPILER_VC
    std::cout << "Press a button" << std::endl;
	getchar();
#endif
    return rtn;
}
