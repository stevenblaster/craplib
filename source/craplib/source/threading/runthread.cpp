////////////////////////////////////////////////////////
//	CRAP Library
//!		@file thread.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Starts inherited runnable as thread
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "control/asserts.h"
#include "threading/runnable.h"

#include "threading/runthread.h"

namespace crap
{

runthread::runthread( runnable* run )
{
	THREAD_CREATE( _thread, runthread::starter, run);
	CRAP_ASSERT_DEBUG( _thread != THREAD_NULL, "Thread coudn't be started");

	_runnable = run;
}

runthread::~runthread()
{
	if( !kill_thread() )
		wait_for_thread();
	delete _runnable;

}

THREAD_RETURN runthread::THREAD_STARTER( ptr )
{
	CRAP_ASSERT_DEBUG( THREAD_CANCEL_SETUP == 0, "Could not setup thread cancel type" );

	runnable* run = static_cast< runnable* >( ptr );
#if defined(CRAP_PLATFORM_WIN)
	run->start();
	return 0x00;
#else
	return run->start();
#endif
}

bool runthread::wait_for_thread() const
{
	if( !_runnable->_is_running )
		return false;

	return THREAD_JOIN( _thread ) == THREAD_ZERO;
}

bool runthread::kill_thread()
{
	if(!_runnable->_is_running)
		return false;

	bool success = THREAD_KILL( _thread );
	if( success )
		_runnable->_is_running = false;
	return success;
}

THREAD_HANDLE runthread::thread_id()
{
	return _thread;
}

}	// namespace crap
