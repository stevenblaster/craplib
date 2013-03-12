////////////////////////////////////////////////////////
//	CRAP Library
//!		@file processors.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Looking for processor specific macros
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_PROCESSORS_H
#define CRAP_CONFIG_PROCESSORS_H

//lib namespace
namespace crap
{

/*
 * Enum representing detected CPU
 */

enum cpu
{
	x86,
	x86_64,
	power_pc,
	ia64,
	arm,
	unknown_cpu
};

//x86_64
#if ( defined(_M_AMD64) || defined(_AMD64_) || defined(_M_X64) || defined(__amd64) || defined(__x86_64__) )

#define CRAP_PROCESSOR_X86_64
#define CRAP_PROCESSOR_NAME "x86_64"
static const crap::cpu processor = x86_64;

//x86
#elif ( defined(_M_IX86) || defined(_X86_) || defined(__i386__) || defined(__i386) || defined(__intel__) )

#define CRAP_PROCESSOR_X86
#define CRAP_PROCESSOR_NAME "x86"
static const crap::cpu processor = x86;

//power pc
#elif ( defined (powerc) || defined (__powerc) || defined (__powerpc__) )

#define CRAP_PROCESSOR_POWERPC
#define CRAP_PROCESSOR_NAME "PowerPC"
static const crap::cpu processor = power_pc;

//ia64
#elif ( defined(_M_IA64) || defined(_IA64_) || defined(__ia64) )

#define CRAP_PROCESSOR_IA64
#define CRAP_PROCESSOR_NAME "ia64"
static const crap::cpu processor = ia64;

//arm
#elif ( defined(_M_ARM) )

#define CRAP_PROCESSOR_ARM
#define CRAP_PROCESSOR_NAME "Arm"
static const crap::cpu processor = arm;

//unknown cpu
#else

#define CRAP_PROCESSOR_UNKNOWN
#define CRAP_PROCESSOR_NAME "Unknown"
static const crap::cpu processor = unknown_cpu;

#endif


}	// namespace crap

#endif // CRAP_CONFIG_PROCESSORS_H
