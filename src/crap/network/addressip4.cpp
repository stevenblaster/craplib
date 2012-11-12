////////////////////////////////////////////////////////
// CRAP Library
//!		@file addressip4.cpp
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

#include "control/endian.h"
#include "network/addressip4.h"

//lib namespace
namespace crap
{

address_ip4::address_ip4( void )
{

}

address_ip4::address_ip4( const address_ip4& other )
{
	ip = other.ip;
	port = other.port;
}

address_ip4::address_ip4( const u8& aa, const u8& bb, const u8& cc, const u8& dd, const u16& prt )
{
	a = aa;
	b = bb;
	c = cc;
	d = dd;
	port = prt;
}

address_ip4::address_ip4( const u32& addr, const u16& prt )
{
	ip = addr;
	port = prt;
}

address_ip4& address_ip4::operator=( const address_ip4& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	ip = other.ip;
	port = other.port;
	return *this;
}

u32 address_ip4::ip_to_network( void ) const
{
	return endian::to_big(ip);
}

u16 address_ip4::port_to_network( void ) const
{
	return endian::to_big(port);
}

}	//namespace crap
