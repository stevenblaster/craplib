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
#include "crapwindow.h"

//lib namespace
namespace crap
{

crapwindow::crapwindow( const window_setup& setup ) : _window_setup( setup )
{
#ifndef CRAP_GLFW_INIT
#define CRAP_GLFW_INIT

    CRAP_ASSERT_DEBUG( glfwInit(), "Could not init GLFW" );

#endif
}

crapwindow::~crapwindow( void )
{
    close();
}

void crapwindow::update_settings( const window_setup& setup )
{
	_window_setup = setup;
}

void crapwindow::open( void )
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

    std::cerr << "Result is " << result << std::endl;
    CRAP_ASSERT_DEBUG( result == GL_TRUE, "Failed to create a GLFW Window");

	glfwSetWindowTitle( _window_setup.title.cstring() );
	glfwSetWindowPos( _window_setup.position.x, _window_setup.position.y );
}

void crapwindow::close( void )
{
	glfwCloseWindow();
}

void crapwindow::reset_window( void )
{
	close();
	open();
}

void crapwindow::set_position( const vector2i& pos )
{
	_window_setup.position = pos;
	glfwSetWindowPos( pos.x, pos.y );
}

void crapwindow::set_size( int width, int height )
{
	_window_setup.width = width;
	_window_setup.height = height;
	glfwSetWindowSize( width, height );
}

void crapwindow::set_title( const string64& name )
{
	_window_setup.title = name;
	glfwSetWindowTitle( name.cstring() );
}

} //namespace crap
