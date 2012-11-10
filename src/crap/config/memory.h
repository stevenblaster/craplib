////////////////////////////////////////////////////////
//	CRAP Library
//!		@file memory.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Setting memory macros (depricated)
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_MEMORY_H
#define CRAP_CONFIG_MEMORY_H

//memory definitions
#ifndef CRAP_CONFIG_NO_MEMMAN
	#define CRAP_MEMORY_MANAGER
#endif
#ifndef CRAP_CONFIG_NO_MEMTRACK
	#define CRAP_MEMORY_TRACKER
#endif
#ifndef CRAP_CONFIG_NO_GARBAGECOLLECTOR
	#define CRAP_GARBAGE_COLLECTOR
	#define CRAP_GC_TICK 1000000
#endif

#endif // CRAP_CONFIG_MEMORY_H
