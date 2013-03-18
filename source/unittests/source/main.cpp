#include "crap.h"
#include "opengl/openglwindow.h"
#include "opengl/openglkeyboard.h"
#include "opengl/openglmouse.h"
#include "opengl/opengljoystick.h"
#include "threading/sleep.h"
#include "audio/audiodevice.h"
#include "files/file.h"
#include "math/vector3.h"
#include "audio/wavefile.h"

#include "UnitTest++.h"


void test( int a  )
{
    std::cout << "Key pressed:" << (char)a << std::endl;
}

void click_left( i32 button )
{
	if( (crap::opengl_mouse::button) button == crap::opengl_mouse::button_left )
		std::cout << "left button clicked" << std::endl;
	else if( (crap::opengl_mouse::button) button == crap::opengl_mouse::button_right )
		std::cout << "right button clicked" << std::endl;
	else if( (crap::opengl_mouse::button) button == crap::opengl_mouse::button_middle )
		std::cout << "middle button clicked" << std::endl;
	else
		std::cout << "button number " << button << " clicked" << std::endl;
}

void move_mouse( i32 x, i32 y )
{
	std::cout << "Mouse pos:" << crap::opengl_mouse::position().x << ", " << crap::opengl_mouse::position().y 
		<< " - movement:" << crap::opengl_mouse::movement().x << ", " << crap::opengl_mouse::movement().y << std::endl;
}

void wheel_move( i32 var )
{
	std::cout << "Wheel pos:" << crap::opengl_mouse::wheel() << ", Wheel movement:" << crap::opengl_mouse::wheel_movement() << std::endl;
}

void joystick_attach( crap::opengl_joystick::joystick id, crap::opengl_joystick::joystick_info info )
{
	std::cout << "Joystick " << id << " with " << info.num_axis << " axis and " << info.num_buttons << " buttons attached." << std::endl;
}

void joystick_deattach( crap::opengl_joystick::joystick id, crap::opengl_joystick::joystick_info info )
{
	std::cout << "Joystick " << id << " with " << info.num_axis << " axis and " << info.num_buttons << " buttons deattached." << std::endl;
}

int main ()
{
    std::cout << "Starting Unittests:" << std::endl << "=====================" << std::endl;
    int rtn =  UnitTest::RunAllTests();

    
	std::cout << std::endl;
	std::cout << "Starting Window tests:" << std::endl << "=====================" << std::endl;
	crap::window_setup setup;
	setup.title = "Funny Window";
    crap::opengl_window test_win( setup );

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

	crap::opengl_keyboard keyboard;
	keyboard.set_on_pressed_function( &test );

	crap::opengl_mouse mouse;
	mouse.set_on_pressed_function( &click_left );
	mouse.set_on_move_function( &move_mouse );
	mouse.set_on_wheel_function( &wheel_move );

	crap::opengl_joystick joy;
	joy.set_on_attach_function( &joystick_attach );
	joy.set_on_deattach_function( &joystick_deattach );

	crap::audiodevice audio_device;
	crap::wave_file wav( "audiofile.wav" );
    wav.play( crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0), crap::vector3f(0,0,0),
		crap::vector3f(0,0,-1), crap::vector3f(0,1,0) );

	
	while( !keyboard.is_pressed( crap::opengl_keyboard::key_escape ) && test_win.is_open() )
	{
		test_win.poll_events();
		if( joy.get_button( crap::opengl_joystick::joystick_01, crap::opengl_joystick::button_01 ) )
			std::cout << "Joystick button 0 pressed" << std::endl;
		joy.poll_events();
	}

    //crap::sleep_sec(5);
	test_win.close();
    
    

//#ifdef CRAP_COMPILER_VC
//    std::cout << "Press a button" << std::endl;
//	getchar();
//#endif
    return rtn;
}
