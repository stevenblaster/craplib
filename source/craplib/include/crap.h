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

#ifndef CRAP_H
#define CRAP_H

//cpp includes
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <memory>

//include all headers of config folder
#include "config/config_platforms.h"
#include "config/config_processors.h"
#include "config/config_compilers.h"
#include "config/config_types.h"
#include "config/config_endianness.h"
#include "config/config_threading.h"
#include "config/config_memory.h"
#include "config/config_network.h"
#include "config/config_simd.h"
#include "config/config_math.h"
#include "config/config_network.h"
#include "config/config_files.h"
#include "config/config_logger.h"

//include control headers
#include "control/breakpoints.h"
#include "control/logger.h"
#include "control/asserts.h"

//platform specific stuff
#ifdef CRAP_PLATFORM_WIN
#include <malloc.h>
#pragma warning(disable : 4800)
#endif


#endif // CRAP_H
