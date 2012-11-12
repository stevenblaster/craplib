////////////////////////////////////////////////////////
// CRAP Library
//!		@file addressip4.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief ip ver 4 address + port
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_ADDRESSIP4_H
#define CRAP_ADDRESSIP4_H

#include "control/asserts.h"

//lib namespace
namespace crap
{

struct address_ip4
{
	//! @brief data structure
	union
	{
		u8 a,b,c,d;
		u32 ip;
	};

	u16 port;

	//! @brief default constructor
	address_ip4(void);

	//! @brief copy constructor
	address_ip4( const address_ip4& other );

	//! @brief values constructor
	address_ip4( const u32& addr, const u16& prt );

	//! @brief values constructor
	address_ip4( const u8& aa, const u8& bb, const u8& cc, const u8& dd, const u16& prt );

	//! @brief assignment operator
	address_ip4& operator=( const address_ip4& other );

	//! @convert ip to network endian
	u32 ip_to_network( void ) const;

	//! @convert port to network endian
	u16 port_to_network( void ) const;
};

}	//namespace crap

#endif // CRAP_ADDRESSIP4_H
