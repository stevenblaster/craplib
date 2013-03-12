////////////////////////////////////////////////////////
//	CRAP Library
//!		@file mutex.h
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

#pragma once

#ifndef CRAP_THREADING_MUTEX_H
#define CRAP_THREADING_MUTEX_H

//lib namespace
namespace crap
{

class mutex
{
private:

	MUTEX_HANDLE _mutex;
	CONDITION _condition;
	void init( void );
	bool _locked;

public:

	mutex( void );
	mutex( bool locked );
	mutex( const mutex& other );
	~mutex( void );

	mutex& operator=( const mutex& other );

	void lock( void );
	void unlock( void );
	bool try_lock( void );
	bool is_locked( void ) const;

	void wait_for_signal( void );
	void send_signal( void );
};

}	// namespace crap

#endif // CRAP_THREADING_MUTEX_H
