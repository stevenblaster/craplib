////////////////////////////////////////////////////////
//	CRAP Library
//		@file copyobject.h
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
//		@brief Help functions for copying data efficiently
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTROL_COPYOBJECT_H
#define CRAP_CONTROL_COPYOBJECT_H

#include "control/checkvtable.h"

//lib namespace
namespace crap
{
	
/*
 * @brief copy single obejct
 */

template<typename T>
void copy_object( const T* source, T* destination )
{
	if( crap::has_vtable<T>::RESULT )
		*destination = *source;
	else
		memcpy( destination, source, sizeof(T) );
};

/*
 * @brief copy array
 */

template<typename T>
void copy_array( const T* source, T* destination, u64 arraysize )
{
	if( crap::has_vtable<T>::RESULT )
	for( u64 i=0; i< arraysize; ++i)
		destination[i] = source[i];
	else
		memcpy( destination, source, sizeof(T) * arraysize );
};


}	// namespace crap

#endif // CRAP_CONTROL_COPYOBJECT_H
