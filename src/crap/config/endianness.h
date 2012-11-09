////////////////////////////////////////////////////////
//  CRAP Library
//		@file endianess.h
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
//		@brief Checking / setting macros caring about
//		little and big endian.
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_ENDIAN_H
#define CRAP_CONFIG_ENDIAN_H

#include "config/platforms.h"
#include "config/processors.h"

/*
 * @brief detect endian by processor type
 */

//known litte endian processors
#if ( defined(CRAP_PROCESSOR_X86_64) || defined(CRAP_PROCESSOR_X86) || defined(CRAP_PROCESSOR_IA64) || defined(CRAP_PROCESSOR_ARM) )

	#define CRAP_ENDIAN_LITTLE
	#define CRAP_ENDIAN_ID 0
	#define CRAP_ENDIAN_TYPE "little"

//else its big endian
#elif !defined(CRAP_PROCESSOR_UNKNOWN)

	#define CRAP_ENDIAN_BIG
	#define CRAP_ENDIAN_ID 1
	#define CRAP_ENDIAN_TYPE "big"

//or unknown
#else

	#define CRAP_ENDIAN_UNKNOWN
	#define CRAP_ENDIAN_ID 2
	#define CRAP_ENDIAN_TYPE "unknown"

#endif

#endif // CRAP_CONFIG_ENDIAN_H
