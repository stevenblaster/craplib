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
#include "network/sockets.h"
#include "network/addressip6.h"

//lib namespace
namespace crap
{

address_ip6::address_ip6( void )
{
	socket_address.sin6_family = ip_v6;
}

address_ip6::address_ip6( const address_ip6& other )
{
	socket_address.sin6_family = ip_v6;
	socket_address.sin6_addr = other.socket_address.sin6_addr;
	socket_address.sin6_port = other.socket_address.sin6_port;
}

address_ip6::address_ip6( const u128& ip, const u16& prt )
{
	socket_address.sin6_family = ip_v6;
	u128 tmp = endian::to_big(ip);
	memcpy(&socket_address.sin6_addr, &tmp, 16);
	socket_address.sin6_port = htons(prt);
}

address_ip6::address_ip6( const u16& aa, const u16& bb, const u16& cc, const u16& dd,
						  const u16& ee, const u16& ff, const u16& gg, const u16& hh, const u16& prt )
{
	u128 ip;

//workaround
#if defined(CRAP_COMPILER_GCC)
	ip = ( (u128)aa << 112 ) | ( (u128)bb << 96 ) | ( (u128)cc << 80 ) | ( (u128)dd << 64 ) |
		( (u128)ee << 48 ) | ( (u128)ff << 32 ) | ( (u128)gg << 16 ) | hh;
#else
	ip.part_16[0] = aa;
	ip.part_16[1] = bb;
	ip.part_16[2] = cc;
	ip.part_16[3] = dd;
	ip.part_16[4] = ee;
	ip.part_16[5] = ff;
	ip.part_16[6] = gg;
	ip.part_16[7] = hh;
	/*ip.part_64[0] = ( aa << 48 ) | ( bb << 32 ) | ( cc << 16 ) | dd;
	ip.part_64[1] = ( ee << 48 ) | ( ff << 32 ) | ( gg << 16 ) | hh;*/
#endif
	ip = endian::to_big(ip);

	memcpy(&socket_address.sin6_addr, &ip, 16);
	socket_address.sin6_port = htons(prt);
	socket_address.sin6_family = ip_v6;
}

address_ip6& address_ip6::operator=( const address_ip6& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	socket_address.sin6_addr = other.socket_address.sin6_addr;
	socket_address.sin6_port = other.socket_address.sin6_port;
	return *this;
}

u128 address_ip6::get_ip( void ) const
{
	return endian::big_to_local( *((u128*)&socket_address.sin6_addr) );
}

void address_ip6::set_ip( const u128& ip )
{
	u128 tmp = endian::to_big(ip);
	memcpy(&socket_address.sin6_addr, &tmp, 16);
}

u16 address_ip6::get_port( void ) const
{
	return ntohs(socket_address.sin6_port);
}

void address_ip6::set_port( const u16& port )
{
	socket_address.sin6_port = htons(port);
}

#if defined( CRAP_COMPILER_GCC )
address_ip6 address_ip6::any = address_ip6(0,0);
#else
address_ip6 address_ip6::any = address_ip6(u128(),0);
#endif

}	//namespace crap

