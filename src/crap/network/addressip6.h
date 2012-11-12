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
	struct ip_v6
	{
		u64 ip;
		u64 interface;
	};

	union
	{
		u16 a,b,c,d,e,f,g,h;
		ip_v6 address;
	};

	u16 port;

	//! @brief default constructor
	address_ip6(void);

	//! @brief copy constructor
	address_ip6( const address_ip6& other );

	//! @brief values constructor
	address_ip6( const ip_v6& addr, const u16& prt );

	//! @brief values constructor
	address_ip6( const u64& addr, const u64& ifc, const u16& prt );

	//! @brief values constructor
	address_ip6( const u8& aa, const u8& bb, const u8& cc, const u8& dd,
				 const u8& ee, const u8& ff, const u8& gg, const u8& hh, const u16& prt );

	//! @brief assignment operator
	address_ip6& operator=( const address_ip6& other );

	//! @convert ip to network endian
	ip_v6 ip_to_network( void ) const;

	//! @convert port to network endian
	u16 port_to_network( void ) const;
};

}	//namespace crap

#endif // CRAP_ADDRESSIP6_H
