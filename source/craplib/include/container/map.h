////////////////////////////////////////////////////////
//	CRAP Library
//!		@file map.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Wrapper for std::map
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_MAP_H
#define CRAP_CONTAINER_MAP_H

#include "memory/stlallocatordefault.h"
#include <map>

//lib namespace
namespace crap
{
	template<typename T1,typename T2, typename Allocator = crap::stl_allocator_default< std::pair<T1,T2> > >
	class map : public std::map<T1, T2, Allocator>
	{
	};
}

#endif // CRAP_CONTAINER_MAP_H