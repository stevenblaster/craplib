////////////////////////////////////////////////////////
//  CRAP Library
//!		@file functorthread.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Thread template executing functors
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef FUNCTORTHREAD_H
#define FUNCTORTHREAD_H

#include "config/threading.h"
#include "control/asserts.h"

//lib namespace
namespace crap
{

/*
 *! @brief Template thread class
 */

template<class T>
class functor_thread
{
private:
	T _runnable;
	THREAD_HANDLE _thread;
	bool _running;

	//! @brief private static thread starter, defined by macros
	static THREAD_RETURN THREAD_STARTER( ptr );

public:

	//! @brief default constructor
	functor_thread(void);

	//! @brief destructor
	~functor_thread(void);

	//! @brief starting thread, returning handle
	THREAD_HANDLE start(void);
	bool join(void) const;
	bool kill(void);

	THREAD_HANDLE thread_id(void);
	bool is_running(void);
};

template<class T>
functor_thread<T>::functor_thread(void) : _running(false)
{
}

template<class T>
functor_thread<T>::~functor_thread(void)
{
	if( !kill() )
		join();
}

template<class T>
THREAD_RETURN functor_thread<T>::THREAD_STARTER( ptr )
{
	CRAP_ASSERT_DEBUG( THREAD_CANCEL_SETUP == 0, "Could not setup thread cancel type" );

	functor_thread<T>* thread_pointer = (functor_thread<T>) ptr;
	thread_pointer->_running = true;
#if defined(CRAP_PLATFORM_WIN)
	thread_pointer->_runnable();
	THREAD_RETURN rtn = 0x00;
#else
	THREAD_RETURN rtn = (THREAD_RETURN) thread_pointer->_runnable();;
#endif
	thread_pointer->_running = false;
	return rtn;
}

template<class T>
bool functor_thread<T>::join(void) const
{
	if( !_running )
		return false;

	return THREAD_JOIN( _thread ) == THREAD_ZERO;
}

template<class T>
THREAD_HANDLE functor_thread<T>::start(void)
{
	THREAD_CREATE( _thread, starter, _runnable);
	CRAP_ASSERT_DEBUG( _thread != THREAD_NULL, "Thread coudn't be started");
	return _thread;
}

template<class T>
bool functor_thread<T>::kill(void)
{
	if(!_running)
		return false;

	bool success = THREAD_KILL( _thread );
	if( success )
		_running = false;
	return success;
}

template<class T>
THREAD_HANDLE functor_thread<T>::thread_id(void)
{
	return _thread;
}

template<class T>
bool functor_thread<T>::is_running(void)
{
	return _running;
}

} // namespace crap

#endif // FUNCTORTHREAD_H
