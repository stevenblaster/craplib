////////////////////////////////////////////////////////
// CRAP Library
//!		@file joystick.cpp
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Wrapper for glfw joystick
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "GL/glfw.h"
#include "opengl/controller.h"

//lib namespace
namespace crap
{

joystick::user_joystick_callback_function joystick::_on_attach_function = 0;
joystick::user_joystick_callback_function joystick::_on_deattach_function = 0;

joystick::joystick( void )
{

}

joystick::~joystick( void )
{

}

void joystick::poll_events( void )
{
	for( i32 i=0; i<16; ++i )
	{
		if( glfwGetJoystickParam( i, GLFW_PRESENT ) )
		{
			if( _status[i].active == false )
			{
				_status[i].active = true;
				_status[i].num_axis = glfwGetJoystickParam( i, GLFW_AXES );
				_status[i].num_buttons = glfwGetJoystickParam( i, GLFW_BUTTONS );
				if( _on_attach_function != 0 )
					_on_attach_function( (joy_id)i, _status[i] );
			}

			glfwGetJoystickPos( i, _status[i].axis_info, _status[i].num_axis );
			glfwGetJoystickButtons( i, _status[i].button_info, _status[i].num_buttons );
		}
		else if( _status[i].active == true )
		{
			if( _on_deattach_function != 0 )
				_on_deattach_function( (joy_id)i, _status[i] );

			_status[i].reset();	
		}
	}
}

f32 joystick::get_axis( joy_id joystick_id, axis axis_id )
{
	return _status[ joystick_id ].axis_info[ axis_id ];
}

b8 joystick::get_button( joy_id joystick_id, button button_id )
{
	return _status[ joystick_id ].button_info[ button_id ] == 1;
}

void joystick::set_on_attach_function( void (*function)( joy_id id, joystick_info info) )
{
	_on_attach_function = function;
}

void joystick::set_on_deattach_function( void (*function)( joy_id id, joystick_info info) )
{
	_on_deattach_function = function;
}

} //namespace crap