////////////////////////////////////////////////////////
// CRAP Library
//!		@file audio.h
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Wrapper for openal
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_AUDIO_H
#define CRAP_AUDIO_H

#include "precompiled.h"

#if defined(CRAP_PLATFORM_WIN)
#include "config_win32.h"
#elif defined(CRAP_PLATFORM_WIN)
#include "osx/config.h"
#else
#include "linux/config.h"
#endif


#endif //CARP_AUDIO_H