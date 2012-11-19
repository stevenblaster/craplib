////////////////////////////////////////////////////////
// CRAP Library
//!		@file packet.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief combine address with data
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_PACKET_H
#define CRAP_PACKET_H

//lib namespace
namespace crap
{

template<typename ADDRESS_T, size_t32 S>
struct packet
{
	ADDRESS_T address;
	u8 data[S];
};

}	// namespace crap

#endif // CRAP_PACKET_H
