////////////////////////////////////////////////////////
//	CRAP Library
//!		@file scopelock.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Locks a mutex until end of scope
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "threading/mutex.h"
#include "threading/semaphore.h"

#include "threading/scopelock.h"

//lib namespace
namespace crap
{

scope_lock::scope_lock( mutex* mutex )
{
	_mutex = mutex;
	_semaphore = 0;

	_mutex->lock();
}

scope_lock::scope_lock( semaphore* semaphore )
{
	_mutex = 0;
	_semaphore = semaphore;

	_semaphore->wait();
}

scope_lock::~scope_lock( void )
{
	if( _mutex != 0 )
		_mutex->unlock();

	if( _semaphore != 0 )
		_semaphore->post();
}

}	// namespace crap

