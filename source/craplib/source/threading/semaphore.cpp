////////////////////////////////////////////////////////
//	CRAP Library
//!		@file semaphore.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Semaphore class
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "threading/semaphore.h"

//lib namespace
namespace crap
{

semaphore::semaphore( i32 init /*= 0*/ )
{
#if defined(CRAP_PLATFORM_WIN)
	_semaphore = CreateSemaphore( 0, init, LMAXIMUMCOUNT, 0 );
#else
	sem_init( &_semaphore, 0, init );
#endif
}

semaphore::semaphore(const semaphore& other)
{
	i32 value = other.value();
#if defined(CRAP_PLATFORM_WIN)
	_semaphore = CreateSemaphore( 0, value, LMAXIMUMCOUNT, 0 );
#else
	sem_init( &_semaphore, 0, value );
#endif
}

semaphore::~semaphore( void )
{
#if defined(CRAP_PLATFORM_WIN)
	CloseHandle( _semaphore );
#else
	sem_destroy( &_semaphore );
#endif
}

void semaphore::operator=( const semaphore& other )
{
	reset( other.value() );
}

bool semaphore::wait() const
{
#if defined(CRAP_PLATFORM_WIN)
	return WaitForSingleObject( static_cast< SEMAPHORE_HANDLE >(_semaphore), INFINITE ) == 0x00000000L;
#else
	return sem_wait( const_cast<SEMAPHORE_HANDLE*>(&_semaphore) ) == 0;
#endif
}

bool semaphore::post()
{
#if defined(CRAP_PLATFORM_WIN)
	return ReleaseSemaphore( static_cast< SEMAPHORE_HANDLE >(_semaphore), 1, 0 ) != 0;
#else
	return sem_post( &_semaphore ) == 0;
#endif
}

i32 semaphore::value() const
{
#if defined(CRAP_PLATFORM_WIN)
	long value = -1; //was i64s (long)
	ReleaseSemaphore( static_cast<const SEMAPHORE_HANDLE>(_semaphore), 0, &value );
	return (i32)value;
#else
	i32 value = -1;
	sem_getvalue( const_cast<SEMAPHORE_HANDLE*>(&_semaphore), &value );
	return value;
#endif
}

void semaphore::reset( i32 init /*= 0*/ )
{
#if defined(CRAP_PLATFORM_WIN)
	CloseHandle(_semaphore);
	_semaphore = CreateSemaphore( 0, init, LMAXIMUMCOUNT, 0 );
#else
	sem_destroy( &_semaphore );
	sem_init( &_semaphore, 0, init );
#endif
}

}	// namespace crap
