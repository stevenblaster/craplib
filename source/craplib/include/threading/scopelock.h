////////////////////////////////////////////////////////
//	CRAP Library
//!		@file scopelock.h
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
#pragma once

#ifndef CRAP_THREADING_SCOPELOCK_H
#define CRAP_THREADING_SCOPELOCK_H

#include "threading/mutex.h"
#include "threading/semaphore.h"

//lock mutex or semaphore in local variable
#define SCOPE_MUTEX( type ) crap::scope_lock lock__LINE__(type)

//lib namespace
namespace crap
{

class scope_lock
{
private:
	mutex* _mutex;
	semaphore* _semaphore;

public:
	scope_lock( mutex* mutex );
	scope_lock( semaphore* semaphore );
	~scope_lock( void );
};

}	// namespace crap

#endif // CRAP_THREADING_SCOPELOCK_H
