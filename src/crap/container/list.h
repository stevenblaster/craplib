////////////////////////////////////////////////////////
//  CRAP Library
//		@file list.h
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
//		@brief Placeholder for own implementation
//		currently using EASTL
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_LIST_H
#define CRAP_CONTAINER_LIST_H

#include "memory/allocatordefault.h"
#include "eastl/list.h"

//lib namespace
namespace crap
{
	template<typename T, typename Allocator = crap::allocator_default<T> >
	class list : public eastl::list<T, Allocator>
	{
	};
}


#endif //CRAP_CONTAINER_LIST_H
