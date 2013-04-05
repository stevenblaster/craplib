////////////////////////////////////////////////////////
// CRAP Library
//!		@file audiodevice.cpp
//
//	Author(s):
//!		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Wrapper for opanAL device
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "AL/al.h"
#include "AL/alc.h"

#include "audio/audiodevice.h"

//lib namespace
namespace crap
{

audiodevice::audiodevice( void )
{
	_device = alcOpenDevice(NULL);
	CRAP_ASSERT_DEBUG( _device, "Could not create OpenAL device." );

    _context = alcCreateContext( (ALCdevice*)_device, NULL );
    alcMakeContextCurrent( (ALCcontext*)_context );
	CRAP_ASSERT_DEBUG( _context, "Could not create OpenAL context." );
}

audiodevice::~audiodevice( void )
{
	alcMakeContextCurrent(NULL);
    alcDestroyContext( (ALCcontext*)_context );
    alcCloseDevice( (ALCdevice*)_device );
}

};
