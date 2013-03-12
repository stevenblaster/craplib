////////////////////////////////////////////////////////
//	CRAP Library
//!		@file sleep.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Thread sleeps...
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "threading/sleep.h"

//lib namespace
namespace crap
{

void sleep_msec( u32 millisec )
{
	SLEEP_MSEC(millisec);
}

void sleep_sec( u32 seconds )
{
	SLEEP_MSEC( seconds * 1000 );
}

}
