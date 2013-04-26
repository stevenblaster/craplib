////////////////////////////////////////////////////////
//	CRAP Library
//!		@file allocator.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Allocator interface
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_MEMORY_ALLOCATOR_H
#define CRAP_MEMORY_ALLOCATOR_H

#include "crap.h"

#include "container/intrusivelist.h"

//lib namespace
namespace crap
{

class allocator
{
public:
	allocator_type type;
	virtual void* allocate( size_t32 size, size_t32 alignment, size_t32 offset ){ return 0; }
	virtual void deallocate(void* address){}

protected:
	friend class memory_manager;

	void* _memory_start;
	void* _memory_end;

	crap::intrusive_list_node<allocator> _node;
};

}

#endif // CRAP_MEMORY_ALLOCATOR_H