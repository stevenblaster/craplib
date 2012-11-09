////////////////////////////////////////////////////////
//	CRAP Library
//		@file thread.cpp
//
//	Creator:
//		Steffen Kopany <steffen@kopany.at>
//
//	Author(s):
// 		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright (c) 2012 Steffen Kopany
//
//	Description:
//		@brief Starts inherited runnable as thread
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#include "control/asserts.h"
#include "threading/runnable.h"

#include "threading/thread.h"

namespace crap
{

thread::thread( runnable* run )
{
    THREAD_CREATE( _thread, thread::starter, run);
    CRAP_ASSERT_DEBUG( _thread != THREAD_NULL, "Thread coudn't be started");

    _runnable = run;
}

thread::~thread()
{
    if( !kill_thread() )
		wait_for_thread();
	delete _runnable;

}

THREAD_RETURN thread::THREAD_STARTER( ptr )
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

bool thread::wait_for_thread() const
{
    if( !_runnable->_is_running )
        return false;

    return THREAD_JOIN( _thread ) == THREAD_ZERO;
}

bool thread::kill_thread()
{
    if(!_runnable->_is_running)
        return false;

    bool success = THREAD_KILL( _thread );
    if( success )
    	_runnable->_is_running = false;
    return success;
}

THREAD_HANDLE thread::thread_id()
{
    return _thread;
}

}	// namespace crap
