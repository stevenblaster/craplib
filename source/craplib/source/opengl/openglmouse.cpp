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

bit_set<8> openglmouse::_bitset;

vector2i openglmouse::_position;

vector2i openglmouse::_movement;

i32 openglmouse::_wheel = 0;

i32 openglmouse::_wheel_movement = 0;

openglmouse::user_button_callback_function openglmouse::_on_pressed_function = 0;

openglmouse::user_button_callback_function openglmouse::_on_release_function = 0;

openglmouse::user_move_callback_function openglmouse::_on_move_function = 0;

openglmouse::user_wheel_callback_function openglmouse::_on_wheel_function = 0;

openglmouse::openglmouse( void )
{
	glfwSetMouseButtonCallback( &openglmouse::button_callback_function );
	glfwSetMousePosCallback( &openglmouse::move_callback_function );
	glfwSetMouseWheelCallback( &openglmouse::wheel_callback_function );
}

openglmouse::~openglmouse( void )
{
	glfwSetMouseButtonCallback(NULL);
	glfwSetMousePosCallback(NULL);
	glfwSetMouseWheelCallback( NULL );
}

void openglmouse::button_callback_function( i32 button_id, i32 button_state )
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

void openglmouse::move_callback_function( i32 pos_x, i32 pos_y )
{
	_movement.x = pos_x - _position.x; 
	_movement.y = pos_y - _position.y; 
	_position.x = pos_x;
	_position.y = pos_y;
	if( _on_move_function != 0 )
		_on_move_function( pos_x, pos_y );
}

void openglmouse::wheel_callback_function( i32 pos )
{
	_wheel_movement = pos - _wheel;
	_wheel = pos;
	if( _on_wheel_function != 0 )
		_on_wheel_function( pos );
}

b8 openglmouse::is_pressed( button button_id )
{
	return _bitset.test( button_id );
}

vector2i openglmouse::position( void )
{
	return _position;
}

vector2i openglmouse::movement( void )
{
	return _movement;
}

i32 openglmouse::wheel( void )
{
	return _wheel;
}

i32 openglmouse::wheel_movement( void )
{
	return _wheel_movement;
}

void openglmouse::overwrite_button_callback( void (*function)( i32 button_id, i32 button_state ) )
{
	glfwSetMouseButtonCallback( (GLFWmousebuttonfun)function );
}

void openglmouse::overwrite_move_callback( void (*function)( i32 pos_x, i32 pos_y ) )
{
	glfwSetMousePosCallback( (GLFWmouseposfun)function );
}

void openglmouse::overwrite_wheel_callback( void (*function)( i32 pos ) )
{
	glfwSetMouseWheelCallback( (GLFWmousewheelfun)function );
}

void openglmouse::set_on_pressed_function( void (*function)( i32 key_id ) )
{
	_on_pressed_function = function;
}

void openglmouse::set_on_release_function( void (*function)( i32 key_id ) )
{
	_on_release_function = function;
}

void openglmouse::set_on_move_function( void (*function)( i32 pos_x, i32 pos_y ) )
{
	_on_move_function = function;
}

void openglmouse::set_on_wheel_function( void (*function)( i32 key_id ) )
{
	_on_wheel_function = function;
}

} //namespace crap