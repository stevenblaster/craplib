////////////////////////////////////////////////////////
//	CRAP Library
//		@file asserts.h
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
//		@brief Assert macros
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_ASSERTS_H
#define CRAP_CONTROL_ASSERTS_H

#include <assert.h>

#include "control/breakpoints.h"

#ifndef CRAP_CONFIG_NODEBUG
	#define CRAP_ASSERT_BREAK() CRAP_DEBUGBREAK()
#else
	#define CRAP_ASSERT_BREAK() exit(1)
#endif

#if  defined(CRAP_COMPILER_VC)
#define __func__ __FUNCTION__
#endif

#define CRAP_ASSERT_STOP(test, message)								\
	do {																				\
		if (!(test)) {																\
			std::cerr << std::endl											\
						<< "[ERROR] ASSERTION FAILED AT "		\
						<< __TIMESTAMP__									\
						<< std::endl												\
						<< "[FILE]: "												\
						<< __FILE__												\
						<< std::endl												\
						<< "[LINE]: "												\
						<< __LINE__											\
						<< std::endl												\
						<< "[FUNCTION]: "									\
						<< __func__												\
						<< std::endl												\
						<< "[INFO]: "											\
						<< message												\
						<< std::endl												\
						<< std::endl;												\
			exit(1);																	\
		}																				\
	} while (0)

#define CRAP_ASSERT_DEBUG(test, message)							\
	do {																				\
		if (!(test)) {																\
			std::cerr << std::endl											\
						<< "[DEBUG] ASSERTION FAILED AT "		\
						<< __TIMESTAMP__									\
						<< std::endl												\
						<< "[FILE]: "												\
						<< __FILE__												\
						<< std::endl												\
						<< "[LINE]: "												\
						<< __LINE__											\
						<< std::endl												\
						<< "[FUNCTION]: "									\
						<< __func__												\
						<< std::endl												\
						<< "[INFO]: "											\
						<< message												\
						<< std::endl												\
						<< std::endl;												\
			CRAP_DEBUGBREAK();											\
		}																				\
	} while (0)

#define CRAP_ASSERT_WARNING(test, message)						\
	do {																				\
		if (!(test)) {																\
			std::cerr << std::endl											\
						<< "[WARNING] ASSERTION FAILED AT "	\
						<< __TIMESTAMP__									\
						<< std::endl												\
						<< "[FILE]: "												\
						<< __FILE__												\
						<< std::endl												\
						<< "[LINE]: "												\
						<< __LINE__											\
						<< std::endl												\
						<< "[FUNCTION]: "									\
						<< __func__												\
						<< std::endl												\
						<< "[INFO]: "											\
						<< message												\
						<< std::endl												\
						<< std::endl;												\
		}																				\
	} while (0)

#define CRAP_ASSERT_ERROR(message)									\
	do {																				\
			std::cerr << std::endl											\
						<< "[ERROR] ASSERTION FAILED AT "		\
						<< __TIMESTAMP__									\
						<< std::endl												\
						<< "[FILE]: "												\
						<< __FILE__												\
						<< std::endl												\
						<< "[LINE]: "												\
						<< __LINE__											\
						<< std::endl												\
						<< "[FUNCTION]: "									\
						<< __func__												\
						<< std::endl												\
						<< "[INFO]: "											\
						<< message												\
						<< std::endl												\
						<< std::endl;												\
	} while (0)

#endif // CRAP_CONTROL_ASSERTS_H
