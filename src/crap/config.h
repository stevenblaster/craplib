////////////////////////////////////////////////////////
// CRAP Library
//	config.h
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
//		Collecting all config/*.h files
// 	Setting up configuration such as
//		breakpoints
//
//	Status (scratch, developed, final):
//		scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_H
#define CRAP_CONFIG_H

//include all headers of config folder
#include "config/platforms.h"
#include "config/processors.h"
#include "config/compilers.h"
#include "config/types.h"
#include "config/endianness.h"
#include "config/threading.h"
#include "config/memory.h"
#include "config/simd.h"
#include "config/math.h"



#endif // CRAP_CONFIG_H
