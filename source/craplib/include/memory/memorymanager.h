////////////////////////////////////////////////////////
//	CRAP Library
//!		@file memorymanager.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Memory Manager
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_MEMORY_MEMORYMANAGER_H
#define CRAP_MEMORY_MEMORYMANAGER_H

#include "crap.h"

#include "memory/allocator.h"

//lib namespace
namespace crap
{

class memory_manager
{
public:
	/* get raw memory, construct, destruct, access allocators */
	static void* raw_memory( size_t32 size );
private:
	crap::intrusive_list<allocator> _intrusive_list;
};

}

#endif // CRAP_MEMORY_MEMORYMANAGER_H