#include "crap.h"
#include "opengl/openglwindow.h"
#include "opengl/openglkeyboard.h"
#include "opengl/openglmouse.h"
#include "threading/sleep.h"
#include "audio/audiodevice.h"
#include "files/file.h"
#include "geometry/vector3.h"
#include "audio/wavefile.h"
#include "GL/glfw.h"

#include "UnitTest++.h"


void test( int a  )
{
    std::cout << "Key pressed:" << (char)a << std::endl;
}

void click_left( i32 button )
{
	if( (crap::openglmouse::button) button == crap::openglmouse::button_left )
		std::cout << "left button clicked" << std::endl;
	else if( (crap::openglmouse::button) button == crap::openglmouse::button_right )
		std::cout << "right button clicked" << std::endl;
	else if( (crap::openglmouse::button) button == crap::openglmouse::button_middle )
		std::cout << "middle button clicked" << std::endl;
	else
		std::cout << "button number " << button << " clicked" << std::endl;
}

void move_mouse( i32 x, i32 y )
{
	std::cout << "Mouse pos:" << crap::openglmouse::position().x << ", " << crap::openglmouse::position().y 
		<< " - movement:" << crap::openglmouse::movement().x << ", " << crap::openglmouse::movement().y << std::endl;
}

void wheel_move( i32 var )
{
	std::cout << "Wheel pos:" << crap::openglmouse::wheel() << ", Wheel movement:" << crap::openglmouse::wheel_movement() << std::endl;
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

	crap::openglmouse mouse;
	mouse.set_on_pressed_function( &click_left );
	mouse.set_on_move_function( &move_mouse );
	mouse.set_on_wheel_function( &wheel_move );

	crap::audiodevice audio_device;
	crap::wave_file wav( "audiofile.wav" );
    wav.play( crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0),
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
