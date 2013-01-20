////////////////////////////////////////////////////////
// CRAP Library
//!		@file audio.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief openal wrap
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#include "control/asserts.h"
#include "sound/audio.h"

//lib namespace
namespace crap
{

audio::audio(void)
{
	alGetError();
	_device = 0;
	CRAP_ASSERT_DEBUG(alGetError() != AL_NO_ERROR, "Could not open audio device");
}

audio::~audio(void)
{
	alcCaptureCloseDevice(_device);
}

}
