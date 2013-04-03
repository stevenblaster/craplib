////////////////////////////////////////////////////////
// CRAP Library
//!		@file keyboard.cpp
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
#include "opengl/keyboard.h"

//lib namespace
namespace crap
{

bit_set<325> keyboard::_bitset;

keyboard::user_callback_function keyboard::_on_pressed_function = 0;

keyboard::user_callback_function keyboard::_on_release_function = 0;

keyboard::keyboard( void )
{
	glfwSetKeyCallback( &keyboard::callback_function );
}

keyboard::~keyboard( void )
{
	glfwSetKeyCallback(NULL);
}

void keyboard::callback_function( i32 key_id, i32 key_state )
{
	if( key_state )
	{
		_bitset.set( key_id );
		if( _on_pressed_function != 0 )
			_on_pressed_function( key_id );
	}
	else
	{
		_bitset.reset( key_id );
		if( _on_release_function != 0 )
			_on_release_function( key_id );
	}
}

b8 keyboard::is_pressed( key key_id )
{
	return _bitset.test( key_id );
}

void keyboard::overwrite_callback( void (*function)( i32 key_id, i32 key_state ) )
{
	glfwSetKeyCallback( (GLFWkeyfun)function );
}

void keyboard::set_on_pressed_function( void (*function)(i32 key_id) )
{
	_on_pressed_function = function;
}

void keyboard::set_on_release_function( void (*function)(i32 key_id) )
{
	_on_release_function = function;
}

}	// namespace crap