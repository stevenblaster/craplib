////////////////////////////////////////////////////////
//	CRAP Library
//!		@file time.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Provides info of time and clock
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_TIME_H
#define CRAP_CONTROL_TIME_H

#include "container/staticstring.h"

//lib namespace
namespace crap
{

class time
{
	public:
		struct time_info
		{
				u16 seconds;			/* Seconds.	[0-60] (1 leap second) */
				u16 minutes;			/* Minutes.	[0-59] */
				u16 hours;			/* Hours.	[0-23] */
				u16 day;			/* Day.		[1-31] */
				u16 month;			/* Month.	[0-11] */
				u16 year;			/* Year	- 1900.  */
				u16 weekday;			/* Day of week.	[0-6] */
				u16 yearday;			/* Days in year.[0-365]	*/

				time_info( u16 s, u16 m, u16 h, u16 d, u16 M, u16 Y, u16 w, u16 y ) : seconds(s),minutes(m),hours(h),day(d), month(M), year(1900+Y), weekday(w), yearday(y) {}
		};

		static time& instance( void );
		~time( void );

		time_info current_time( void );
		u64 current_tick( void );

		string64 week_day_name( u16 id );
		string64 month_name( u16 id );

		static const u32 TICKS_PER_SECOND;
	protected:
	private:
		time();
		static time* _instance;
};

}	// crap

#endif // CRAP_CONTROL_TIME_H
