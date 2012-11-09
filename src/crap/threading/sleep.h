////////////////////////////////////////////////////////
//	CRAP Library
//		@file sleep.h
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
//		@brief Thread sleeps...
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_THREADING_SLEEP_H
#define CRAP_THREADING_SLEEP_H

//lib namespace
namespace crap
{

void sleep_msec( u32 millisec );
void sleep_sec( u32 seconds );

}

#endif // CRAP_THREADING_SLEEP_H
