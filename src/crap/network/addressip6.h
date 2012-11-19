////////////////////////////////////////////////////////
// CRAP Library
//!		@file addressip6.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief ip ver 6 address + port
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_ADDRESSIP6_H
#define CRAP_ADDRESSIP6_H

#include "control/asserts.h"

//lib namespace
namespace crap
{

struct address_ip6
{
	//! @brief data structure
	sockaddr_in6 socket_address;

	//! @brief default constructor
	address_ip6(void);

	//! @brief copy constructor
	address_ip6( const address_ip6& other );

	//! @brief values constructor
	address_ip6( const u128& addr, const u16& prt );

	//! @brief values constructor
	address_ip6( const u16& aa, const u16& bb, const u16& cc, const u16& dd,
				 const u16& ee, const u16& ff, const u16& gg, const u16& hh, const u16& prt );

	//! @brief assignment operator
	address_ip6& operator=( const address_ip6& other );

	//! @convert ip to local endian
	u128 get_ip( void ) const;

	//! @convert ip to network endian
	void set_ip( const u128& ip );

	//! @convert port to local endian
	u16 get_port( void ) const;

	//! @convert port to network endian
	void set_port( const u16& port );
};

}	//namespace crap

#endif // CRAP_ADDRESSIP6_H
