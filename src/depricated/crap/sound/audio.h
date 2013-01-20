////////////////////////////////////////////////////////
// CRAP Library
//!		@file audio.h
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
#pragma once

#ifndef CRAP_SOUND_AUDIO_H
#define CRAP_SOUND_AUDIO_H


//lib namespace
namespace crap
{

class audio
{
public:
	audio(void);
	~audio(void);

private:
	ALCdevice* _device;
};

}

#endif // CRAP_SOUND_AUDIO_H
