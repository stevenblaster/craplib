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

#include "network/addressip4.h"
#include "network/addressip6.h"

//lib namespace
namespace crap
{

template<typename ADDRESS_T, size_t32 S>
struct packet
{
	ADDRESS_T address;
	u8 data[S];
};

//types...
template< size_t32 S >
struct packet_ip4 : public packet< crap::address_ip4, S>
{

};

template< size_t32 S >
struct packet_ip6 : public packet< crap::address_ip6, S>
{

};

}	// namespace crap

#endif // CRAP_PACKET_H
