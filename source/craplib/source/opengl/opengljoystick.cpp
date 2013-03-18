////////////////////////////////////////////////////////
// CRAP Library
//!		@file opengljoystick.cpp
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
#include "opengl/opengljoystick.h"

//lib namespace
namespace crap
{

opengl_joystick::user_joystick_callback_function opengl_joystick::_on_attach_function = 0;
opengl_joystick::user_joystick_callback_function opengl_joystick::_on_deattach_function = 0;

opengl_joystick::opengl_joystick( void )
{

}

opengl_joystick::~opengl_joystick( void )
{

}

void opengl_joystick::poll_events( void )
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
					_on_attach_function( (joystick)i, _status[i] );
			}

			glfwGetJoystickPos( i, _status[i].axis_info, _status[i].num_axis );
			glfwGetJoystickButtons( i, _status[i].button_info, _status[i].num_buttons );
		}
		else if( _status[i].active == true )
		{
			if( _on_deattach_function != 0 )
				_on_deattach_function( (joystick)i, _status[i] );

			_status[i].reset();	
		}
	}
}

f32 opengl_joystick::get_axis( joystick joystick_id, axis axis_id )
{
	return _status[ joystick_id ].axis_info[ axis_id ];
}

b8 opengl_joystick::get_button( joystick joystick_id, button button_id )
{
	return _status[ joystick_id ].button_info[ button_id ] == 1;
}

void opengl_joystick::set_on_attach_function( void (*function)( joystick id, joystick_info info) )
{
	_on_attach_function = function;
}

void opengl_joystick::set_on_deattach_function( void (*function)( joystick id, joystick_info info) )
{
	_on_deattach_function = function;
}

} //namespace crap