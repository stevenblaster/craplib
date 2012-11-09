////////////////////////////////////////////////////////
//	CRAP Library
//		@file semaphore.h
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
//		@brief Semaphore class
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_THREADING_SEMAPHORE_H
#define CRAP_THREADING_SEMAPHORE_H

#include "config/threading.h"

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
	// @todo: add timedWait and tryWait, do they exist in Win api?
	bool post( void );
	void reset( i32 init = 0 );

	i32 value( void ) const;
};

}	// namespace crap

#endif // CRAP_THREADING_SEMAPHORE_H
