////////////////////////////////////////////////////////
// CRAP Library
//!		@file addressip6.cpp
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

#include "control/endian.h"
#include "network/addressip6.h"

//lib namespace
namespace crap
{

address_ip6::address_ip6( void )
{

}

address_ip6::address_ip6( const address_ip6& other )
{
	address = other.address;
	port = other.port;
}

address_ip6::address_ip6( const u64& addr, const u64& ifc, const u16& prt )
{
	address.ip = addr;
	address.interface = ifc;
	port = prt;
}

address_ip6::address_ip6( const u8& aa, const u8& bb, const u8& cc, const u8& dd,
						  const u8& ee, const u8& ff, const u8& gg, const u8& hh, const u16& prt )
{
	a = aa;
	b = bb;
	c = cc;
	d = dd;
	e = ee;
	f = ff;
	g = gg;
	h = hh;
	port = prt;
}

address_ip6::address_ip6( const ip_v6& addr, const u16& prt )
{
	address = addr;
	port = prt;
}

address_ip6& address_ip6::operator=( const address_ip6& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	address = other.address;
	port = other.port;
	return *this;
}

ip_v6 address_ip6::ip_to_network( void ) const
{
	return endian::to_big(address);
}

u16 address_ip6::port_to_network( void ) const
{
	return endian::to_big(port);
}

}	//namespace crap
