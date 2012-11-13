////////////////////////////////////////////////////////
//	CRAP Library
//!		@file network.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Network settings
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_NETWORK_H
#define CRAP_CONFIG_NETWORK_H

#include "config/platforms.h"

#if defined(CRAP_PLATFORM_WIN)

//! @brief looks like windows.h contains that already somehwhere
//#include <winsock2.h>
//#pragma comment(lib, "wsock32.lib")

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netinet/in_systm.h>

#endif


#endif // CRAP_CONFIG_NETWORK_H
