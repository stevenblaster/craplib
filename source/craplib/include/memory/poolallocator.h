////////////////////////////////////////////////////////
//	CRAP Library
//!		@file poolallocator.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief A Pool Allocator
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_MEMORY_POOLALLOCATOR_H
#define CRAP_MEMORY_POOLALLOCATOR_H

#include "crap.h"

#include "memory/memorymanager.h"
#include "memory/allocator.h"

//lib namespace
namespace crap
{

class pool_allocator : public allocator
{
public:
	explicit pool_allocator( size_t32 size ); //dont forget to init intrusive list
	pool_allocator( void* mem_start, void* mem_end );

	virtual void* allocate( size_t32 size, size_t32 alignment, size_t32 offset );
	virtual void deallocate(void* address);

private:

};

}

#endif // CRAP_MEMORY_POOLALLOCATOR_H