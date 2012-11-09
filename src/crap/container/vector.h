////////////////////////////////////////////////////////
//  CRAP Library
//		@file vector.h
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

#ifndef CRAP_CONTAINER_VECTOR_H
#define CRAP_CONTAINER_VECTOR_H

#include "memory/allocatordefault.h"
#include "eastl/vector.h"

//lib namespace
namespace crap
{
	template<typename T, typename Allocator = crap::allocator_default<T> >
	class vector : public eastl::vector<T, Allocator>
	{
	};
}

// @todo static vector

#endif	// CRAP_CONTAINER_VECTOR_H
