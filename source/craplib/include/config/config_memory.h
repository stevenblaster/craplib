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

#define CRAP_STACK_MEMORY( size ) alloca( size )
#define CRAP_HEAP_MEMORY( size ) crap::memory_manager::raw_memory( size )

//lib namespace
namespace crap
{
	enum allocator_type 
	{ 
		stack_allocator,
		linear_allocator,
		double_ended_stack_allocator,
		frame_allocator,
		pool_allocator
	};
}


#endif // CRAP_CONFIG_MEMORY_H
