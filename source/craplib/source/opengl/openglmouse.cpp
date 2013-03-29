////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglmouse.cpp
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Wrapper for glfw keyboard
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "GL/glfw.h"
#include "opengl/openglmouse.h"

//lib namespace
namespace crap
{

bit_set<8> opengl_mouse::_bitset;

vector2i opengl_mouse::_position(0,0);

vector2i opengl_mouse::_movement(0,0);

i32 opengl_mouse::_wheel = 0;

i32 opengl_mouse::_wheel_movement = 0;

opengl_mouse::user_button_callback_function opengl_mouse::_on_pressed_function = 0;

opengl_mouse::user_button_callback_function opengl_mouse::_on_release_function = 0;

opengl_mouse::user_move_callback_function opengl_mouse::_on_move_function = 0;

opengl_mouse::user_wheel_callback_function opengl_mouse::_on_wheel_function = 0;

opengl_mouse::opengl_mouse( void )
{
	glfwSetMouseButtonCallback( &opengl_mouse::button_callback_function );
	glfwSetMousePosCallback( &opengl_mouse::move_callback_function );
	glfwSetMouseWheelCallback( &opengl_mouse::wheel_callback_function );
}

opengl_mouse::~opengl_mouse( void )
{
	glfwSetMouseButtonCallback(NULL);
	glfwSetMousePosCallback(NULL);
	glfwSetMouseWheelCallback( NULL );
}

void opengl_mouse::button_callback_function( i32 button_id, i32 button_state )
{
	if( button_state )
	{
		_bitset.set( button_id );
		if( _on_pressed_function != 0 )
			_on_pressed_function( button_id );
	}
	else
	{
		_bitset.reset( button_id );
		if( _on_release_function != 0 )
			_on_release_function( button_id );
	}
}

void opengl_mouse::move_callback_function( i32 pos_x, i32 pos_y )
{
	_movement.x = pos_x - _position.x; 
	_movement.y = pos_y - _position.y; 
	_position.x = pos_x;
	_position.y = pos_y;
	if( _on_move_function != 0 )
		_on_move_function( pos_x, pos_y );
}

void opengl_mouse::wheel_callback_function( i32 pos )
{
	_wheel_movement = pos - _wheel;
	_wheel = pos;
	if( _on_wheel_function != 0 )
		_on_wheel_function( pos );
}

b8 opengl_mouse::is_pressed( button button_id )
{
	return _bitset.test( button_id );
}

vector2i opengl_mouse::position( void )
{
	return _position;
}

void opengl_mouse::set_position( vector2i pos )
{
	glfwSetMousePos(pos.x, pos.y);
}

vector2i opengl_mouse::movement( void )
{
	vector2i rtn_mov = _movement;
	_movement.x = 0;
	_movement.y = 0;
	return rtn_mov;
}

i32 opengl_mouse::wheel( void )
{
	return _wheel;
}

i32 opengl_mouse::wheel_movement( void )
{
	return _wheel_movement;
}

void opengl_mouse::overwrite_button_callback( void (*function)( i32 button_id, i32 button_state ) )
{
	glfwSetMouseButtonCallback( (GLFWmousebuttonfun)function );
}

void opengl_mouse::overwrite_move_callback( void (*function)( i32 pos_x, i32 pos_y ) )
{
	glfwSetMousePosCallback( (GLFWmouseposfun)function );
}

void opengl_mouse::overwrite_wheel_callback( void (*function)( i32 pos ) )
{
	glfwSetMouseWheelCallback( (GLFWmousewheelfun)function );
}

void opengl_mouse::set_on_pressed_function( void (*function)( i32 key_id ) )
{
	_on_pressed_function = function;
}

void opengl_mouse::set_on_release_function( void (*function)( i32 key_id ) )
{
	_on_release_function = function;
}

void opengl_mouse::set_on_move_function( void (*function)( i32 pos_x, i32 pos_y ) )
{
	_on_move_function = function;
}

void opengl_mouse::set_on_wheel_function( void (*function)( i32 key_id ) )
{
	_on_wheel_function = function;
}

} //namespace crap