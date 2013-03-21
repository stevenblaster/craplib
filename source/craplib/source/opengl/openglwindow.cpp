////////////////////////////////////////////////////////
// CRAP Library
//!		@file openglwindow.cpp
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
#include "crap.h"

#if defined(CRAP_PLATFORM_WIN)
#pragma warning (disable:4005)
#endif

#include "GL/glew.h"
#include "GL/glfw.h"

#include "container/staticstring.h"
#include "opengl/openglwindow.h"

//lib namespace
namespace crap
{

opengl_window::opengl_window( const window_setup& setup ) : _window_setup( setup )
{
#ifndef CRAP_GLFW_INIT
#define CRAP_GLFW_INIT

    CRAP_ASSERT_DEBUG( glfwInit(), "Could not init GLFW" );
	glfwDisable(GLFW_AUTO_POLL_EVENTS); //disable autopolling, thats our stuff 

#endif
}

opengl_window::~opengl_window( void )
{
    close();
}

void opengl_window::update_settings( const window_setup& setup )
{
	_window_setup = setup;
}

b8 opengl_window::is_open( void ) const
{
	return glfwGetWindowParam( GLFW_OPENED );
}

void opengl_window::open( void )
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

	glfwSetWindowTitle( _window_setup.title.cstring() );
	glfwSetWindowPos( _window_setup.position.x, _window_setup.position.y );

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

	result = glewInit();
	CRAP_ASSERT_DEBUG( result == GLEW_OK, "Failed to init GLEW");
}

void opengl_window::close( void )
{
	glfwCloseWindow();
}

void opengl_window::reset_window( void )
{
	close();
	open();
}

vector2i opengl_window::size( void ) const
{
	vector2i rtn;
	glfwGetWindowSize( &rtn.x, &rtn.y );
	return rtn;
}

void opengl_window::set_position( const vector2i& pos )
{
	_window_setup.position = pos;
	glfwSetWindowPos( pos.x, pos.y );
}

void opengl_window::set_size( int width, int height )
{
	_window_setup.width = width;
	_window_setup.height = height;
	glfwSetWindowSize( width, height );
}

void opengl_window::set_title( const string64& name )
{
	_window_setup.title = name;
	glfwSetWindowTitle( name.cstring() );
}

void opengl_window::set_fullscreen( bool value )
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

void opengl_window::swap( void )
{
	glfwSwapBuffers();
}


void opengl_window::set_window_close_function( void* function )
{
	glfwSetWindowCloseCallback( (GLFWwindowclosefun)function );
}

void opengl_window::set_window_size_function( void* function )
{
	glfwSetWindowSizeCallback( (GLFWwindowsizefun)function );
}

void opengl_window::set_window_refresh_function( void* function )
{
	glfwSetWindowRefreshCallback( (GLFWwindowrefreshfun)function );
}

void opengl_window::poll_events( void )
{
	glfwPollEvents();
}

} //namespace crap
