////////////////////////////////////////////////////////
//	CRAP Library
//!		@file list.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Placeholder for own implementation
//		currently using EASTL
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_LIST_H
#define CRAP_CONTAINER_LIST_H

#include "memory/allocatordefault.h"
//#include "eastl/list.h"
#include <list>

//lib namespace
namespace crap
{
	template<typename T, typename Allocator = crap::allocator_default<T> >
	class list : public std::list<T, Allocator>
	{
	};
}


#endif //CRAP_CONTAINER_LIST_H
