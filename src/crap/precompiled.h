////////////////////////////////////////////////////////
// CRAP Library
//!		@file config.h
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Precompiled header
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#ifndef CRAP_PRECOMPILED_H
#define CRAP_PRECOMPILED_H

//cpp includes
#include <memory>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

////cpuinfo include on VC or complatible
//#if (defined(CRAP_COMPILER_VC) || defined(CRAP_COMPILER_INTEL))
//	#include <intrin.h>
//#endif

//default includes
#include "config.h"

//include control headers
#include "control/breakpoints.h"
#include "control/asserts.h"

//platform specific stuff
#ifdef CRAP_TARGET_WINDOWS
#include <malloc.h>
#endif


#endif // CRAP_PRECOMPILED_H
