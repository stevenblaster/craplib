////////////////////////////////////////////////////////
//	CRAP Library
//!		@file runnable.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Runnable class for inheritance
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "threading/runnable.h"

//lib namespace
namespace crap
{

runnable::runnable( const crap::string64& name, bool delete_on_finish /*= true*/ ) :
		_is_running(false), _stop_runnable(false), _name(name), _delete_on_finish(delete_on_finish)
{

}

runnable::~runnable( void )
{

}

void* runnable::start( void )
{
	_is_running = true;
	void* rtn = run();
	_is_running = false;
	return rtn;
}

bool runnable::is_running( void ) const
{
	return _is_running;
}

bool runnable::delete_on_finish( void ) const
{
	return _delete_on_finish;
}

void runnable::stop_runnable( void )
{
	_stop_runnable = true;
}

const crap::string64& runnable::name( void ) const
{
	return _name;
}

}	// crap

