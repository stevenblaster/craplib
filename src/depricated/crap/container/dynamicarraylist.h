////////////////////////////////////////////////////////
// CRAP Library
//	xxx.h
//
//	Creator:
//		Steffen Kopany <steffen@kopany.at>
//
//	Author(s):
// 	Steffen Kopany <steffen@kopany.at>
//
//	Copyright (c) 2012 Steffen Kopany
//
//	Description:
//		The description can take
//		more then one line
//
//	Status (scratch, developed, final):
//		scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_DYNAMICARRAYLIST_H
#define CRAP_CONTAINER_DYNAMICARRAYLIST_H

#include <vector>

#include "memory/standardallocator.h"

namespace crap
{
namespace container
{

template<typename T>
class DynamicArraylist : public std::vector<T, crap::memory::StandardAllocator<T> >
{

};

}
}

#endif // CRAP_CONTAINER_DYNAMICARRAYLIST_H
