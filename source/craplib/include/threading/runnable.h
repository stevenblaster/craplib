////////////////////////////////////////////////////////
//	CRAP Library
//!		@file runnable.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Runnable class for inheritance
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_THREADING_RUNNABLE_H
#define CRAP_THREADING_RUNNABLE_H

//macro for stopping at checkpoints
#define CRAP_THREAD_CHECKPOINT() if( _stopRunnable ) return 0x00

#include "container/fixedstring.h"

//lib namespace
namespace crap
{

class runnable
{

friend class runthread;

public:
	runnable( const crap::string64& name, bool delete_on_finish = true );
	virtual ~runnable();
	void* start();
	bool is_running() const;
	bool delete_on_finish() const;
	void stop_runnable();
	const string64& name() const;

protected:
	virtual void* run() = 0;
	bool _is_running;
	bool _stop_runnable;
	string64 _name;
	bool _delete_on_finish;
};

}	// crap

#endif // CRAP_THREADING_RUNNABLE_H
