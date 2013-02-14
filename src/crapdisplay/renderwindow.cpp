////////////////////////////////////////////////////////
// CRAP Library
//!		@file window.cpp
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Wrapper for freeglut window
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma warning (disable:4005)

#include <GL/glfw.h>

#include "container/staticstring.h"
#include "renderwindow.h"

//lib namespace
namespace crap
{

renderwindow::renderwindow( const window_setup& setup ) : _window_setup( setup )
{
#ifndef CRAP_GLFW_INIT
#define CRAP_GLFW_INIT

    CRAP_ASSERT_DEBUG( glfwInit(), "Could not init GLFW" );

#endif
}

renderwindow::~renderwindow( void )
{
    close();
}

void renderwindow::update_settings( const window_setup& setup )
{
	_window_setup = setup;
}

void renderwindow::open( void )
{
	glfwOpenWindowHint( GLFW_REFRESH_RATE, _window_setup.refresh_rate );
	glfwOpenWindowHint( GLFW_ACCUM_RED_BITS, _window_setup.accumulation_color_bits.r );
	glfwOpenWindowHint( GLFW_ACCUM_GREEN_BITS, _window_setup.accumulation_color_bits.g );
	glfwOpenWindowHint( GLFW_ACCUM_BLUE_BITS, _window_setup.accumulation_color_bits.b );
	glfwOpenWindowHint( GLFW_ACCUM_ALPHA_BITS, _window_setup.accumulation_color_bits.a );
	glfwOpenWindowHint( GLFW_AUX_BUFFERS, _window_setup.auxiliary_buffer );
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, (int)!_window_setup.resizeable );
	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, _window_setup.multisampling_count );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, (int)_window_setup.opengl_version );
	int minor = ((int)(_window_setup.opengl_version * 10)/10) % 10;
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, minor );
	glfwOpenWindowHint( GLFW_OPENGL_FORWARD_COMPAT, (int)_window_setup.forward_compatible );
	glfwOpenWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, _window_setup.debug_context );
	glfwOpenWindowHint( GLFW_OPENGL_PROFILE, _window_setup.opengl_profile ); 

	int fullscreen = ( _window_setup.fullscreen ) ? GLFW_FULLSCREEN : GLFW_WINDOW;

    int result = glfwOpenWindow( 
		_window_setup.width,
		_window_setup.height, 
		_window_setup.color_bits.r,
		_window_setup.color_bits.g,
		_window_setup.color_bits.b,
		_window_setup.color_bits.a,
		_window_setup.depth_bits,
		_window_setup.stencil_bits,
		fullscreen );

    CRAP_ASSERT_DEBUG( result == GL_TRUE, "Failed to create a GLFW Window");

	glfwSetWindowTitle( _window_setup.title.cstring() );
	glfwSetWindowPos( _window_setup.position.x, _window_setup.position.y );
}

void renderwindow::close( void )
{
	glfwCloseWindow();
}

void renderwindow::reset_window( void )
{
	close();
	open();
}

void renderwindow::set_position( const vector2i& pos )
{
	_window_setup.position = pos;
	glfwSetWindowPos( pos.x, pos.y );
}

void renderwindow::set_size( int width, int height )
{
	_window_setup.width = width;
	_window_setup.height = height;
	glfwSetWindowSize( width, height );
}

void renderwindow::set_title( const string64& name )
{
	_window_setup.title = name;
	glfwSetWindowTitle( name.cstring() );
}

void renderwindow::set_fullscreen( bool value )
{
	if( value && _window_setup.fullscreen )
	{
		glfwRestoreWindow();
	}
	else if( value )
	{
		_window_setup.fullscreen = true;
		reset_window();
	}
	else if( !value && _window_setup.fullscreen )
	{
		glfwIconifyWindow();
	}
}

void renderwindow::swap( void )
{
	glfwSwapBuffers();
}

/*
volatile void set_window_close_function( GLFWwindowclosefun function )
{
	glfwSetWindowCloseCallback( function );
}

volatile void set_window_size_function( GLFWwindowsizefun function )
{
	glfwSetWindowSizeCallback( function );
}

volatile void set_window_refresh_function( GLFWwindowrefreshfun function )
{
	glfwSetWindowRefreshCallback( function );
}
*/

} //namespace crap