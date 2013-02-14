////////////////////////////////////////////////////////
//	CRAP Library
//!		@file time.cpp
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
#include <ctime>
#include "time.h"

//lib namespace
namespace crap
{

const u32 time::TICKS_PER_SECOND = CLOCKS_PER_SEC;

time* time::_instance = 0;

time& time::instance( void )
{
	if( _instance == 0 )
	{
		_instance = new time();
	}
	return *_instance;
}

time::time( void )
{

}

time::~time( void )
{
	//dtor
}

u64 time::current_tick( void )
{
	return static_cast<u64>( clock() );
}

time::time_info time::current_time( void )
{
	time_t rawtime;
	struct tm * ti;

	::time ( &rawtime );
	ti = localtime ( &rawtime );

	return time_info(ti->tm_sec, ti->tm_min, ti->tm_hour, ti->tm_mday, ti->tm_mon, ti->tm_year, ti->tm_wday, ti->tm_yday);
}


string64 time::week_day_name( u16 id )
{
	string64 wdaysLong[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	return wdaysLong[id];
}

string64 time::month_name( u16 id )
{
	string64 monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	return monthNames[id];
}

}	//namespace crap
