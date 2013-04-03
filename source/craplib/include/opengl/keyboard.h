////////////////////////////////////////////////////////
// CRAP Library
//!		@file keyboard.h
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

#ifndef CRAP_keyboard_H
#define CRAP_keyboard_H

#include "container/bitset.h"

//lib namespace
namespace crap
{

class keyboard
{
public:
	enum key
	{
		key_space					= 0x20, //' '
		key_exclamation				= 0x21, //'!'
		key_doublequote				= 0x22, //'"'
		key_pound					= 0x23, //'#'
		key_dollar					= 0x24, //'$'
		key_percent					= 0x25, //'%'
		key_and						= 0x26, //'&'
		key_quote					= 0x27, //'''
		key_paranthesis_left		= 0x28, //'('
		key_paranthesis_right		= 0x29, //')'
		key_asteriks				= 0x2A, //'*'
		key_plus					= 0x2B, //'+'
		key_comma					= 0x2C, //','
		key_minus					= 0x2D, //'-'
		key_dot						= 0x2E, //'.'
		key_slash					= 0x2F, //'/'
		key_0						= 0x30, //'0'
		key_1						= 0x31, //'1'
		key_2						= 0x32, //'2'
		key_3						= 0x33, //'3'
		key_4						= 0x34, //'4'
		key_5						= 0x35, //'5'
		key_6						= 0x36, //'6'
		key_7						= 0x37, //'7'
		key_8						= 0x38, //'8'
		key_9						= 0x39, //'9'
		key_colon					= 0x3A, //':'
		key_semicolon				= 0x3B, //';'
		key_less_than				= 0x3C, //'<'
		key_equal					= 0x3D, //'='
		key_greater_than			= 0x3E, //'>'
		key_question				= 0x3F, //'?'
		key_at						= 0x40, //'@'
		key_A						= 0x41, //'A'
		key_B						= 0x42, //'B'
		key_C						= 0x43, //'C'
		key_D						= 0x44, //'D'
		key_E						= 0x45, //'E'
		key_F						= 0x46, //'F'
		key_G						= 0x47, //'G'
		key_H						= 0x48, //'H'
		key_I						= 0x49, //'I'
		key_J						= 0x4A, //'J'
		key_K						= 0x4B, //'K'
		key_L						= 0x4C, //'L'
		key_M						= 0x4D, //'M'
		key_N						= 0x4E, //'N'
		key_O						= 0x4F, //'O'
		key_P						= 0x50, //'P'
		key_Q						= 0x51, //'Q'
		key_R						= 0x52, //'R'
		key_S						= 0x53, //'S'
		key_T						= 0x54, //'T'
		key_U						= 0x55, //'U'
		key_V						= 0x56, //'V'
		key_W						= 0x57, //'W'
		key_X						= 0x58, //'X'
		key_Y						= 0x59, //'Y'
		key_Z						= 0x5A, //'Z'
		key_square_bracket_left		= 0x5B, //'['
		key_backslash				= 0x5C, //'\'
		key_square_bracket_right	= 0x5D, //']'
		key_circumflex				= 0x5E, //'^'
		key_underscore				= 0x5F, //'_'
		key_apostrophe				= 0x60, //'`'
		key_a						= 0x61, //'a'
		key_b						= 0x62, //'b'
		key_c						= 0x63, //'c'
		key_d						= 0x64, //'d'
		key_e						= 0x65, //'e'
		key_f						= 0x66, //'f'
		key_g						= 0x67, //'g'
		key_h						= 0x68, //'h'
		key_i						= 0x69, //'i'
		key_j						= 0x6A, //'j'
		key_k						= 0x6B, //'k'
		key_l						= 0x6C, //'l'
		key_m						= 0x6D, //'m'
		key_n						= 0x6E, //'n'
		key_o						= 0x6F, //'o'
		key_p						= 0x70, //'p'
		key_q						= 0x71, //'q'
		key_r						= 0x72, //'r'
		key_s						= 0x73, //'s'
		key_t						= 0x74, //'t'
		key_u						= 0x75, //'u'
		key_v						= 0x76, //'v'
		key_w						= 0x77, //'w'
		key_x						= 0x78, //'x'
		key_y						= 0x79, //'y'
		key_z						= 0x7A, //'z'
		key_brace_left				= 0x7B, //'{'
		key_vertical_bar			= 0x7C, //'|'
		key_brace_right				= 0x7D, //'}'
		key_tilde					= 0x7E, //'~'
		//glfw special keys
		key_spacebar				= 32,
		key_escape					= 256+1,
		key_f1						= 256+2,
		key_f2						= 256+3,
		key_f3						= 256+4,
		key_f4						= 256+5,
		key_f5						= 256+6,
		key_f6						= 256+7,
		key_f7						= 256+8,
		key_f8						= 256+9,
		key_f9						= 256+10,
		key_f10						= 256+11,
		key_f11						= 256+12,
		key_f12						= 256+13,
		key_up						= 256+27,
		key_down					= 256+28,
		key_left					= 256+29,
		key_right					= 256+30,
		key_shift_left				= 256+31,
		key_shift_right				= 256+32,
		key_control_left			= 256+33,
		key_control_right			= 256+34,
		key_alt_left				= 256+35,
		key_alt_right				= 256+36,
		key_tabulator				= 256+37,
		key_return					= 256+38,
		key_backspace				= 256+39,
		key_insert					= 256+40,
		key_delete					= 256+41,
		key_page_up					= 256+42,
		key_page_down				= 256+43,
		key_home					= 256+44,
		key_end						= 256+45,
		key_keypad_0				= 256+46,
		key_keypad_1				= 256+47,
		key_keypad_2				= 256+48,
		key_keypad_3				= 256+49,
		key_keypad_4				= 256+50,
		key_keypad_5				= 256+51,
		key_keypad_6				= 256+52,
		key_keypad_7				= 256+53,
		key_keypad_8				= 256+54,
		key_keypad_9				= 256+55,
		key_keypad_divide			= 256+56,
		key_keypad_multiply			= 256+57,
		key_keypad_substract		= 256+58,
		key_keypad_add				= 256+59,
		key_keypad_decimal			= 256+60,
		key_keypad_equal			= 256+61,
		key_keypad_return			= 256+62,
		key_keypad_numlock			= 256+63,
		key_capslock				= 256+64,
		key_scroll_lock				= 256+65,
		key_pause					= 256+66,
		key_super_left				= 256+67,
		key_super_right				= 256+68,
		key_menu					= 256+69
	};

private:
	static bit_set<256+69> _bitset;

	static void callback_function( i32 key_id, i32 key_state );

	typedef void (*user_callback_function)( i32 key_id );
	static user_callback_function _on_pressed_function;
	static user_callback_function _on_release_function;

public:
	keyboard( void );
	~keyboard( void );

	b8 is_pressed( key key_id );

	void overwrite_callback( void (*function)( i32 key_id, i32 key_state ) );

	void set_on_pressed_function( void (*function)(i32 key_id) );
	void set_on_release_function( void (*function)(i32 key_id) );
};

} //namespace crap

#endif // CRAP_keyboard_H
