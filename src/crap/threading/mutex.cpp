////////////////////////////////////////////////////////
//	CRAP Library
//!		@file mutex.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief mutex class using win api or posix
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "threading/mutex.h"

namespace crap
{

void mutex::init( void )
{
#if defined(CRAP_PLATFORM_WIN)
	InitializeCriticalSection( &_mutex );
	_condition = CreateEvent( 0, true, false, 0 );
#else
	pthread_mutex_init( &_mutex, 0 );
	pthread_cond_init( &_condition, 0 );
#endif
	_locked = false;
}

mutex::mutex( void )
{
	init();
}

mutex::mutex( bool locked )
{
	init();
	if( locked )
	{
		lock();
	}
}

mutex::mutex( const mutex& other )
{
	init();

	if( other._locked && !_locked )
	{
		lock();
	}
}

mutex& mutex::operator=( const mutex& other )
{
	if( other._locked && !_locked )
	{
		lock();
	}
	else if( !other._locked && _locked )
	{
		unlock();
	}
	return *this;
}

mutex::~mutex( void )
{
#if defined(CRAP_PLATFORM_WIN)
	DeleteCriticalSection( &_mutex );
	CloseHandle( _condition );
#else
	pthread_mutex_unlock( &_mutex );
	pthread_mutex_destroy( &_mutex );
	pthread_cond_destroy( &_condition );
#endif
}

void mutex::lock( void )
{
	_locked = true;
#if defined(CRAP_PLATFORM_WIN)
	EnterCriticalSection( &_mutex );
#else
	pthread_mutex_lock( &_mutex );
#endif
}

bool mutex::try_lock( void )
{

#if defined(CRAP_PLATFORM_WIN)
	if( TryEnterCriticalSection( &_mutex ) && !_locked )
	{
		_locked = true;
		return true;
	}
	return false;
#else
	_locked = true;
	return pthread_mutex_trylock( &_mutex ) == 0;
#endif
}

void mutex::unlock( void )
{
	_locked = false;
#if defined(CRAP_PLATFORM_WIN)
	LeaveCriticalSection( &_mutex );
#else
	pthread_mutex_unlock( &_mutex );
#endif
}

bool mutex::is_locked( void ) const
{
	return _locked;
}

void mutex::wait_for_signal( void )
{
#if defined(CRAP_PLATFORM_WIN)
	WaitForMultipleObjects( 1, &_condition, false, INFINITE );
#else
	pthread_cond_wait( &_condition, &_mutex );
#endif
}

void mutex::send_signal( void )
{
#if defined(CRAP_PLATFORM_WIN)
	SetEvent( _condition );
#else
	pthread_cond_signal( &_condition );
#endif
}

}	// namespace crap
