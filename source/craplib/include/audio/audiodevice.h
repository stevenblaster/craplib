////////////////////////////////////////////////////////
// CRAP Library
//!		@file audiodevice.h
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
#pragma once

#ifndef CRAP_AUDIODEVICE_H
#define CRAP_AUDIODEVICE_H

#include "AL/al.h"
#include "AL/alc.h"

//lib namespace
namespace crap
{

class audiodevice
{
private:
    void* _device;
    void* _context;

public:
	audiodevice( void );
	~audiodevice( void );
};

} //lib namespace


#endif //CRAP_AUDIODEVICE_H
