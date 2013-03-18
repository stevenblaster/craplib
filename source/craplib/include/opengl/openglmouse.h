////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglmouse.h
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Using glfw input
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_OPENGLMOUSE_H
#define CRAP_OPENGLMOUSE_H

#include "container/bitset.h"
#include "geometry/vector2.h"

//lib namespace
namespace crap
{

class openglmouse
{
public:
	enum button
	{
		button_left = 0,
		button_1 = 0,
		button_right = 1,
		button_2 = 1,
		button_middle = 2,
		button_3 = 2,
		button_4 = 3,
		button_5 = 4,
		button_6 = 5,
		button_7 = 6,
		button_8 = 7,
		button_last = button_8
	};

private:
	static bit_set<8> _bitset;
	static vector2i _position;
	static vector2i _movement;
	static i32 _wheel;
	static i32 _wheel_movement;

	static void button_callback_function( i32 button_id, i32 button_state );
	static void move_callback_function( i32 pos_x, i32 pos_y );
	static void wheel_callback_function( i32 pos );

	typedef void (*user_button_callback_function)( i32 button_id );
	typedef void (*user_move_callback_function)( i32 pos_x, i32 pos_y );
	typedef void (*user_wheel_callback_function)( i32 pos );

	static user_button_callback_function _on_pressed_function;
	static user_button_callback_function _on_release_function;
	static user_move_callback_function _on_move_function;
	static user_wheel_callback_function _on_wheel_function;

public:
	openglmouse( void );
	~openglmouse( void );

	static b8 is_pressed( button button_id );
	static vector2i position( void );
	static vector2i movement( void );
	static i32 wheel( void );
	static i32 wheel_movement( void );

	void overwrite_button_callback( void (*function)( i32 button_id, i32 button_state ) );
	void overwrite_move_callback( void (*function)( i32 pos_x, i32 pos_y ) );
	void overwrite_wheel_callback( void (*function)( i32 pos ) );

	void set_on_pressed_function( void (*function)( i32 key_id ) );
	void set_on_release_function( void (*function)( i32 key_id ) );
	void set_on_move_function( void (*function)( i32 pos_x, i32 pos_y ) );
	void set_on_wheel_function( void (*function)( i32 key_id ) );
};

}

#endif //CRAP_OPENGLMOUSE_H