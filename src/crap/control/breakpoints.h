////////////////////////////////////////////////////////
//	CRAP Library
//!		@file breakpoints.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Compiler/Platform specific breakpoints
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_BREAKPOINTS_H
#define CRAP_CONTROL_BREAKPOINTS_H

#include "config/compilers.h"
#include "config/processors.h"

/*
 * Breakpoint macros
 */

// no debugbreak
#if defined( CRAP_CONFIG_NODEBUG )
	#define CRAP_DEBUGBREAK()

// visual studio
#elif defined( CRAP_COMPILER_VC )
	#define CRAP_DEBUGBREAK() __debugbreak()

// power pc
#elif defined( CRAP_PROCESSOR_POWERPC )
	#define CRAP_DEBUGBREAK() asm(".long 0")

// GCC on x86, x86_64
#elif ( defined(CRAP_PROCESSOR_X86) || defined(CRAP_PROCESSOR_X86_64) ) && defined(CRAP_COMPILER_GCC)
	#define CRAP_DEBUGBREAK() asm("int3")

// other compiler on x86, x86_64
#elif ( defined(CRAP_PROCESSOR_X86) || defined(CRAP_PROCESSOR_X86_64) )
	#define CRAP_DEBUGBREAK() { __asm int 3 }
#else
	#define CRAP_DEBUGBREAK()
#endif


#endif // CRAP_CONTROL_BREAKPOINTS_H
