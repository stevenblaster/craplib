#include "crap.h"
#include "opengl/openglwindow.h"
#include "opengl/openglkeyboard.h"
#include "threading/sleep.h"
#include "audio/audiodevice.h"
#include "files/file.h"
#include "geometry/vector3.h"
#include "audio/wavefile.h"
#include "AL/al.h"

#include "GL/glfw.h"

#include "UnitTest++.h"


void test( int a  )
{
	int fun=0;
}

int main ()
{
    std::cout << "Starting Unittests:" << std::endl << "=====================" << std::endl;
    int rtn =  UnitTest::RunAllTests();

    
	std::cout << std::endl;
	std::cout << "Starting Window tests:" << std::endl << "=====================" << std::endl;
	crap::window_setup setup;
	setup.title = "Funny Window";
    crap::openglwindow test_win( setup );

	std::cout << "Default settings" << std::endl;
	test_win.open();

	std::cout << "800x600 windowed" << std::endl;
	setup.width = 800;
	setup.height = 600;
	test_win.update_settings( setup );
	test_win.reset_window();

    crap::sleep_sec(3);

	std::cout << "1024x768 fullscreen" << std::endl;
	setup.width = 1024;
	setup.height = 768;
	setup.fullscreen = true;
	test_win.update_settings( setup );
	test_win.reset_window();

    crap::sleep_sec(3);

	std::cout << "320x240 windowed" << std::endl;
	setup.width = 320;
	setup.height = 240;
	setup.fullscreen = false;
	test_win.update_settings( setup );
	test_win.reset_window();

	crap::openglkeyboard keyboard;
	keyboard.set_on_pressed_function( &test );

	crap::audiodevice audio_device;
	crap::wave_file wav( "audiofile.wav" );
	wav.play( &audio_device, crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0), 
		crap::vector3f(0,0,-1), crap::vector3f(0,1,0) );

	
	while( !keyboard.is_pressed( crap::openglkeyboard::key_escape ) )
	{
		glfwPollEvents();
	}

    //crap::sleep_sec(5);
	test_win.close();
    
    

//#ifdef CRAP_COMPILER_VC
//    std::cout << "Press a button" << std::endl;
//	getchar();
//#endif
    return rtn;
}
