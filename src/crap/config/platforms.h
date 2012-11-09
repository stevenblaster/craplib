////////////////////////////////////////////////////////
//  CRAP Library
//		@file platforms.h
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
//		@brief Looking for platform specific macros
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_PLATFORMS_H
#define CRAP_CONFIG_PLATFORMS_H

//lib namespace
namespace crap
{

/*
 * @brief enum representing detected od
 */

enum os
{
	platform_windows,
    platform_macintosh,
    platform_ios,
    platform_linux,
    platform_bsd,
    platform_unix,
    platform_unknown
};

//Windwos
#if ( defined(_WIN32) || defined(__WIN32__) )

#define CRAP_PLATFORM_WIN
#define CRAP_PLATFORM_NAME "Windows"
static const crap::os platform = platform_windows;

//Mac / IOS
#elif ( defined(__MACH__) || defined(__APPLE_CPP__) || defined(__APPLE__) )

	// IOS
	#include "TargetConditionals.h"
    #if ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )

		#define CRAP_PLATFORM_IOS
		#define CRAP_PLATFORM_NAME "IOS"
		static const crap::os platform = platform_ios;

	// Mac
	#else

		#define CRAP_PLATFORM_MAC
		#define CRAP_PLATFORM_NAME "Macintosh"
		static const crap::os platform = platform_macintosh;

	#endif

//Linux
#elif ( defined(linux) || defined(__linux) || defined(__linux__) )

#define CRAP_PLATFORM_LINUX
#define CRAP_PLATFORM_NAME "Linux"
static const crap::os platform = platform_linux;

//FreeBSD
#elif ( defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)  )

#define CRAP_PLATFORM_BSD
#define CRAP_PLATFORM_NAME "Bsd"
static const crap::os platform = platform_bsd;

//other unix
#elif ( defined(__unix__) || defined(__SUNPRO_CC) || defined(__sun) )

#define CRAP_PLATFORM_UNIX
#define CRAP_PLATFORM_NAME "Unix"
static const crap::os platform = platform_unix;

//other platform
#else

#define CRAP_PLATFORM_UNKNOWN
#define CRAP_PLATFORM_NAME "Unknown"
static const crap::os platform = platform_unknown;

#endif

}	// namespace crap

#endif // CRAP_CONFIG_PLATFORMS_H
