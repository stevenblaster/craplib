////////////////////////////////////////////////////////
//	CRAP Library
//!		@file semaphore.h
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

#pragma once

#ifndef CRAP_THREADING_SEMAPHORE_H
#define CRAP_THREADING_SEMAPHORE_H

//lib namespace
namespace crap
{

class time;

class semaphore
{
private:
	SEMAPHORE_HANDLE _semaphore;

public:
	semaphore( i32 init = 0 );
	semaphore( const semaphore& other );
	~semaphore( void );

	void operator=( const semaphore& other );

	bool wait( void ) const;
	//! @todo: add timedWait and tryWait, do they exist in Win api?
	bool post( void );
	void reset( i32 init = 0 );

	i32 value( void ) const;
};

}	// namespace crap

#endif // CRAP_THREADING_SEMAPHORE_H
