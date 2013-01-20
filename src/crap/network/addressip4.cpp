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
#include "network/sockets.h"
#include "network/addressip4.h"

//lib namespace
namespace crap
{

address_ip4::address_ip4( void )
{
	socket_address.sin_family = ip_v4;
}

address_ip4::address_ip4( const address_ip4& other )
{
	socket_address.sin_addr = other.socket_address.sin_addr;
	socket_address.sin_port = other.socket_address.sin_port;
}

address_ip4::address_ip4( const u8& aa, const u8& bb, const u8& cc, const u8& dd, const u16& prt )
{
	u32 addr = ( aa << 24 ) | ( bb << 16 ) | ( cc << 8 ) | dd;
	socket_address.sin_addr.s_addr = htonl(addr);
	socket_address.sin_port = htons(prt);
}

address_ip4::address_ip4( const u32& addr, const u16& prt )
{
	socket_address.sin_addr.s_addr = htonl(addr);
	socket_address.sin_port = htons(prt);
}

address_ip4& address_ip4::operator=( const address_ip4& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	socket_address.sin_addr = other.socket_address.sin_addr;
	socket_address.sin_port = other.socket_address.sin_port;
	return *this;
}

u32 address_ip4::get_ip( void ) const
{
	return ntohl(socket_address.sin_addr.s_addr);
}

void address_ip4::set_ip( const u32& ip )
{
	socket_address.sin_addr.s_addr = htonl(ip);
}

u16 address_ip4::get_port( void ) const
{
	return (u16) ntohl(socket_address.sin_port);
}

void address_ip4::set_port( const u16& port )
{
	socket_address.sin_port = (u16) htonl(port);
}

address_ip4 address_ip4::any = address_ip4(0x00000000,0);

}	//namespace crap
