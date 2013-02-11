////////////////////////////////////////////////////////
// CRAP Library
//!		@file renderwindow.h
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Wrapper for glfw window
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_RENDERWINDOW_H
#define CRAP_RENDERWINDOW_H

#include "precompiled.h"
#include "container/staticstring.h"
#include "geometry/vector2.h"
#include "geometry/vector4.h"

#if defined(CRAP_PLATFORM_WIN)
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#endif

//lib namespace
namespace crap
{

//window setup struct
typedef
struct window_setup
{
	int width;
	int height;
	vector2i position;
	vector4i color_bits; // red-,green-,blue- and alphabits
	int depth_bits;
	int stencil_bits;
	bool fullscreen;
	int refresh_rate;
	vector4i accumulation_color_bits; //red-,green-,blue-,alphabits
	int auxiliary_buffer;
	bool stereo_rendering;
	bool resizeable;
	int multisampling_count;
	float opengl_version;
	bool forward_compatible;
	bool debug_context;
	int opengl_profile;
	string64 title;

	//default values
	window_setup( void ) : width(640), height(480), position(vector2i()), color_bits(vector4i()), depth_bits(0), stencil_bits(0), fullscreen(false), refresh_rate(0),
		accumulation_color_bits(vector4i()), auxiliary_buffer(0), stereo_rendering(false), resizeable(true),
		multisampling_count(0), opengl_version(1.1f), forward_compatible(false), debug_context(false), opengl_profile(0), title(string64("Default Window"))
	{
	}

	window_setup( const window_setup& other ) : width(other.width), height(other.height), position(other.position), color_bits(other.color_bits), 
		depth_bits(other.depth_bits), stencil_bits(other.stencil_bits), fullscreen(false), refresh_rate(other.refresh_rate),
		accumulation_color_bits(other.accumulation_color_bits), auxiliary_buffer(other.auxiliary_buffer), 
		stereo_rendering(other.stereo_rendering), resizeable(other.resizeable), multisampling_count(other.multisampling_count), 
		opengl_version(other.opengl_version), forward_compatible(other.forward_compatible), debug_context(other.debug_context),
		opengl_profile(other.opengl_profile), title(other.title)
	{
	}

}
window_setup;

class renderwindow
{
public:
    renderwindow( const window_setup& setup );
    ~renderwindow( void );

	void update_settings( const window_setup& setup );
	void reset_window( void );

	void open( void );
	void close( void );

	void set_position( const vector2i& pos );
	void set_size( int width, int height );
	void set_title( const string64& name );
	void set_fullscreen( bool value );

	void swap( void );
	/*
	void set_window_close_function( GLFWwindowclosefun function );
	void set_window_size_function( GLFWwindowsizefun function );
	void set_window_refresh_function( GLFWwindowrefreshfun function );
	*/
private:
	window_setup _window_setup;

};

}

#endif // CRAP_CRAPWINDOW_H
