////////////////////////////////////////////////////////
//	CRAP Library
//!		@file thread.h
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
#pragma once

#ifndef CRAP_THREADING_THREAD_H
#define CRAP_THREADING_THREAD_H

#include "config/threading.h"

//thread stopping and deleteing at scopeend
#define SCOPED_THREAD(runnable) crap::thread scopeThread__LINE__(runnable)

//lib namespace
namespace crap
{

class runnable;

class thread
{
private:
	runnable* _runnable;
	static THREAD_RETURN THREAD_STARTER( ptr );
	static void cleanup( void* self );
	THREAD_HANDLE _thread;

public:
	thread( runnable* runner );
	~thread();

	bool wait_for_thread() const;
	bool kill_thread();
	THREAD_HANDLE thread_id();
};

}	//namespace crap

#endif // CRAP_THREADING_THREAD_H
